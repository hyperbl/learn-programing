#include <stdlib.h>
#include "bin_tree.h"

#ifdef _LINK_BIN_TREE_
BinTree BinTree_init()
{
    BinTree BT = (BinTree) malloc(sizeof (BTNode));
    elem_init(BT->elem);
    BT->left = BT->right = NULL;
    return BT;
}

void BinTree_free(BinTree BT)
{
    if (BT)
    {
        BinTree_free(BT->left);
        elem_free(BT->elem);
        free(BT);
        BinTree_free(BT->right);
    }
    else;
}

int BinTree_depth(BinTree BT)
{
    BTNode * cur = BT;
    if (cur)
    {
        int left_depth = BinTree_depth(cur->left);
        int right_depth = BinTree_depth(cur->right);
        if (left_depth < right_depth)
            return left_depth + 1;
        else
            return right_depth + 1;
    }
    else
        return 0;
}

void BinTree_preOrderTraverse(BinTree BT, void (*pf)(ElementType * e))
{
    BTNode * cur = BT;
    if (cur)
    {
        pf(cur->elem);
        BinTree_preOrderTraverse(cur->left, pf);
        BinTree_preOrderTraverse(cur->right, pf);
    }
    else;
}

void BinTree_inOrderTraverse(BinTree BT, void (*pf)(ElementType * e))
{
    BTNode * cur = BT;
    if (cur)
    {
        BinTree_inOrderTraverse(cur->left, pf);
        pf(cur->elem);
        BinTree_inOrderTraverse(cur->right, pf);
    }
    else;
}

void BinTree_postOrderTraverse(BinTree BT, void (*pf)(ElementType * e))
{
    BTNode * cur = BT;
    if (cur)
    {
        BinTree_postOrderTraverse(cur->left, pf);
        BinTree_postOrderTraverse(cur->right, pf);
        pf(cur->elem);
    }
    else;
}
#else
#ifdef _ARRAY_BIN_TREE_
BinTree BinTree_init(int maxElements)
{
    BinTree BT;
    if (maxElements > MIN_TREE_CAPATICITY)
    {
        BT = (BinTree) malloc(sizeof (binTree));
        if (BT)
        {
            BT->elems = (ElementType *) malloc(sizeof (ElementType) * 
                                                    (maxElements + 1));
            BT->capacity = maxElements;
            BT->size = 0;
            elem_init(BT->elems);
        }
    }
    return BT;
}

void BinTree_free(BinTree BT)
{
    if (BT)
    {
        for (int i = 0; i <= BT->capacity; i++)
        {
            elem_free(BT->elems + i);
            free(BT->elems + i);
        }
    }
}
#endif
#endif