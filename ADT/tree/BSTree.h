/*BSTree.h -- 二叉查找树ADT*/
#ifndef BSTREE_H_
#define BSTREE_H_

#include <memory.h>

typedef int ElementType;

// 用于比较大小: LT -> Less Than, EQ -> Equal, GT -> Greater Than
typedef enum {LT = -1, EQ = 0, GT = 1} Order;

// 比较函数
static inline Order compare(ElementType * e1, ElementType * e2)
{
    Order ord;
    if (*e1 - *e2 < 0)
        ord = LT;
    else if (*e1 - *e2 > 0)
        ord = GT;
    else
        ord = EQ;
    return ord;
}

// 对元素的赋值函数
static inline void * copy(ElementType * e1, ElementType * e2)
{
    return memcpy(e1, e2, sizeof (ElementType));
}

typedef struct node
{
    ElementType elem;
    struct node * left;
    struct node * right;
} Node;

typedef Node * BSTree;

// 以下是关于二叉查找树的函数

// 初始化BST
BSTree init();

// 删除BST
void del(BSTree BST);

// 查找BST中的某元素
Node * find(BSTree BST, ElementType const * pelem);

// 向BST中插入元素
BSTree insert(BSTree BST, ElementType const * pelem);

// 从BST中删除元素
BSTree remove(BSTree BST, ElementType const * pelem);

// 输出BST
void show(BSTree BST);

#endif