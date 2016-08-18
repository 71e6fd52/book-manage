/*************************************************************************
    > 文件名: ../src/mainlib/do.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月13日 星期三 14时33分35秒
    >
 ************************************************************************/

#include "head.hpp"
using namespace std;

static int errout(string msg, int code);

void increase(char target, string jsoninfo, string call_num)
{
	switch (target)
	{
		case 'B':
			json(jsoninfo, call_num, book_sql::sqlin, errout);
			break;

		case 'U':
			cerr << _("未完成") << endl;
			break;

		default:
			cout << _("选项不正确") << endl;
			return;
			break;
	}
}

static int errout(string msg, int code)
{
	cerr << code << ":" << msg << endl;
	return 0;
}

void search(char target, string content, unsigned int flag)
{
	switch (target)
	{
		case 'B':
			book_sql::sqlsearch(content, flag);
			break;

		case 'U':
			cerr << _("未完成") << endl;
			break;

		default:
			cout << _("选项不正确") << endl;
			return;
			break;
	}
}

int outbookinfo(book_json *res)
{
#define p(x) cout << #x << ":" << res -> x << endl;
	p(bookname);
	p(author);
	p(translator);
	p(publisher);
	p(pages);
	p(menu);
	p(summary);
	p(author_intro);
	p(isbn13);
	p(call_num);
	p(price);
	p(binding);
	return 0;
}
