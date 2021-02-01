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

# -- Zisa ----------------------------------------------------------------------
# -- core ----------------------------------------------------------------------
add_library(core SHARED "")
set_target_properties(core PROPERTIES OUTPUT_NAME zisa_core)
set_target_properties(core PROPERTIES CXX_STANDARD 17)
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
