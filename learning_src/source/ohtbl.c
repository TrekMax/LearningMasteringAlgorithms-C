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
#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

/* 为腾出的元素保留哨兵内存地址 */
static char vacated;

int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *data), int (*h2)(const void *data),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(const void *data))
{
    int i;
    if (htbl->size = (void **)malloc(positions * sizeof(void *)) == NULL)
    {
        return -1;
    }

    /* 遍历每个位置 */
    htbl->positions = positions;
    for (i = 0; i < htbl->positions; i++)
    {
        htbl->table[i] = NULL;
    }

    /* 将腾出的成员设置为此前保留的哨兵内存地址 */
    htbl->vacated = &vacated;

    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;

    /* 初始化元素数量 */
    htbl->size = 0;

    return 0;
}

/**
 * 销毁哈希表
 * 
 * @param    OHTbl *htbl 指定要销毁的哈希表
 * 
 * 
 */
void ohtbl_destroy(OHTbl *htbl)
{
    int i;
    if (htbl->destroy != NULL)
    {
        for (i = 0; i < htbl->size; i++)
        {
            if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
            {
                htbl->destroy(htbl->table[i]);
            }
        }
    }

    free(htbl->table);

    memset(htbl, 0, sizeof(OHTbl));
    return;
}

/**
 * 插入哈希元素
 * 
 * @param    OHTbl *htbl 指定向该哈希表中插入元素
 * 
 * @param   void **data 需要插入的元素数据
 * 
 */
int ohtbl_insert(OHTbl *htbl, void *data)
{
    void *temp;
    int position, i;
    if (htbl->size == htbl->positions)
    {
        return -1;
    }

    /* 查找元素是否已存在 */
    temp = (void *)data;
    if (ohtbl_lookup(htbl, &temp) == 0)
    {
        return 1;
    }

    for (i = 0; i < htbl->positions; i++)
    {
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;

        if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated)
        {
            htbl->table[position] = (void *)data;
            htbl->size++;
            return 0;
        }
    }
    return -1;
}

/**
 * 移除哈希元素
 * 
 * @param    OHTbl *htbl 指定从该哈希表中移除元素
 * 
 * @param   void **data 需要移除的元素数据
 * 
 */
int ohtbl_remove(OHTbl *htbl, void **data)
{
    int position, i;
    for (i = 0; i < htbl->positions; i++)
    {
        /* 哈希键 */
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        if (htbl->table[position] == NULL)
        {
            return -1;
        }
        else if (htbl->table[position] == htbl->vacated)
        {
            continue;
        }
        else if (htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size--;
            return 0;
        }
    }

    return -1;
}

/**
 * 查找哈希元素
 * 
 * @param    OHTbl *htbl 指定查找的哈希表
 * 
 * @param   void **data 查找的元素数据
 * 
 */
int ohtbl_lookup(OHTbl *htbl, void **data)
{
    int position, i;
    for (i = 0; i < htbl->positions; i++)
    {
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        if (htbl->table[position] == NULL)
        {
            return -1;
        }
        else if (htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            return 0;
        }
    }
    return -1;
}
