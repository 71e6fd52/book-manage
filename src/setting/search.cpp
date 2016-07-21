/*************************************************************************
    > 文件名: src/setting/search.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月21日 星期四 10时33分02秒
    >
 ************************************************************************/

#include "head.hpp"
using namespace std;

void search_setting()
{
	unsigned int flag = 0;
	char in;
	cout << _("是否搜索名称[Y/n]");
	cin.get(in);

	if (in != '\n') cin.get();

	switch (in)
	{
		case 'y':
		case 'Y':
		case '\n':
			flag |= SQL_search_flag_name;
			break;

		default:
			flag &= ~SQL_search_flag_name;
			break;
	}

	cout << _("是否搜索简介[Y/n]");
	cin.get(in);

	if (in != '\n') cin.get();

	switch (in)
	{
		case 'y':
		case 'Y':
		case '\n':
			flag |= SQL_search_flag_summary;
			break;

		default:
			flag &= ~SQL_search_flag_summary;
			break;
	}

	cout << _("是否区分大小写[N/y]");
	cin.get(in);

	if (in != '\n') cin.get();

	switch (in)
	{
		case 'n':
		case 'N':
		case '\n':
			flag &= ~SQL_search_flag_case_sen;

		default:
			flag |= SQL_search_flag_case_sen;
	}

	cout << _("搜索(H)头，(T)尾，还是(A)任何地方[A/h/t]");
	cin.get(in);

	if (in != '\n') cin.get();

	switch (in)
	{
		case 'a':
		case 'A':
		case '\n':
		default:
			flag |= SQL_search_flag_anywhere;
			break;

		case 'h':
		case 'H':
			flag &= ~SQL_search_flag_anywhere;
			flag &= ~SQL_search_flag_tail;
			flag |= SQL_search_flag_head;
			break;

		case 't':
		case 'T':
			flag &= ~SQL_search_flag_anywhere;
			flag &= ~SQL_search_flag_head;
			flag |= SQL_search_flag_tail;
			break;
	}

	ofstream file(bookmanagehome + "search.conf" , ios_base::out | ios_base::binary);

	if (!file.is_open())
	{
		cerr << _("写入默认配置文件错误") << endl;
		exit(1);
	}

	file.write((char *)&flag, sizeof(unsigned int));
	file.close();
}
