#include <stdlib.h>
#include "bin_tree.h"

BinTree BinTree_init()
{
    return NULL;
}

void BinTree_del(BinTree BT)
{
    ;
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

void BinTree_preOrderTraverse(BinTree BT, void (*pf)(Item * pitem))
{
    BTNode * cur = BT;
    if (cur)
    {
        pf(&cur->item);
        BinTree_preOrderTraverse(cur->left, pf);
        BinTree_preOrderTraverse(cur->right, pf);
    }
    else;
}

void BinTree_inOrderTraverse(BinTree BT, void (*pf)(Item * pitem))
{
    BTNode * cur = BT;
    if (cur)
    {
        BinTree_inOrderTraverse(cur->left, pf);
        pf(&cur->item);
        BinTree_inOrderTraverse(cur->right, pf);
    }
    else;
}

void BinTree_postOrderTraverse(BinTree BT, void (*pf)(Item * pitem))
{
    BTNode * cur = BT;
    if (cur)
    {
        BinTree_postOrderTraverse(cur->left, pf);
        BinTree_postOrderTraverse(cur->right, pf);
        pf(&cur->item);
    }
    else;
}
