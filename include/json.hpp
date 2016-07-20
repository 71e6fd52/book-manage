/*************************************************************************
    > 文件名: ../include/json.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 17时28分34秒
    > json操作的头文件
 ************************************************************************/

#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
#include "json/json.h"
#include "avhttp.hpp"

struct book_json
{
	string bookname;
	string author;
	string translator;
	string publisher;
	string pages;
	string menu;
	string summary;
	string author_intro;
	string isbn13;
	string price;
	string binding;
};

inline string get(string name, Json::Value value)
{
	return value[name].asString();
}

string get_web(unsigned long long isbn);
int json(string in, int (*callback)(book_json *res), int (*errout)(string msg, int code),
         string &name);

#endif
