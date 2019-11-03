/**
 * @filename: ex_list.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

typedef struct student_
{
    int sn_number;
    int score;
} student_t;

void print_data(char *buf, int buf_len, void *data)
{
    student_t i = *(student_t *)data;
    snprintf(buf, buf_len, "STU[%02d]:%2d", i.sn_number, i.score);
}

/**
 * 使用自定义打印格式,打印链表节点数据
 * 
 * @param List *list 指定需要打印的链表
 * 
 * @param void (*print_data)(char *buf, int buf_len, void *data) 自定义打印函数
 * 
 */
void print_list(List *list, void (*print_data)(char *buf, int buf_len, void *data))
{
    char buf[20];
    int i = 0;
    ListElmt *element;
    if (list_size(list) == 0)
    {
        printf("\t->链表为空\r\n");
        return;
    }
    element = list_head(list);
    while (1)
    {
        print_data(buf, sizeof(buf), element->data);
        fprintf(stdout, "\tlist[%2d]->data:{%s}\r\n", //d]",
                i++, buf);                            //*((int*)element->data));
        if (list_is_tail(element))
        {
            break;
        }
        element = list_next(element);
    }
}

int main(void)
{
    List list;
    ListElmt *element;
    int i, log_c = 0;
    student_t *data;

    /* ---------------------------------------------------------------------- */
    /* 设置随机数种子 */
    srand((unsigned)time(NULL));

    /* 初始化链表 */
    printf("[%d|%d]初始化链表\r\n", __LINE__, log_c++);
    list_init(&list, free);

    printf("[%d|%d]初始化测试数据\r\n", __LINE__, log_c++);
    element = list_head(&list);
    for (i = 0; i <= 10; i++)
    {
        if ((data = (student_t *)malloc(sizeof(student_t))) == NULL)
        {
            printf("[%d|%d]申请空间失败[%d]\r\n", __LINE__, log_c++, i);
            /* 内存空间申请失败,退出程序前,销毁链表释放空间 */
            list_destroy(&list);
            return -1;
        }

        data->sn_number = i;
        data->score = rand() % 100 + 1;

        /* 插入链表头 */
        if (list_ins_next(&list, list_tail(&list), data) != 0)
        {
            printf("[%d|%d]插入节点失败[%d]\r\n", __LINE__, log_c++, i);
            /* 退出程序前,销毁链表释放空间 */
            free(data);
            list_destroy(&list);
            return 1;
        }
    }
    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);

    /* ---------------------------------------------------------------------- */
    /* 重新指向头节点 */
    element = list_head(&list);
    for (i = 0; i < 3; i++)
    {
        element = list_next(element);
    }
    data = list_next(element)->data;
    printf("[%d|%d]移除链表节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_rem_next(&list, element, (void **)&data) != 0)
    {
        /* 插入节点失败,退出程序前,销毁链表释放空间 */
        free(data);
        list_destroy(&list);
        return 1;
    }
    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);

    /* ---------------------------------------------------------------------- */

    if ((data = (student_t *)malloc(sizeof(student_t))) == NULL)
    {
        printf("[%d|%d]申请空间失败[%d]\r\n", __LINE__, log_c++, i);
        /* 内存空间申请失败,退出程序前,销毁链表释放空间 */
        list_destroy(&list);
        return -1;
    }
    data->sn_number = 12;
    data->score = 60;

    printf("[%d|%d]插入链表节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_ins_next(&list, element, (void *)data) != 0)
    {
        /* 插入节点失败,退出程序前,销毁链表释放空间 */
        free(data);
        list_destroy(&list);
        return 1;
    }

    if ((data = (student_t *)malloc(sizeof(student_t))) == NULL)
    {
        printf("[%d|%d]申请空间失败[%d]\r\n", __LINE__, log_c++, i);
        /* 内存空间申请失败,退出程序前,销毁链表释放空间 */
        list_destroy(&list);
        return -1;
    }
    data->sn_number = 11;
    data->score = 89;

    printf("[%d|%d]插入链表节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_ins_next(&list, element, (void *)data) != 0)
    {
        /* 插入节点失败,退出程序前,销毁链表释放空间 */
        free(data);
        list_destroy(&list);
        return 1;
    }

    if ((data = (student_t *)malloc(sizeof(student_t))) == NULL)
    {
        printf("[%d|%d]申请空间失败[%d]\r\n", __LINE__, log_c++, i);
        return -1;
    }
    data->sn_number = 20;
    data->score = 85;

    printf("[%d|%d]插入链表尾节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_ins_next(&list, list_tail(&list), (void *)data) != 0)
    {
        /* 插入节点失败,退出程序前,销毁链表释放空间 */
        free(data);
        list_destroy(&list);
        return 1;
    }

    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);
    
    /* ---------------------------------------------------------------------- */
    data = list_head(&list)->data;
    printf("[%d|%d]移除链表头节点节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_rem_next(&list, NULL, (void **)&data) != 0)
    {
        /* 移除节点失败,退出程序前,销毁链表释放空间 */
        list_destroy(&list);
        return 1;
    }
    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);

    /* ---------------------------------------------------------------------- */
    if ((data = (student_t *)malloc(sizeof(student_t))) == NULL)
    {
        printf("[%d|%d]申请空间失败[%d]\r\n", __LINE__, log_c++, i);
        return -1;
    }
    data->sn_number = 45;
    data->score = 99;

    printf("[%d|%d]插入链表头节点:STU[%d]\r\n", __LINE__, log_c++, data->sn_number);
    if (list_ins_next(&list, NULL, (void *)data) != 0)
    {
        /* 插入节点失败,退出程序前,销毁链表释放空间 */
        free(data);
        list_destroy(&list);
        return 1;
    }

    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);
    
    /* ---------------------------------------------------------------------- */
    i = list_is_head(&list, list_head(&list));
    printf("[%d|%d]Testing list_is_head...Value=%d (1=OK)\n", __LINE__, log_c++, i);
    i = list_is_head(&list, list_tail(&list));
    printf("[%d|%d]Testing list_is_head...Value=%d (0=OK)\n", __LINE__, log_c++, i);
    i = list_is_tail(list_tail(&list));
    printf("[%d|%d]Testing list_is_tail...Value=%d (1=OK)\n", __LINE__, log_c++, i);
    i = list_is_tail(list_head(&list));
    printf("[%d|%d]Testing list_is_tail...Value=%d (0=OK)\n", __LINE__, log_c++, i);
    /* ---------------------------------------------------------------------- */
    /* 销毁链表 */
    printf("[%d|%d]销毁链表\r\n", __LINE__, log_c++);
    list_destroy(&list);

    /* 打印链表数据 */
    printf("[%d|%d]打印链表\r\n", __LINE__, log_c++);
    print_list(&list, print_data);

    return 0;
}