if(ZISA_HAS_CUDA)

target_sources(core_cuda_obj
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/check_cuda_error.cpp
)

endif()
