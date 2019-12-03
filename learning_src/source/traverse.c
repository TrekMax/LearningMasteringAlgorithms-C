/**
 * @filename: traverse.c
 *
 * @author: QinYUN575
 *
 * @create: 2019/12/03
 *
 *
 */
#include "list.h"
#include "bitree.h"
#include <stdlib.h>

/**
 * @brief preorder tarverse binary tree
 *
 * @param[in]   node    pointer to binary tree root node
 * @param[in]   list    pointer to list
 *
 * @return None
 *
 * @retval  0,  traverse succcessful
 *          -1, traverse fail
 */
int preorder(const BiTreeNode *node, List *list)
{
    /* Load the list with a preorder listing of the tree. */
    if (!bitree_is_eob(node))
    {
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
        {
            return -1;
        }

        if (!bitree_is_eob(bitree_left(node)))
        {
            if (preorder(bitree_left(node), list) != 0)
            {
                return -1;
            }
        }
        if (!bitree_is_eob(bitree_right(node)))
        {
            if (preorder(bitree_right(node), list) != 0)
            {
                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief inorder tarverse binary tree
 *
 * @param[in]   node    pointer to binary tree root node
 * @param[in]   list    pointer to list
 *
 * @return None
 *
 * @retval  0,  traverse succcessful
 *          -1, traverse fail
 */
int inorder(const BiTreeNode *node, List *list)
{
    /* Load the list with a in-order list to tree */
    if (!bitree_is_eob(node))
    {
        if (!bitree_is_eob(bitree_left(node)))
        {
            if (!inorder(bitree_left(node), list) != 0)
            {
                return -1;
            }
        }

        if ((list_ins_next(list, list_tail(list), bitree_data(node))) != 0)
        {
            return -1;
        }

        if (!bitree_is_eob(bitree_right(node)))
        {
            if (!inorder(bitree_right(node), list) != 0)
            {
                return -1;
            }
        }
    }
    return 0;
}

/**
 * @brief postorder tarverse binary tree
 *
 * @param[in]   node    pointer to binary tree root node
 * @param[in]   list    pointer to list
 *
 * @return None
 *
 * @retval  0,  traverse succcessful
 *          -1, traverse fail
 */
int postorder(const BiTreeNode *node, List *list)
{
    if (!bitree_is_eob(node))
    {
        return -1;

        if (bitree_is_eob(bitree_left(node)))
        {
            if (postorder(bitree_left(node), list))
            {
                return -1;
            }
        }
        if (bitree_is_eob(bitree_right(node)))
        {
            if (postorder(bitree_right(node), list))
            {
                return -1;
            }
        }

        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
        {
            return -1;
        }
    }

    return 0;
}
