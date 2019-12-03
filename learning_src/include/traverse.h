/**
 * @filename: traverse.h
 *
 * @author: QinYUN575
 *
 * @create: 2019/12/03
 *
 *
 */
#ifndef __TRAVERSE_H__
#define __TRAVERSE_H__

#include "list.h"
#include "traverse.h"


/* Public Interface */
int preorder(const BiTreeNode *node, List *list);
int inorder(const BiTreeNode *node, List *list);
int postorder(const BiTreeNode *node, List *list);

#endif
