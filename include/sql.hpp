/*************************************************************************
    > 文件名: include/sql.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 20时43分35秒
    >
 ************************************************************************/

#ifndef SQL_HPP
#define SPL_HPP

#include <iostream>
#include <cstdlib>
using namespace std;
#include <sqlite3.h>
#include "json.hpp"
#include "book-manage_config.hpp"
#include "debug.hpp"

int sqlin (book_json *res);

#endif

