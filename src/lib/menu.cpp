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
doing:
	cout << _("(I)增加\t(D)删除\t(S)查询") << endl;
	char doing,target;
	cin >> doing;
	switch(doing)
	{
		case 'i':
		case 'd':
		case 's':
			doing -= 0x20; //小写转大写
			DEBUGOUT(doing);
		case 'I':
		case 'D':
		case 'S':
			break;
		default:
			cout << _("请输入正确的选项") << endl;
			goto doing;
	}
target:
	cout << _("(B)书籍\t(U)用户") << endl;
	cin >> target;
	switch(target)
	{
		case 'b':
		case 'u':
			doing -= 0x20; //小写转大写
			DEBUGOUT(target);
		case 'B':
		case 'U':
			break;
		default:
			cout << _("请输入正确的选项") << endl;
			goto target;
	}
}
