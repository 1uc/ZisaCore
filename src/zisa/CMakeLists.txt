target_sources(core_generic_obj
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/datetime.cpp
)

if(ZISA_HAS_CUDA)

endif()
add_subdirectory(cuda)
add_subdirectory(io)
add_subdirectory(math)
add_subdirectory(utils)
