/*************************************************************************
    > 文件名: menu.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时51分55秒
    >
 ************************************************************************/

#include "head.hpp"
using namespace std;

void print_main_menu(char doing, char target)
{
	char odoing = doing, otarget = target;
start:
target:

	if (!target)
	{
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
				cerr << _("请输入正确的选项") << endl;
				otarget = 0;
				goto target;
		}
	}

	//未完成处理
	if (target == 'U')
	{
		cerr << target << _("未完成") << endl;
		otarget = 0;
		target = 0;
		goto target;
	}

doing:

	if (!doing)
	{
		cout << _("(Q)退出\t(I)增加\t(D)删除\t(S)查询") << endl;

		if (target == 'B') cout << _("(B)借书\t(R)还书") << endl;

		cin >> doing;

		switch (doing)
		{
			case 'b':
			case 'r':
				if (target != 'B')
				{
					cerr << _("请输入正确的选项") << endl;
					odoing = 0;
					doing = 0;
					goto doing;
				}
				else
				{
					doing -= 0x20; //小写转大写
					DEBUGOUT(doing);
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
					cerr << _("请输入正确的选项") << endl;
					odoing = 0;
					goto doing;
				}

			case 'I':
			case 'D':
			case 'S':
				break;

			case 'q':
			case 'Q':
				return;

			default:
				cerr << _("请输入正确的选项") << endl;
				odoing = 0;
				doing = 0;
				goto doing;
		}
	}

	//未完成处理
	if (!(doing == 'I' || doing == 'S'))
	{
		cerr << doing << _("未完成") << endl;
		odoing = 0;
		doing = 0;
		goto doing;
	}

	guide(doing, target);

	if (odoing && otarget)
	{
		return;
	}
	else
	{
		doing = odoing;
		target = otarget;
		goto start;
	}
}

int guide(char doing, char target)
{
	switch (target)
	{
		case 'B':
		case 'U':
			break;

		default:
			cerr << _("选项不正确") << endl;
			return -1;
	}

	string isbn, call_num, jsoninfo;

	switch (doing)
	{
		case 'B':
		case 'R':
			if (target != 'B')
			{
				cerr << _("选项不正确") << endl;
				return -1;
			}

		case 'I':
			while (true)
			{
				cout << _("请输入isbn号（输入0退出）： ");
				cin >> isbn;

				if (isbn == "0") return 0;

				if (get_web(isbn, jsoninfo) != 0)
					continue;

				cout << getbookname(jsoninfo) << endl;
				cout << _("请输入索书号： ");
				cin >> call_num;
				increase(target, jsoninfo, call_num);
			}

		case 'S':
			while (true)
			{
				cout << _("请输入搜索内容（输入_退出）： ");
				string content;
				cin >> content;

				if (content == "_")
					return 0;

				unsigned int flag;
				ifstream file(bookmanagehome + "search.conf",
				              ios_base::in | ios_base::binary);

				if (file.is_open())
				{
					file.read((char *)&flag, sizeof(unsigned int));
					file.close();
				}
				else
				{
					cerr << _("读取配置文件失败") << endl;
					return -2;
				}

				search(target, content, flag);
			}

		case 'D':
			break;

		default:
			cerr << _("选项不正确") << endl;
			return -1;
	}

	return 0;
}
