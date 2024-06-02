/* AVLTree.h -- 二叉平衡树ADT */
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "../element.h"

// 相比于一般的二叉树，结点还存储了当前结点的高度
typedef struct AVLNode AVLNode;
struct AVLNode
{
    ElementType elem;
    int height;
    AVLNode * left;
    AVLNode * right;
};
typedef AVLNode * AVLTree;

// 初始化函数
AVLTree AVL_init();

// 删除AVL树
void AVL_del(AVLTree AVL);

// 获取当前结点高度
int AVL_height(AVLTree AVL);

// AVL树结点的插入
AVLTree AVL_insert(AVLTree AVL, ElementType * e);

// AVL树结点的删除
AVLTree AVL_remove(AVLTree AVL, ElementType * e);

// 输出AVL树
void AVL_show(AVLTree AVL);

#endif