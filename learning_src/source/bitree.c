/**
 * @filename: bitree.c
 *
 * @author: QinYUN575
 *
 * @create: 2019/12/01
 *
 *
 */
#include "bitree.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief initialize binary tree.
 *
 * @attention None
 *
 * @param[in]   tree    pointer to initialize of the binary tree
 * @param[in]   destroy pointer to the destroy handler of the bitree
 *
 * @return None
 *
 */
void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    /* Initalize the binary tree. */

    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;

    return;
}

/**
 * @brief destroy binary tree.
 *
 * @attention None
 *
 * @param[in]   tree    pointer to destroy of the binary tree
 *
 * @return None
 */
void bitree_destroy(BiTree *tree)
{
    /* Remove all the nodes from the tree. */
    bitree_rem_left(tree, NULL);

    /* No operations are allowed now, but clear the structure as a precaution. */
    memset(tree, 0, sizeof(BiTree));
}

/**
 * @brief insert node into binary tree as left node
 *
 * @attention None
 *
 * @param[in]   tree    pointer to left to the binary tree
 * @param[in]   node    pointer to left node
 * @param[in]   data    pointer to data as left node data
 *
 * @return errcode
 * @retval  0, insertion successful
 *          -1, insertion fail
 *
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    /* Determine where to insert the node. */
    if (node == NULL)
    {
        /* Allow insertion at the root only in an empty tree. */
        if (bitree_size(tree) > 0)
        {
            return -1;
        }
        position = &tree->root;
    }
    else
    {
        /* Normally allow insertion only at the end of a branch. */
        if (bitree_left(node) != NULL)
        {
            return -1;
        }
        position = &node->left;
    }

    /* Allocate storage for the node. */
    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
    {
        return -1;
    }

    /* Insert the node into the tree. */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    /* Adjust the size of the tree to account for the inserted node. */
    tree->size++;

    return 0;
}

/**
 * @brief insert node into binary tree as right node
 *
 * @attention None
 *
 * @param[in]   tree    pointer to right to the binary tree
 * @param[in]   node    pointer to right node
 * @param[in]   data    pointer to data as right node data
 *
 * @return None
 *
 * @return errcode
 * @retval  0, insertion successful
 *          -1, insertion fail
 *
 */
void bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    /* Determine where to insert the node. */
    if (node == NULL)
    {
        /* Allow insertion at the root only in an empty tree. */
        if (bitree_size(tree) > 0)
        {
            return -1;
        }
        position = &tree->root;
    }
    else
    {
        if (bitree_right(node) != NULL)
        {
            return -1;
        }
        position = &node->right;
    }
    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
    {
        return -1;
    }

    /* Insert the node into the tree. */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    /* Adujst the size of the tree to account for the inserted node. */
    tree->size++;

    return 0;
}

/**
 * @brief remove left for binray tree
 *
 * @attention None
 *
 * @param[in]   tree    pointer to right to the binary node
 * @param[in]   node    pointer to righr node
 *
 * @return None
 *
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    /* Do not allow removal from an empty tree. */
    if (bitree_size(tree) == 0)
    {
        return;
    }

    /* Determine where to remove nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->left;
    }

    /* Remove the nodes. */
    if (*position != NULL)
    {
        bitree_rem_left(tree, node);
        bitree_rem_right(tree, node);

        if (tree->destroy != NULL)
        {
            /* Call a user-define function to free dynamically allocated data. */
            tree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;

        /* Adjust the size of the tree to account for the removed node. */
        tree->size--;
    }
    return;
}

/**
 * @brief remove node for binary tree
 *
 * @param[in]   tree    pointer to right to the binary tree
 * @param[in]   node    pointer to right node
 *
 * @return None
 *
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    /* Do not allow remove form an empty tree. */
    if (bitree_size(tree) == 0)
    {
        return;
    }

    /* Determine where to remove nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->right;
    }

    if (*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            /* Call a user-defined function to free dynamically allocated data. */
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        /* Adjust the size of the tree to account for the removed node. */
        tree->size--;
    }
    return;
}

/**
 * @brief merge left tree and right tree to new tree
 *
 * @param[in]   tree    pointer with new binary tree
 * @param[in]   tree    pointer of left tree
 * @param[in]   tree    pointer of tight tree
 *
 * @return      result code
 *
 * @retval      0, merge successful
 *              -1, merge fail
 *
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    /* Initialize the merge tree. */
    bitree_init(merge, left->destroy);

    /* Insert the data for the root node of the merged tree. */
    if (bitree_ins_left(merge, NULL, data) != 0)
    {
        bitree_destroy(merge);
        return -1;
    }

    /* Merge the two binary trees into a single binary tree. */
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);

    /* Adjust the size of the new binary tree. */
    merge->size = merge->size + bitree_size(left) + bitree_size(right);

    /* Do not let the original trees access the merged nodes. */
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}
