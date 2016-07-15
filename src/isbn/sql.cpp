/*************************************************************************
    > 文件名: src/isbn/sql.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 20时02分22秒
    >
 ************************************************************************/

#include <iostream>
using namespace std;

#include "sql.hpp"

#define errr cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << ":" << errmsg << endl

int id = 0;
string bookisbn;
bool isRepect = false;

/*static int print_record(void *params,int n_column,char **column_value,char **column_name)
{
	for(int i = 0; i < n_column; ++i)
	{
		cout << "\t" << column_value[i];
	}
	cout << endl;
	return 0;
}*/
static int getid (void *params, int n_column, char **column_value, char **column_name)
{
	id = atoi (column_value[0]);
	return 0;
}
static int repect (void *params, int n_column, char **column_value, char **column_name)
{
	for (int i = 0; i < n_column; ++i)
	{
		if (bookisbn == column_value[i]) isRepect = true;
	}

	return 0;
}

string itoa (int input)
{
	stringstream ss;
	ss << input;
	return ss.str();
}

int sqlin (book_json *res)
{
	sqlite3 *db;
	char *errmsg = NULL;
	string tmp = getenv ("HOME");
	tmp += "/.book-manage/book.db";
	int rc = sqlite3_open_v2 (tmp.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	if (rc)
	{
		sqlite3_close (db);
		errr;
		return -1;
	}

	rc = sqlite3_exec (db,
	                   R"(CREATE TABLE IF NOT EXISTS book(
ID		INT	PRIMARY KEY	NOT NULL,
name		TEXT			NOT NULL,
author		TEXT				 ,
translator	TEXT				 ,
publisher	TEXT				 ,
pages		INT				 ,
menu		TEXT				 ,
summary	TEXT				 ,
author_intro	TEXT				 ,
isbn		TEXT			NOT NULL,
price		TEXE				 ,
binging	TEXT				 
);
)", NULL, NULL, &errmsg);

if (rc)
{
sqlite3_close (db);
errr;
return -2;
}

rc = sqlite3_exec (db, "SELECT count(*) FROM book", getid, NULL, &errmsg);

if (rc)
{
sqlite3_close (db);
errr;
return -3;
}

bookisbn = res -> isbn13;
isRepect = false;
rc = sqlite3_exec (db, "SELECT isbn FROM book", repect, NULL, &errmsg);

if (rc)
{
sqlite3_close (db);
errr;
return -4;
}

if (isRepect)
{
sqlite3_close (db);
return 1;
}

string command = "INSERT INTO book VALUES (";
#define d(x);  \
if ((res -> x) != "")  \
{  \
command += "'";  \
command += res -> x;  \
command += "', ";  \
}  \
else \
{  \
command += "null, ";  \
}
#define i(x)  \
if ((res -> x) != "")  \
{  \
command += res -> x;  \
command += ", ";  \
}  \
else \
{  \
command += "null, ";  \
}
command += itoa (id + 1);
command += ", "
d (bookname);
d (author);
d (translator);
d (publisher);
i (pages);
d (menu);
d (summary);
d (author_intro);
d (isbn13);
d (price);

if ( (res -> binging) != "")
{
command += "'";
command += res -> binging;
command += "', ";
}
else
{
command += "null);";
}

rc = sqlite3_exec (db, command.c_str(), NULL, NULL, &errmsg);

if (rc)
{
sqlite3_close (db);
errr;
cerr << command << endl;
return -5;
}

sqlite3_close (db);
return 0;
}
