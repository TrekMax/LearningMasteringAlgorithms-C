/**
 * @filename: page.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/2
 * 
 * 
 * 
 */
#include "page.h"
#include "clist.h"

/**
 * 页表置换操作
 * 
 */
int replace_page(CListElmt **current)
{
    /* 遍历页表,直到找到需要置换的页面 */
    while (((Page *)(*current)->data)->reference != 0)
    {
        ((Page *)(*current)->data)->number = 0;
        *current = clist_next((*current));
    }
    /* 返回可以置换的页码 */
    return ((Page *)(*current)->data)->number;
}