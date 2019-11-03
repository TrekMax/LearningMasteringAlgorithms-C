/**
 * @filename: events.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "event.h"
#include "events.h"

/**
 * 事件接收
 * 
 */
int receive_event(Queue *events, const Event *event)
{
    Event *new_event;
    if ((new_event = (Event *)malloc(sizeof(Event))) == 0)
    {
        return -1;
    }
    memcpy(new_event, event, sizeof(Event));

    if (queue_enqueue(events, event) != 0)
    {
        return -1;
    }
    return 0;
}

/**
 * 事件处理
 * 
 */
int process_event(Queue *events, int (*dispatch)(Event *event))
{
    Event *event;
    if (queue_size(events) == 0)
    {
        return -1;
    }
    else
    {
        if (queue_dequeue(events, (void **)&event) == 0)
        {
            return -1;
        }
        else
        {
            if (dispatch != NULL)
            {
                dispatch(event);
            }
            free(event);
        }
    }
    return 0;
}