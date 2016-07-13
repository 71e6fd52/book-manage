/*************************************************************************
    > 文件名: ../src/isbn/web.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 10时36分38秒
    > 
 ************************************************************************/

#include "json.hpp"
using namespace std;

string get_web(string isbn)
{
	string output;
	try
	{
		boost::asio::io_service io;
		avhttp::http_stream h(io);

		string website = "http://api.douban.com/v2/book/isbn/";
		website += isbn;

		h.open(website);

		ostringstream tmp;
		tmp << &h;
		output = tmp.str();
	}
	catch (exception& e)
	{
		cerr << "Error:" << e.what() << endl;
	}
	return output;
}

int json(string in, int (*callback)(book_json* res), int (*errout)(string msg, int code), string &name)
{
#define g(x) get(x, value)
	Json::Reader reader;
	Json::Value value;
	if (!reader.parse(in, value)) return -1;
	if (value.isMember("msg"))
	{
		errout(g("msg"), atoi(g("code").c_str()));
		return -1;
	}

	int size = value["author"].size();
	string author;
	for (int i = 0; i < size; ++i)
	{
		author += value["author"][i].asString();
		author += " ";
	}
	size = value["translator"].size();
	string translator;
	for (int i = 0; i < size; ++i)
	{
		translator += value["translator"][i].asString();
		translator += " ";
	}

	book_json a =
	{
		g("title"),
		author,
		translator,
		g("publisher"),
		g("pages"),
		g("catalog"),
		g("summary"),
		g("author_intro"),
		g("isbn13"),
		g("price"),
		g("binging"),
	};
	name = g("title");
	int tmp, i = 0;
	while (((tmp = callback(&a)) < 0) && (i < 5)) ++i;
	return tmp;
}
