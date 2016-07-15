/*************************************************************************
    > 文件名: ../src/mainlib/do.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月13日 星期三 14时33分35秒
    >
 ************************************************************************/

#include "head.hpp"
using namespace std;

static int errout (string msg, int code);

void increase (char target, string isbn)
{
	string jsoninfo, name;

	switch (target)
	{
		case 'B':
			jsoninfo = get_web (isbn);
			json (jsoninfo, sqlin, errout, name);
			cout << name << endl;
			break;

		case 'U':
			cerr << _ ("未完成") << endl;
			break;

		default:
			cout << _ ("选项不正确") << endl;
			return;
			break;
	}
}

static int errout (string msg, int code)
{
	cerr << code << ":" << msg << endl;
	return 0;
}
