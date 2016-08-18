aux_source_directory(${PROJECT_SOURCE_DIR}/src/sql LIB_SRCS_LIST)
add_library(${PROJECT_NAME}_sql ${LIB_SRCS_LIST})
