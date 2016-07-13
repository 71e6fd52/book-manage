/*************************************************************************
    > 文件名: main.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时45分10秒
    > main函数 
 ************************************************************************/

#include "head.hpp"
using namespace std;

void init();
int errout(string msg, int code);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	init();
	print_main_menu();
	string jsoninfo = get_web("9787115130228");
	json(jsoninfo, sqlin, errout);
	return 0;
}

void init()
{
	system("mkdir -p ~/.book-manage\n");
}

int errout(string msg, int code)
{
	cerr << code << ":" << msg << endl;
	return 0;
}
