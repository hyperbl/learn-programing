/*bin_tree.h -- 二叉树ADT*/
#ifndef BIN_TREE_H_
#define BIN_TREE_H_

typedef int Item;

typedef struct node
{
    Item item;
    struct node * left;
    struct node * right;
}Node;

typedef Node * BinTree;

#endif