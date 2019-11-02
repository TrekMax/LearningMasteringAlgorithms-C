/**
 * @filename: page.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/2
 * 
 * 
 * 
 */
#ifndef PAGE_H
#define PAGE_H

#include "clist.h"

/**
 * 定义页表结构信息
 * 
 */
typedef struct Page_
{
    int number;
    int reference;
} Page;

/* Public Interface */
int replace_page(CListElmt **current);

#endif