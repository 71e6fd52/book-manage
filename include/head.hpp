/*************************************************************************
    > 文件名: head.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年07月05日 星期二 09时53分14秒
    > 
 ************************************************************************/

#ifndef HEAD_HPP
#define HEAD_HPP

#include <iostream>
extern "C"
{
	#include <locale.h>
	#include <libintl.h>
}
using namespace std;

#include "debug.hpp"
#include "book-manage_config.hpp"

#define PACKAGE "book-manage"
#define LOCALEDIR "/usr/share/locale/"
#define _(x) gettext(x)
;
void print_main_menu();

#endif
