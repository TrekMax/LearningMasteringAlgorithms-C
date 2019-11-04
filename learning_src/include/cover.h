/**
 * @filename: cover.h
 * 
 * @author: QinYUN575
 * 
 * @create date: 2019/11/4
 * 
 * 
 * 
 */
#ifndef COVER_H
#define COVER_H

#include <stdlib.h>
#include "set.h"

typedef struct KSet_
{
    void *key;
    Set set;
} KSet;

/* Public Interface */
int cover(Set *members, Set *subset, Set *covering);

#endif // COVER_H