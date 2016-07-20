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

int main(int argc, char *argv[])
{
	//setlocale(LC_ALL, "");
	init();
	print_main_menu();
	return 0;
}

void init()
{
	system("mkdir -p ~/.book-manage\n");
#define errr cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << ":" << errmsg << endl
	sqlite3 *db;
	char *errmsg = NULL;
	string tmp = getenv("HOME");
	tmp += "/.book-manage/book.db";
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

