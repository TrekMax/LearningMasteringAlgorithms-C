/**
 * @filename: clist.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/1
 * 
 * 
 * 
 */
#include <stdlib.h>
#include <string.h>
#include "clist.h"

/**
 * 链表初始化
 * 
 * @param    CList *list 需要初始化的链表
 * 
 * @param   void (*destroy)(void *data) 析构函数
 * 
 */
void clist_init(CList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;

    list->head = NULL;

    return;
}

/**
 * 指定要销毁的双向链表
 * 
 * @param CList *list 指定要销毁的链表
 * 
 */
void clist_destroy(CList *list)
{
    void *data;

    while (clist_size(list) > 0)
    {
        if ((list)->destroy != NULL && clist_rem_next(list, NULL, (void *)&data))
            ;
        {
            list->destroy(data);
        }
    }

    /* 清除链表结构数据 */
    memset(list, 0, sizeof(CList));
    return;
}

/**
 * 向指定的链表 list 节点 element 之后插入新节点
 * 
 * @param CList *list 指定要操作的链表
 * 
 * @param CListElmt *element 指定要在该节点之后插入新节点
 * 
 * @param const void *data 要插入新节点的数据域
 * 
 */
int clist_ins_next(CList *list, CListElmt *element, const void *data)
{
    CListElmt *new_element;

    if ((new_element = (CListElmt *)malloc(sizeof(CListElmt))) == 0)
    {
        return -1;
    }

    new_element->data = (void *)data;
    if (clist_size(list) == 0)
    {
        /* 链表为空,指向自身 */
        new_element->next = new_element;
        list->head = new_element;
    }
    else
    {
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}

/**
 * 向指定的链表 list 节点 element 之后插入新节点
 * 
 * @param CList *list 指定要操作的链表
 * 
 * @param CListElmt *element 指定要在该节点之后插入新节点
 * 
 * @param const void *data 要插入新节点的数据域
 * 
 */
int clist_rem_next(CList *list, CListElmt *element, void **data)
{
    CListElmt *old_element;

    /*  */
    if (clist_size(list) == 0)
    {
        return -1;
    }

    *data = element->next->data;
    // NOTE: 这里不考虑 element 为 NULL 的情况
    if (element->next = element)
    {
        old_element = element->next;
        list->head = NULL;
    }
    else
    {
        old_element = element->next;
        element->next = old_element->next;
    }
    
    /* 释放节点数据结构内存空间 */
    free(old_element);
    list->size--;
    return 0;
}
