add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_main ${PROJECT_NAME}_isbn ${PROJECT_NAME}_sql ${PROJECT_NAME}_setting pthread boost_system boost_filesystem jsoncpp sqlite3)
