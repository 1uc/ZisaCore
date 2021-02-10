cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ZisaCore VERSION 0.1)

include("cmake/has_build_type.cmake")
include("cmake/warning_flags.cmake")
include("cmake/fast_debug.cmake")
include("cmake/sanitizers.cmake")
include("cmake/gperftools.cmake")
include("cmake/clang_tidy.cmake")

# -- Dependencies --------------------------------------------------------------
add_library(core_dependencies INTERFACE)

# experimental/filesystem
target_link_libraries(core_dependencies INTERFACE stdc++fs)

# Logging
if(ZISA_LOG_LEVEL)
  target_compile_definitions(core_dependencies INTERFACE ZISA_LOG_LEVEL=${ZISA_LOG_LEVEL})
endif()

# MPI
if(ZISA_HAS_MPI)
  find_package(MPI REQUIRED COMPONENTS CXX)
  target_compile_definitions(core_dependencies INTERFACE ZISA_HAS_MPI=1)
  target_link_libraries(core_dependencies INTERFACE MPI::MPI_CXX)
endif()

# CUDA
if(ZISA_HAS_CUDA)
  find_package(CUDAToolkit REQUIRED)
  target_compile_definitions(core_dependencies INTERFACE ZISA_HAS_CUDA=1)

  target_compile_options(core_dependencies INTERFACE
    $<BUILD_INTERFACE:$<$<COMPILE_LANGUAGE:CUDA>:--expt-relaxed-constexpr>>
  )
  target_link_libraries(core_dependencies INTERFACE CUDA::cudart)
endif()

# -- Zisa ----------------------------------------------------------------------
# -- core ----------------------------------------------------------------------
add_library(core_generic_obj OBJECT)
set_target_properties(core_generic_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(core_generic_obj PROPERTIES CXX_STANDARD 17)
target_include_directories(core_generic_obj PUBLIC
  $<BUILD_INTERFACE:${ZisaCore_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )
target_link_libraries(core_generic_obj PUBLIC core_dependencies)
target_link_libraries(core_generic_obj PRIVATE core_warning_flags)

if(ZISA_HAS_CUDA)
  add_library(core_cuda_obj OBJECT)
  set_target_properties(core_cuda_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)
  set_target_properties(core_cuda_obj PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
  set_target_properties(core_cuda_obj PROPERTIES CUDA_STANDARD 11)
  set_target_properties(core_cuda_obj PROPERTIES CXX_STANDARD 17)
  target_include_directories(core_cuda_obj PUBLIC
    $<BUILD_INTERFACE:${ZisaCore_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
  target_link_libraries(core_cuda_obj PUBLIC core_dependencies)
  target_link_libraries(core_cuda_obj PRIVATE core_warning_flags)
endif()

add_library(core STATIC)
set_target_properties(core PROPERTIES OUTPUT_NAME zisa_core)
target_sources(core PRIVATE $<TARGET_OBJECTS:core_generic_obj>)

if(ZISA_HAS_CUDA)
  target_sources(core PRIVATE $<TARGET_OBJECTS:core_cuda_obj>)
  set_target_properties(core PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)
endif()

target_include_directories(core PUBLIC
  $<BUILD_INTERFACE:${ZisaCore_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(core PUBLIC core_dependencies)
target_link_libraries(core PRIVATE core_warning_flags)


# -- clang tidy ----------------------------------------------------------------
if(CLANG_TIDY_EXE)
  set_target_properties(core PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

# -- install -------------------------------------------------------------------
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ZisaCoreConfigVersion.cmake"
  VERSION ${ZisaCore_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
  "cmake/ZisaCoreConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/ZisaCoreConfigVersion.cmake"
  DESTINATION lib/cmake/zisa
)

add_library(Zisa::core ALIAS core)
install(
  TARGETS core core_dependencies core_warning_flags
  EXPORT ZisaCoreTargets
)
include(GNUInstallDirs)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ZisaCoreTargets
  FILE ZisaCoreTargets.cmake
  NAMESPACE Zisa::
  DESTINATION lib/cmake/zisa
)


# -- Tests ---------------------------------------------------------------------
find_package(Catch2 REQUIRED)

add_executable(core_unit_tests "")
set_target_properties(core_unit_tests PROPERTIES OUTPUT_NAME unit_tests)
set_target_properties(core_unit_tests PROPERTIES CXX_STANDARD 17)
target_include_directories(core_unit_tests PUBLIC test)
target_link_libraries(core_unit_tests PUBLIC Zisa::core Catch2::Catch2)

enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

# -- Subdirectories ------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(test)
