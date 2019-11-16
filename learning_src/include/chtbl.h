/**
 * @filename: chtbl.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/16
 * 
 * 
 * 
 */
#ifndef __CHTBL_H
#define __CHTBL_H

#include <stdlib.h>

#include "list.h"

/* 定义链式哈希表抽象数据结构 */
typedef struct CHTBL_
{
    int buckets;

    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    int (*destroy)(void *data);

    int size;
    List *table;
} CHTbl;

/* Public Interface */
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), 
    int (*match)(const void *key1, const void *key2),
    void (*destroy)(void *data));
void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(CHTbl *htbl, void **data);

#define chtbl_size(htbl)    ((htbl)->size)

#endif

