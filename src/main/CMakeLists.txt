add_executable(book-manage main.cpp)
target_link_libraries(book-manage book isbn pthread boost_system boost_filesystem)
