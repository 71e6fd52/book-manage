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

#define errr cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << ":" << errmsg << endl

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
	cout << _("ID：") << column_value[0] << endl;
	cout << _("书名：") << column_value[1] << endl;
	cout << _("作者：") << column_value[2] << endl;
	cout << _("译者：") << column_value[3] << endl;
	cout << _("出版社：") << column_value[4] << endl;
	cout << _("简介：") << column_value[5] << endl;
	cout << _("作者介绍：") << column_value[6] << endl;
	cout << _("isbn：") << column_value[7] << endl;
	cout << _("价格：") << column_value[8] << endl;
	cout << _("装帧形式：") << column_value[9] << endl;
	return 0;
}

int sqlsearch(string content, unsigned int flag)
{
	if (!(bitlook(flag, SQL_search_flag_name) || bitlook(flag, SQL_search_flag_summary)))
		return 1;

	if (bitlook(flag, SQL_search_flag_anywhere))
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

	if (bitlook(flag, SQL_search_flag_case_sen))
		case_sen = true;

	if (bitlook(flag, SQL_search_flag_name))
	{
		tmp += " name";

		if (case_sen)
			tmp += " GLOB";
		else
			tmp += " LIKE";

		tmp += " '";

		if (bitlook(flag, SQL_search_flag_head))
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += content;

		if (bitlook(flag, SQL_search_flag_tail))
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += "'";

		if (bitlook(flag, SQL_search_flag_summary))
			tmp += " AND";
	}

	if (bitlook(flag, SQL_search_flag_summary))
	{
		tmp += " summary";

		if (case_sen)
			tmp += " GLOB";
		else
			tmp += " LIKE";

		tmp += " '";

		if (bitlook(flag, SQL_search_flag_head))
		{
			if (case_sen)
				tmp += "*";
			else
				tmp += "%";
		}

		tmp += content;

		if (bitlook(flag, SQL_search_flag_tail))
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
	tmp =  "SELECT ID,name,author,translator,publisher,summary,author_intro,isbn,price,binding FROM book WHERE ID = ";
	tmp += ID;
	tmp += ";";
	rc = sqlite3_exec(db, tmp.c_str(), outall, NULL, &errmsg);

	if (rc)
	{
		sqlite3_close(db);
		errr;
		return -3;
	}

	sqlite3_close(db);
	return 0;
}
}
