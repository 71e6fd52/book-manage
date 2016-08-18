/*************************************************************************
    > 文件名: src/sql/search.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月12日 星期二 20时02分22秒
    >
 ************************************************************************/

#include "head.hpp"
using namespace std;

#include "sql.hpp"

namespace book_sql
{

#define errr \
	cerr << __FILE__ << ":" << __LINE__ << ":" << __func__;\
	if (errmsg != NULL) cerr << ":" << errmsg; \
	cerr << endl;
#define out(x,y) \
	if (column_value[y])\
		cout << _(x) << column_value[y] << endl;


stack<int> *gpsti = NULL;
stack<string *> *gpststrp = NULL;

static int getmain(void *params, int n_column, char **column_value, char **column_name)
{
	gpsti->push(atoi(column_value[0]));
	string *tmp = new string(column_value[1]);
	gpststrp->push(tmp);
	return 0;
}

static int outall(void *params, int n_column, char **column_value, char **column_name)
{
	out("ID：", 0);
	out("书名：", 1);
	out("作者：", 2);
	out("译者：", 3);
	out("出版社：", 4);
	out("简介：", 5);
	out("作者介绍：", 6);
	out("isbn：", 7);
	out("价格：", 8);
	out("装帧形式：", 9);
	out("索书号：", 10);
	return 0;
}

int sqlsearch(string content, unsigned int flag)
{
	if (!(flag & SQL_search_flag_name || flag & SQL_search_flag_summary))
		return 1;

	if (flag & SQL_search_flag_anywhere)
		flag |= SQL_search_flag_head | SQL_search_flag_tail;

	sqlite3 *db;
	char *errmsg = NULL;
	string tmp = getenv("HOME");
	tmp += "/.book-manage/book.db";
	int rc = sqlite3_open_v2(tmp.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	if (rc)
	{
		sqlite3_close(db);
		errr;
		return -1;
	}

	gpsti = new stack<int>();
	gpststrp = new stack<string *>();
	tmp = "SELECT id,name FROM book WHERE";
	bool case_sen = false;

	if (flag & SQL_search_flag_case_sen)
		case_sen = true;

	if (flag & SQL_search_flag_name)
	{
		tmp += " name";

		if (case_sen)
			tmp += " GLOB";
		else
			tmp += " LIKE";

		tmp += " '";

		if (flag & SQL_search_flag_head)
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += content;

		if (flag & SQL_search_flag_tail)
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += "'";

		if (flag & SQL_search_flag_summary)
			tmp += " AND";
	}

	if (flag & SQL_search_flag_summary)
	{
		tmp += " summary";

		if (case_sen)
			tmp += " GLOB";
		else
			tmp += " LIKE";

		tmp += " '";

		if (flag & SQL_search_flag_head)
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += content;

		if (flag & SQL_search_flag_tail)
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += "'";
	}

	rc = sqlite3_exec(db, tmp.c_str(), getmain, NULL, &errmsg);

	if (rc)
	{
		delete gpsti;
		delete gpststrp;
		sqlite3_close(db);
		errr;
		return -2;
	}

	int size = gpststrp->size();
	string name[size];
	int id[size];

	for (int i = 0; i < size; ++i)
	{
		id[i] = gpsti->top();
		gpsti->pop();
		name[i] = *gpststrp->top();
		delete gpststrp->top();
		gpststrp->pop();
	}

	for (int i = 0; i < size; ++i)
		cout << id[size - i - 1] << ":" << name[size - i - 1] << endl;

	cout << _("你要查询哪本的详细信息（输入ID）：");
	string ID;
	cin >> ID;
	tmp =  "SELECT ID,name,author,translator,publisher,summary,author_intro,isbn,price,binding,call_num FROM book WHERE ID = ";
	tmp += ID;
	tmp += ";";
	rc = sqlite3_exec(db, tmp.c_str(), outall, NULL, &errmsg);

	if (rc)
	{
		delete gpsti;
		delete gpststrp;
		sqlite3_close(db);
		errr;
		return -3;
	}

	delete gpsti;
	delete gpststrp;
	sqlite3_close(db);
	return 0;
}
}
