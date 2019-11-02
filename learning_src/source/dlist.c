/**
 * @filename: dlist.c
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

#include "dlist.h"

/**
 * 初始化双向链表
 * 
 * @param DList *list 指定要初始化的链表
 * 
 * @param DList void (*destroy)(void *data) 指定用于销毁链表的操作
 * 
 */
void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;

    list->head = NULL;
    list->tail = NULL;

    return;
}

/**
 * 指定要销毁的双向链表
 * 
 * @param DList *list 指定要销毁的链表
 * 
 */
void dlist_destroy(DList *list)
{
    void *data;

    /* 移除所有节点 */
    while (dlist_size(list) > 0)
    {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0
            && list->destroy != NULL)
        {
            /* 使用用户定义的销毁函数,移除节点数据 */
            list->destroy(data);
        }
    }

    /* 清除链表结构 */
    memset(list, 0, sizeof(DList));
    return;
}

/**
 * 向指定双向链表 list 节点 element 之后插入一个新节点,
 * 如果 element 为 NULL, 则向链表头节点插入新节点
 * 
 * @param DList *list 指定要销毁的链表
 * 
 * @param DListElmt *elemnt 指定要新节点要在其之后插入的节点
 * 
 * @param const void *data 要插入新节点的数据
 * 
 */
int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    /* element 为 NULL 时,仅当链表也为空时才允许插入 */
    if (element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }
    /* 为插入的新节点的抽象数据类型申请内存空间 */
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
    {
        return -1;
    }

    /* 插入新节点到链表中 */
    new_element->data = (void *)data;
    if (dlist_size(list) == 0)
    {
        /* 链表为空时的插入操作 */
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        /* 链表不为空时的插入操作 */
        new_element->next = element->next;
        new_element->prev = element;
        if (element->next == NULL)
        {
            list->tail = new_element;
        }
        else
        {
            element->next->prev = new_element;
        }
        element->next = new_element;
    }

    list->size++;
    return 0;
}

/**
 * 向指定双向链表 list 节点 element 之前插入一个新节点,
 * 如果 element 为 NULL, 则向链表头节点插入新节点
 * 
 * @param DList *list 指定要销毁的链表
 * 
 * @param DListElmt *elemnt 指定要新节点要在其之前插入的节点
 * 
 * @param const void *data 要插入新节点的数据
 * 
 */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    /* element 为 NULL 时,仅当链表也为空时才允许插入  */
    if (element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }
    /* 为新节点的抽象数据类型申请内存空间 */
    if ((new_element = (DListElmt *)maclloc(sizeof(DListElmt))) == NULL)
    {
        return -1;
    }

    /* 插入新节点到链表中 */
    new_element->data = (void *)data;
    if (dlist_size(list) == 0)
    {
        /* 当链表为空时的插入操作 */
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        /* 链表不为空时的插入操作 */
        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL)
        {
            list->head = new_element;
        }
        else
        {
            element->prev->next = new_element;
        }

        element->prev = new_element;
    }
    list->size++;
    return 0;
}

/**
 * 从链表 list 中移除指定节点 element
 * 
 * @param DList *list 指定的链表
 * 
 * @param DListElmt *elemnt 指定要移除的节点
 * 
 * @param const void *data 被移除节点的数据域
 * 
 */
int dlist_remove(DList *list, DListElmt *element, void **data)
{
    if (element == NULL || dlist_size(list) == 0)
    {
        return -1;
    }

    *data = element->data;

    if (element == list->head)
    {
        /* 从链表头移除节点 */
        list->head = element->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        else
        {
            element->next->prev = NULL;
        }
    }
    else
    {
        /* 从非链表头移除节点 */
        element->prev->next = element->next;
        if (element->next == NULL)
        {
            list->tail = element->prev;
        }
        else
        {
            element->next->prev = element->prev;
        }
    }

    free(element);
    list->size--;
    return 0;
}