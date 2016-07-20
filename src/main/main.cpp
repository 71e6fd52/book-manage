/*************************************************************************
    > 文件名: main.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时45分10秒
    > main函数
 ************************************************************************/

#include "head.hpp"
using namespace std;

string bookmanagehome;

void init();

int main(int argc, char *argv[])
{
	//setlocale(LC_ALL, "");
	init();
	struct option longopts[] =
	{
		{ "book", no_argument, NULL, 'B' },
		{ "user", no_argument, NULL, 'U' },
		{ "increase", no_argument, NULL, 'i' },
		{ "delete", no_argument, NULL, 'd' },
		{ "search", no_argument, NULL, 's' },
		{ "borrow", no_argument, NULL, 'b' },
		{ "return", no_argument, NULL, 'r' },
		{ NULL, no_argument, NULL, 0 }
	};
	char doing = 0, target = 0;
	int opt;

	while ((opt = getopt_long(argc, argv, "BUidsbr", longopts, NULL)) != -1)
	{
		switch (opt)
		{
			case 'B':
			case 'U':
				target = opt;
				break;

			case 'i':
			case 'd':
			case 's':
			case 'b':
			case 'r':
				doing = opt - 0x20;
				break;

			default:
				break;
		}
	}

	print_main_menu(doing, target);
	return 0;
}

void init()
{
	bookmanagehome = getenv("HOME");
	bookmanagehome += "/.book-manage/";
	system("mkdir -p ~/.book-manage\n");
	ifstream test(bookmanagehome + "search.conf", ios_base::in);

	if (!test.is_open())
	{
		ofstream file(bookmanagehome + "search.conf" , ios_base::out | ios_base::binary);

		if (!file.is_open())exit(1);

		unsigned int flag = SQL_search_flag_name |
		                    SQL_search_flag_summary |
		                    SQL_search_flag_anywhere;
		file.write((char *)&flag, sizeof(unsigned int));
		file.close();
	}
	else
	{
		test.close();
	}

#define errr cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << ":" << errmsg << endl
	sqlite3 *db;
	char *errmsg = NULL;
	string tmp = bookmanagehome + "book.db";
	int rc = sqlite3_open_v2(tmp.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	if (rc)
	{
		sqlite3_close(db);
		errr;
		return;
	}

	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS book(\n"
	                  "ID\t\tINT\tPRIMARY KEY\tNOT NULL,\n"
	                  "name\t\tTEXT\t\t\tNOT NULL,\n"
	                  "author\t\tTEXT\t\t\t\t ,\n"
	                  "translator\tTEXT\t\t\t\t ,\n"
	                  "publisher\tTEXT\t\t\t\t ,\n"
	                  "pages\t\tINT\t\t\t\t ,\n"
	                  "menu\t\tTEXT\t\t\t\t ,\n"
	                  "summary\tTEXT\t\t\t\t ,\n"
	                  "author_intro\tTEXT\t\t\t\t ,\n"
	                  "isbn\t\tTEXT\t\t\tNOT NULL,\n"
	                  "call_num\tTEXT\t\t\t\t ,\n"
	                  "price\t\tTEXE\t\t\t\t ,\n"
	                  "binding	TEXT\t\t\t\t \n);\n",
	                  NULL, NULL, &errmsg);

	if (rc)
	{
		sqlite3_close(db);
		errr;
		return;
	}

	sqlite3_close(db);
	locale::global(locale(""));
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
}

