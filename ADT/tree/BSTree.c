#include "BSTree.h"
#include <stdio.h>
#include <stdlib.h>

BSTree init()
{
    BSTree BST = (Node *) malloc(sizeof (Node));
    BST->left = BST->right = NULL;
}

void del(BSTree BST)
{
    if (BST)
    {
        del(BST->left);
        del(BST->right);
        free(BST);
    }
    else return;
}

Node * find(BSTree BST, ElementType const * pelem)
{
    Node * cur = BST;
    while (cur)
    {
        switch (compare(&cur->elem, pelem))
        {
            case LT : cur = cur->right; break;
            case GT : cur = cur->left; break;
            case EQ : 
            default : break;
        }
    }
    return cur;
}

BSTree insert(BSTree BST, ElementType const * pelem)
{
    if (BST->left || BST->right)
    {
        BSTree cur = BST, prev = cur, tmp;
        while (cur)
        {
            prev = cur;
            switch (compare(&cur->elem, pelem))
            {
                case LT : cur = cur->right; break;
                case GT : cur = cur->left; break;
                case EQ : 
                default : break;
            }
        }
        if (!cur)
        {
            Node * tmp = (Node *) malloc(sizeof (Node));
            tmp->left = tmp->right = NULL;
            copy(&BST->elem, pelem);
            switch (compare(&prev->elem, pelem))
            {
                case LT : prev->right = tmp; break;
                case GT : prev->left = tmp; break;
                default : break;
            }
        }
        else;
    }
    else
        copy(&BST->elem, pelem);
    return BST;
}

BSTree remove(BSTree BST, ElementType const * pelem)
{
    BSTree cur = BST, prev = cur, tmp;
    switch (compare(&cur->elem, pelem))
    {
        case LT : cur = cur->right; break;
        case GT : cur = cur->left; break;
        case EQ : if (cur->left)
                  {
                    cur = cur->left;
                    while (cur->right)
                    {
                        prev = cur;
                        cur = cur->right;
                    }
                    prev->right = BST->right;
                    cur = BST->left;
                  }
                  else
                  {
                    cur = cur->right;
                    while (cur->left)
                    {
                        prev = cur;
                        cur = cur->left;
                    }
                    prev->left = BST->left;
                    cur = BST->right;
                  }
                  free(BST);
        default : return cur;
    }
    while (cur)
    {
        prev = cur;
        switch (compare(&cur->elem, pelem))
        {
            case LT : cur = cur->right; break;
            case GT : cur = cur->left; break;
            case EQ : 
            default : break;
        }
    }
    if (!cur)
    {
        switch (compare(&prev->elem, pelem))
        {
            case LT : prev->right = tmp = cur->left;
                      while (tmp->right)
                        tmp = tmp->right;
                      tmp->right = cur->right;
                      break;
            case GT : prev->right = tmp = cur->left;
                      while (tmp->left)
                        tmp = tmp->left;
                      tmp->left = cur->left;
                      break;
            default : break;
        }
        free(cur);
    }
    else;
    return BST;
}

// 鉴于操作的复杂性，本程序选择输出其中序遍历序列
void show(BSTree BST)
{
    if (BST)
    {
        show(BST->left);
        printf("%d ", BST->elem);
        show(BST->right);
    }
    else return;
}