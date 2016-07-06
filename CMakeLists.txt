cmake_minimum_required(VERSION 3.5)
project(book-manage)
# 版本号
set (book-manage_VERSION_one 0)
set (book-manage_VERSION_two 1)
set (book-manage_VERSION_three 1)
set (book-manage_VERSION_four 1)
# 配置一个头文件，通过它向源代码中传递一些CMake设置。
configure_file (
  "${PROJECT_SOURCE_DIR}/include/book-manage_config.h.in"
  "${PROJECT_BINARY_DIR}/include/book-manage_config.h"
)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(src)
