cmake_minimum_required(VERSION 3.5)
project(book-manage)
# 版本号
set (Major_Version_Number 0)
set (Minor_Version_Number 2)
set (Revision_Number -1)
# debug和release的参数
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} --std=c++0x -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} --std=c++0x -O3 -Wall")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
SET(DEBUG true)
else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
SET(DEBUG false)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
# 配置一个头文件，通过它向源代码中传递一些CMake设置。
configure_file (
  "${PROJECT_SOURCE_DIR}/include/book-manage_config.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/book-manage_config.hpp"
)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_INSTALL_PREFIX /usr/)
#aux_source_directory(${PROJECT_SOURCE_DIR}/lib LIB_LISTS)
#aux_source_directory(${PROJECT_SOURCE_DIR}/bin BIN_LIST)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(src)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/locale/ DESTINATION /usr/share/locale FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
add_test (Runs book-manage)
