aux_source_directory(${PROJECT_SOURCE_DIR}/src/isbn LIB_SRCS_LIST)
add_library(book-manage_isbn ${LIB_SRCS_LIST})
