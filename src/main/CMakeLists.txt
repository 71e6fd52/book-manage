add_executable(book-manage main.cpp)
target_link_libraries(book-manage book book-manage_isbn pthread boost_system boost_filesystem jsoncpp sqlite3)
