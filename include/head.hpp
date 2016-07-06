/*************************************************************************
    > 文件名: head.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时53分14秒
    > 
 ************************************************************************/

#include <iostream>
extern "C"
{
	#include <locale.h>
	#include <libintl.h>
}
using namespace std;

#define PACKAGE "book-manage"
#define LOCALEDIR "./locale/"
#define _(x) gettext(x)

void print_main_menu();
