aux_source_directory(${PROJECT_SOURCE_DIR}/src/isbn LIB_SRCS_LIST)
add_library(isbn SHARED ${LIB_SRCS_LIST})
