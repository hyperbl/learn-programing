#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

// 初始化函数
AVLTree AVL_init()
{
    return NULL;
}

// 删除AVL树
void AVL_del(AVLTree AVL)
{
    if (AVL)
    {
        AVL_del(AVL->left);
        AVL_del(AVL->right);
        elem_free(&AVL->elem);
        free(AVL);
    }
    else
        return;
}

// 获取当前结点高度
int AVL_height(AVLTree AVL)
{
    if (AVL)
        return AVL->height;
    else
        return 0;
}

// 更新的当前结点高度
static void updateHeight(AVLTree AVL)
{
    if (AVL)
    {
        int hl = AVL_height(AVL->left);
        int hr = AVL_height(AVL->right);
        AVL->height = 1 + ((hl < hr) ? hr : hl);
    }
    else
        return;
}

// RR旋转
static AVLTree singleRotateWithRight(AVLTree AVL)
{
    if (AVL)
    {
        AVLTree P2 = AVL->right;
        AVL->right = P2->left;
        P2->left = AVL;
        return P2;
    }
    else
        return AVL;
}

// LL旋转
static AVLTree singleRotateWithLeft(AVLTree AVL)
{
    if (AVL)
    {
        AVLTree P2 = AVL->left;
        AVL->left = P2->right;
        P2->right = AVL;
        return P2;
    }
    else
        return AVL;
}

// RL旋转
static AVLTree doubleRotateWithRight(AVLTree AVL)
{
    if (AVL)
    {
        AVL->right = singleRotateWithLeft(AVL->right);
        return singleRotateWithRight(AVL);
    }
    else
        return AVL;
}

// LR旋转
static AVLTree doubleRotateWithLeft(AVLTree AVL)
{
    if (AVL)
    {
        AVL->left = singleRotateWithRight(AVL->left);
        return singleRotateWithLeft(AVL);
    }
    else
        return AVL;
}

// AVL树结点的插入
AVLTree AVL_insert(AVLTree AVL, ElementType * e)
{
    if (AVL == NULL)
    {
        AVL = (AVLTree) malloc(sizeof (AVLNode));
        elem_copy(&AVL->elem, e);
        AVL->height = 1;
        AVL->left = AVL->right = 0;
        return AVL;
    }
    else
    {
        switch (elem_compare(e, &AVL->elem))
        {
            case LT : AVL->left = AVL_insert(AVL->left, e); break;
            case GT : AVL->right = AVL_insert(AVL->right, e); break;
            case EQ : return AVL;
            default : break;
        }
        int hl = AVL_height(AVL->left);
        int hr = AVL_height(AVL->right);
        if (hl - hr == 2)
        {
            switch (elem_compare(e, &AVL->left->elem))
            {
                case LT : AVL = singleRotateWithLeft(AVL); break;
                case GT : AVL = doubleRotateWithLeft(AVL); break;
                case EQ :
                default : break; 
            }
        }
        else if (hl - hr == -2)
        {
            switch (elem_compare(e, &AVL->right->elem))
            {
                case GT : AVL = singleRotateWithRight(AVL); break;
                case LT : AVL = doubleRotateWithRight(AVL); break;
                case EQ :
                default : break;
            }
        }
        updateHeight(AVL);
        return AVL;
    }
}

// AVL树结点的删除
AVLTree AVL_remove(AVLTree AVL, ElementType * e)
{
    return NULL;
}

// AVL的前序遍历
static void preOrderTraversal(AVLTree AVL)
{
    if (AVL)
    {
        elem_show(&AVL->elem);
        preOrderTraversal(AVL->left);
        preOrderTraversal(AVL->right);
    }
    else
        return;
}

// AVL的中序遍历
static void inOrderTraversal(AVLTree AVL)
{
    if (AVL)
    {
        inOrderTraversal(AVL->left);
        elem_show(&AVL->elem);
        inOrderTraversal(AVL->right);
    }
    else
        return;
}

// AVL的后序遍历
static void postOrderTraversal(AVLTree AVL)
{
    if (AVL)
    {
        postOrderTraversal(AVL->left);
        postOrderTraversal(AVL->right);
        elem_show(&AVL->elem);
    }
    else
        return;
}

// 输出AVL树
void AVL_show(AVLTree AVL)
{
    if (AVL)
    {
        printf("The pre-order traversal sequence is: ");
        preOrderTraversal(AVL); puts("");
        printf("The in-order traversal sequence is: ");
        inOrderTraversal(AVL); puts("");
        printf("The post-order traversal sequence is: ");
        postOrderTraversal(AVL); puts("");
    }
    else
        puts("Empty AVLTree");
}