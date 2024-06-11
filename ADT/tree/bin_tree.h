/*bin_tree.h -- 二叉树ADT*/
#ifndef BIN_TREE_H_
#define BIN_TREE_H_
#include "../element.h"

// 使用链式存储
#define _LINK_BIN_TREE_

// 使用顺序存储
#ifdef _ARRAY_BIN_TREE_   
#undef _LINK_BIN_TREE_
#endif

#ifdef _LINK_BIN_TREE_
typedef struct node
{
    ElementType * elem;
    struct node * left;
    struct node * right;
}BTNode;

typedef BTNode * BinTree;
#else
#define MIN_TREE_CAPATICITY (0)
typedef struct binTree
{
    int capacity;    // 二叉树的最大结点数
    int size;        // 当前整个二叉树的大小
    ElementType * elems; // 元素数组
} binTree;

typedef binTree * BinTree;
#endif

// 以下为二叉树的一些函数的原型
// 初始化二叉树
#ifdef _LINK_BIN_TREE_
BinTree BinTree_init();
#else
#ifdef _ARRAY_BIN_TREE_
BinTree BinTree_init(int maxElements);
#endif
#endif
// 删除二叉树
void BinTree_free(BinTree BT);

// 获取树的深度
int BinTree_depth(BinTree BT);

// 树的先序遍历
void BinTree_preOrderTraverse(BinTree BT, void (*pf)(ElementType * e));

// 树的中序遍历
void BinTree_inOrderTraverse(BinTree BT, void (*pf)(ElementType * e));

// 树的后序遍历
void BinTree_postOrderTraverse(BinTree BT, void (*pf)(ElementType * e));
#endif