target_sources(core_generic_obj
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/human_readable_size.cpp
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/indent_block.cpp
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/join.cpp
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/logging.cpp
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/parse_duration.cpp
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/replace_all.cpp
)

if(ZISA_HAS_CUDA)

endif()
