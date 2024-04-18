/*bin_tree.h -- 二叉树ADT*/
#ifndef BIN_TREE_H_
#define BIN_TREE_H_

typedef int Item;

typedef struct node
{
    Item item;
    struct node * left;
    struct node * right;
}BTNode;

typedef BTNode * BinTree;

// 以下为二叉树的一些函数的原型
// 初始化二叉树
BinTree BinTree_init();

// 删除二叉树
void BinTree_del(BinTree BT);

// 获取树的深度
int BinTree_depth(BinTree BT);

// 树的先序遍历
void BinTree_preOrderTraverse(BinTree BT, void (*pf)(Item * pitem));

// 树的中序遍历
void BinTree_inOrderTraverse(BinTree BT, void (*pf)(Item * pitem));

// 树的后序遍历
void BinTree_postOrderTraverse(BinTree BT, void (*pf)(Item * pitem));

#endif