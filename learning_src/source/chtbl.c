/**
 * @filename: chtbl.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/16
 * 
 * 
 * 
 */
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

/**
 * 初始化链式哈希表
 * 
 * 
 * 
 */
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    int i = 0;

    /* 为链式哈希表申请内存空间 */
    if ((htbl->table = (List *)malloc(sizeof(List) * buckets)) == NULL)
    {
        return -1;
    }

    /* 初始化 Buckets */
    htbl->buckets = buckets;
    for (i = 0; i < buckets; i++)
    {
        list_init(&htbl->table[i], destroy);
    }
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    htbl->size = 0;

    return 0;
}

/**
 * 销毁链式哈希表
 * 
 */
void chtbl_destroy(CHTbl *htbl)
{
    int i;
    for (i = 0; i < htbl->buckets; i++)
    {
        list_destroy(&htbl->table[i]);
    }
    free(&htbl->table);
    memset(htbl, 0, sizeof(CHTbl));
    return;
}

/**
 * 哈希操作
 * 
 * 
 */
int chtbl_insert(CHTbl *htbl, const void *data)
{
    void *temp;
    int bucket, retval;

    /* 如果数据已存在于哈希表中,则不进行操作 */
    temp = (void *)data;
    if (chtbl_lookup(htbl, &temp) == 0)
    {
        return 1;
    }

    /* 哈希键 */
    bucket = htbl->h(data) % htbl->buckets;

    /* 插入数据到 bucket 中 */
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
    {
        htbl->size++;
    }
    return retval;
}

/**
 * 移除哈希表中的元素
 * 
 */
int chtbl_remove(CHTbl *htbl, void **data)
{
    ListElmt *element, *prev;
    int bucket;

    /* 哈希键 */
    bucket = htbl->h(*data) % htbl->buckets;

    /* 在 bucket 中查找数据 */
    prev = NULL;
    for (element = list_head(&htbl->table[bucket]); element != NULL;
         element = list_next(element))
    {
        if (htbl->match(*data, list_data(element)))
        {
            /* Remove the data from the bucket. */
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0)
            {
                htbl->size--;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        prev = element;
    }
    return -1;
}

/**
 * 查找哈希表中的元素
 * 
 */
int chtbl_lookup(CHTbl *htbl, void **data)
{
    ListElmt *element;
    int bucket;

    /* 哈希键 */
    bucket = htbl->h(*data) % htbl->buckets;

    for (element = list_head(&htbl->table[bucket]); element != NULL;
         element = list_next(element))
    {
        if (htbl->match(*data, list_data(element)))
        {
            *data = list_data(element);
            return 0;
        }
    }
    /* 未找到数据 */
    return -1;
}
