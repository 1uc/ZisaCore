cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ZisaCore)

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
add_library(zisa_core SHARED "")
set_target_properties(zisa_core PROPERTIES CXX_STANDARD 17)
target_include_directories(zisa_core PUBLIC
  $<BUILD_INTERFACE:${ZisaCore_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(zisa_core PUBLIC core_dependencies)
target_link_libraries(zisa_core PRIVATE warning_flags)

# -- clang tidy ----------------------------------------------------------------
if(CLANG_TIDY_EXE)
  set_target_properties(zisa_core PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

# -- Tests ---------------------------------------------------------------------
find_package(Catch2 REQUIRED)

add_executable(core_unit_tests "")
set_target_properties(core_unit_tests PROPERTIES OUTPUT_NAME unit_tests)
set_target_properties(core_unit_tests PROPERTIES CXX_STANDARD 17)
target_include_directories(core_unit_tests PUBLIC test)
target_link_libraries(core_unit_tests PUBLIC zisa_core Catch2::Catch2)

enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

# -- Subdirectories ------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(test)
