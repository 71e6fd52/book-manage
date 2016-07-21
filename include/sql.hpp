/*************************************************************************
    > 文件名: include/sql.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 20时43分35秒
    >
 ************************************************************************/

#ifndef SQL_HPP
#define SQL_HPP

#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;
#include <sqlite3.h>
#include "json.hpp"
#include "book-manage_config.hpp"
#include "debug.hpp"

namespace book_sql
{
int sqlin(book_json *res);
int sqlsearch(string content, unsigned int flag);
}

const unsigned int SQL_search_flag_name = 0x01;
const unsigned int SQL_search_flag_summary = 0x02;
const unsigned int SQL_search_flag_case_sen = 0x04;
const unsigned int SQL_search_flag_anywhere = 0x08;
const unsigned int SQL_search_flag_head = 0x10;
const unsigned int SQL_search_flag_tail = 0x20;
const unsigned int SQL_search_flag_adjoin = 0x40;

#endif

