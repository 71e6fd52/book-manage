/*************************************************************************
    > 文件名: menu.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时51分55秒
    > 
 ************************************************************************/

#include "head.hpp"
using namespace std;

void print_main_menu()
{
	char doing,target;
target:
	cout << _("(Q)退出\t(B)书籍\t(U)用户") << endl;
	cin >> target;
	switch (target)
	{
		case 'b':
		case 'u':
			target -= 0x20; //小写转大写
			DEBUGOUT(target);
		case 'B':
		case 'U':
			break;
		case 'q':
		case 'Q':
			return;
		default:
			cout << _("请输入正确的选项") << endl;
			goto target;
	}
//未完成处理
	if (target == 'U')
	{
		cerr << _("未完成") << endl;
		goto target;
	}
doing:
	cout << _("(Q)退出\t(I)增加\t(D)删除\t(S)查询") << endl;
	if (target == 'B') cout << _("(B)借书\t(R)还书") << endl;
	cin >> doing;
	switch(doing)
	{
		case 'b':
		case 'r':
			if (target != 'B') 
			{
				cout << _("请输入正确的选项") << endl;
				goto target;
			}
		case 'i':
		case 'd':
		case 's':
			doing -= 0x20; //小写转大写
			DEBUGOUT(doing);
		case 'B':
		case 'R':
			if (target != 'B') 
			{
				cout << _("请输入正确的选项") << endl;
				goto target;
			}
		case 'I':
		case 'D':
		case 'S':
			break;
		case 'q':
		case 'Q':
			return;
		default:
			cout << _("请输入正确的选项") << endl;
			goto doing;
	}
//未完成处理
	if (doing != 'I')
	{
		cerr << _("未完成") << endl;
		goto doing;
	}
	guide(doing, target);
	goto target;
}

int guide(char doing, char target)
{
	switch (target)
	{
		case 'B':
		case 'U':
			break;
		default:
			cout << _("选项不正确") << endl;
			return -1;
	}
	string isbn;
	switch(doing)
	{
		case 'B':
		case 'R':
			if (target != 'B') 
			{
				cout << _("选项不正确") << endl;
				return -2;
			}
		case 'I':
			while (true)
			{
				cout << _("请输入isbn号（0退出）：");
				cin >> isbn;
				if (isbn == "0") return 0;
				increase(target, isbn);
			}
		case 'D':
		case 'S':
			break;
		default:
			cout << _("选项不正确") << endl;
			return -2;
	}
	return 0;
}
