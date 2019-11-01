/**
 * @filename: list.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/10/30
 * 
 * 
 * 
 */
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * 链表初始化
 * 
 * @param    List *list 需要初始化的链表
 * 
 * @param   void (*destroy)(void *data) 析构函数
 * 
 */
void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;

    list->head = NULL;
    list->tail = NULL;

    return;
}

/**
 * 析构函数
 * 
 * @param List *list 指定操作的链表
 * 
 */
void list_destroy(List *list)
{
    void *data;
    /* 移除每一个节点 */
    while (list_size(list) > 0)
    {
        if (list_rem_next(list, NULL, (void **)&data) == 0 
            && list->destroy != NULL)
        {
            // 调用用户定义的函数, 释放动态分配的数据
            list->destroy(data);
        }
    }

    /* 现在不允许任何操作,但需要注意清除链表结数据 */
    memset(list, 0, sizeof(List));
    return;
}

/**
 * 在 List 指定的链表中 element 后面插入一个新节点,
 * 如果 element 设置为 NULL,则把新节点插入到链表头部.
 * 
 * 
 * @param List *list 指定操作的链表
 * 
 * @param ListElmt *element 定义节点
 * 
 * @param const void *data 插入节点的数据
 * 
 */
int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;

    /* 为新节点申请空间 */
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
    {
        return -1;
    }

    /* 将节点插入到链表中 */
    new_element->data = (void *)data;
    if (element == NULL)
    {
        /* 将节点插入到链表头 */
        if (list_size(list) == 0)
        {
            list->tail = new_element;
        }

        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        /* 将节点插入到链表尾部 */
        if (element->next == NULL)
        {
            list->tail = new_element;
        }

        new_element->next = element->next;
        element->next = new_element;
    }
    /* 调整链表大小 */
    list->size++;
    return 0;
}

/**
 * 移除由 list 指定的链表中 element 之后的那个节点,
 * 如果 element 设置为 NULL, 则移除链表头节点
 * 
 * @param List *list 指定操作的链表
 * 
 * @param ListElmt *element 指定的节点
 * 
 * @param void **data 被移除节点的数据
 * 
 */
int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element;

    /* 不允许从空链表中移除节点 */
    if (list_size(list) == 0)
    {
        return -1;
    }

    /* 移除链表头节点 */
    if (element == NULL)
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1)
        {
            list->tail = NULL;
        }
    }
    else
    {
        if (element->next == NULL)
        {
            return -1;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        /* 移除链表尾部节点 */
        if (element->next == NULL)
        {
            list->tail = element;
        }
    }
    /* 释放旧节点占用的内存空间 */
    free(old_element);
    list->size--;
    return 0;
}
