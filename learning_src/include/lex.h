/**
 * @filename: lex.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/16
 * 
 * 
 * 
 */
#ifndef __LEX_H
#define __LEX_H

#include <stdlib.h>
#include "chtbl.h"

/* 定义词法分析器可识别的 token 类型 */
typedef enum Token_
{
    lexit,
    error,
    digit,
    other
} Token;

/* Public interface */
Token lex(const char *istream, CHTbl *symtbl);

#endif