/*************************************************************************
    > 文件名: ../src/isbn/web.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 10时36分38秒
    >
 ************************************************************************/

#include "json.hpp"
using namespace std;

int get_web(string isbn, string &output)
{
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
	catch (exception &e)
	{
		cerr << "Error:" << e.what() << endl;
		return -1;
	}

	return 0;
}
#define g(x) get(x, value)
string getbookname(string in)
{
	Json::Reader reader;
	Json::Value value;

	if (!reader.parse(in, value)) return "error";

	return g("title");
}

int json(string in, string call_num, int (*callback)(book_json *res), int (*errout)(string msg,
         int code))
{
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
		call_num,
		g("price"),
		g("binding"),
	};
	int tmp;
	tmp = callback(&a);
	return tmp;
}
