/**
 * @filename: events.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#ifndef EVENTS_H
#define EVENTS_H

#include <stdio.h>
#include "queue.h"
#include "event.h"

int receive(Queue *events, const Event *event);
int process_event(Queue *events, int (*dispatch)(Event *event));

#endif // EVENTS_H
