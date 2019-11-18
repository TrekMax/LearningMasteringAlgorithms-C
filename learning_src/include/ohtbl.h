/**
 * @filename: ohtbl.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/18
 * 
 * 
 * 
 */
#ifndef __OHTBL_H
#define __OHTBL_H

#include <stdlib.h>

/* 定义开地址式抽象数据结构类型 */
typedef struct OHTbl_
{
    int positions;
    void *vacated;
    int (*h1)(const void *data);
    int (*h2)(const void *data);
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    int size;
    void **table;
} OHTbl;

/* Public Interface */
int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *data), int (*h2)(const void *data),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(const void *data));

void ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(OHTbl *htbl, void **data);

#define ohtbl_size(htbl) ((htbl)->size)

#endif