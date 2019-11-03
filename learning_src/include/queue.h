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
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "list.h"

/* 定义队列抽象数据结构 */
typedef List Queue;

/* Public Interface */
#define queue_init list_init
#define queue_destroy list_destroy

int queue_enqueue(Queue *queue, void *data);
int queue_dequeue(Queue *queue, void **data);

#define queue_peek(queue)   ((queue)->head == NULL ? NULL : (queue)->head->data)
#define queue_size list_size


#endif // QUEUE_H