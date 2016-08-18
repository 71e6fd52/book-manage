function(apt_get pkg)
    message(STATUS "Installing package ${pkg}")

    execute_process(COMMAND sudo apt-get install -y ${pkg} RESULT_VARIABLE install_failed OUTPUT_QUIET)
    if(install_failed)
        message(SEND_ERROR "${pkg} install failed")
        set(INSTALL_FILE_FAILED 1 PARENT_SCOPE)
        return()
    else(install_failed)
        message(STATUS "${pkg} install succeeded")
    endif(install_failed)
endfunction(apt_get pkg)

cmake_minimum_required(VERSION 3.5)
project(book-manage)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_Modules/")
apt_get(libsqlite3-dev)
apt_get(libjsoncpp-dev)
# 版本号
set (major_version 0)
set (minor_version 2)
set (revision_version 4)
# debug和release的参数
SET(CMAKE_CXX_FLAGS_DEBUG "--std=c++11 -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "--std=c++11 -O3 -Wall")
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
#link_directories(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(src)
message(STATUS "Building internationalization files")
execute_process(COMMAND ${PROJECT_SOURCE_DIR}/i18n 2 ${PROJECT_NAME} ${PROJECT_SOURCE_DIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/locale/ DESTINATION share/locale FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(FILES ${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME} DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
# test
#enable_testing()
add_test (Runs book-manage)

