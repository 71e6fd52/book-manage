/*************************************************************************
    > 文件名: ../src/isbn/web.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 10时36分38秒
    > 
 ************************************************************************/

#include "head.hpp"
using namespace std;

string get_web(unsigned long isbn)
{
	string output;
	try
	{
		boost::asio::io_service io;
		avhttp::http_stream h(io);
		string website;
		{
			ostringstream tmp;
			tmp << "http://api.douban.com/v2/book/isbn/" << isbn;
			website = tmp.str();
		}

		h.open(website);
		cout << &h;
	}
	catch (exception& e)
	{
		cerr << "Error:" << e.what() << endl;
	}
	return output;
}
