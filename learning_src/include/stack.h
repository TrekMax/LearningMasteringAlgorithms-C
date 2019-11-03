/**
 * @filename: stack.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "list.h"

/* 定义栈结构抽象数据类型 */
typedef List Stack;

/* Public Interface */
#define stack_init  list_init
#define stack_destroy   list_destroy

int stack_push(Stack *stack, void *data);
int satck_pop(Stack *stack, void **data);
#define stack_peek(stack)  ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

#endif // STACK_H
