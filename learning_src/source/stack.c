/**
 * @filename: stack.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/3
 * 
 * 
 * 
 */
#include <stdio.h>
#include "list.h"
#include "stack.h"

/**
 * 入栈操作
 * 
 * @param Stack *stack 指定栈
 * 
 * @param void *data 入栈数据
 * 
 */
int stack_push(Stack *stack, void *data)
{
    return list_ins_next(stack, NULL, data);
}

/**
 * 入栈操作
 * 
 * @param Stack *stack 指定栈
 * 
 * @param void *data 入栈数据
 * 
 */
int stack_pop(Stack *stack, void **data)
{
    return list_rem_next(stack, NULL, data);
}
