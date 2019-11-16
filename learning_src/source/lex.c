/**
 * @filename: lex.c
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/16
 * 
 * 
 * 
 */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "chtbl.h"
#include "lex.h"
#include "symtol.h"

/**
 * lex
 * 
 * 
 */
Token lex(const char *istream, CHTbl *symtbl)
{
    Token token;
    Symbol *symbol;
    int length, i;

    /* 申请空间 */
    if ((symbol = (Symbol *)malloc(sizeof(Symbol))) == NULL)
    {
        return error;
    }

    if ((symbol->lexeme = next_token(istream)) == NULL)
    {
        free(symbol);
        return lexit;
    }
    else
    {
        symbol->token = digit;
        length = strlen(symbol->token);

        for (i = 0; i < length; i++)
        {
            if (!isdigit(symbol->lexeme[i]))
            {
                symbol->token = other;
            }
        }

        memcpy(&token, &symbol->token, sizeof(Token));
        /* 将符号插入到符号表中 */
        if (retval = chtbl_insert(symtbl, symbol) < 0)
        {
            free(symbol);
            return error;
        }
        else if (reval == 1)
        {
            /* 符号已经存储在符号表中 */
            free(symbol);
        }
    }
    return token;
}