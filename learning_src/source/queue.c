/**
 * @filename: queue.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#include <stdlib.h>
#include "list.h"
#include "queue.h"

/**
 * 入队函数
 * 
 * @param Queue *queue 指定队列 
 * 
 * @param void *data 入队数据
 * 
 */
int queue_enqueue(Queue *queue, void *data)
{
    return list_ins_next(queue, list_tail(queue), data);
}

/**
 * 出队函数
 * 
 * @param Queue *queue 指定队列 
 * 
 * @param void *data 出队数据
 * 
 */
int queue_dequeue(Queue *queue, void **data)
{
    return list_rem_next(queue, NULL, data);
}
