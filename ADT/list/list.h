/*list.h -- 链表ADT*/
#ifndef LIST_H_
#define LIST_H_

typedef int Item; // 每个结点的值类型

void Item_init(Item * pitem); // 给Item赋初值

void Item_copy(Item * pitem, Item const * pitem_src); // 给Item赋值

int Item_get(Item * pitem); // 从输入中获取Item的值

typedef struct node//一个结点的结构
{
    Item item;
    struct node * next;
} Node;

typedef Node * List; //链表类型

void List_init(List * plist); // 构建头指针

void List_free(List * plist); // 释放链表

void List_reset(List * plist); // 清空链表里所有的Item的值

int List_isEmpty(List list); //判断链表是否为空

int List_size(List list); //计算链表长度（包含头指针）

Node * List_Header(List list); // 链表的头结点

Node * List_Tailer(List list); // 链表当前的最后一个结点

Node * List_at(List * plist, unsigned int index); // 链表中某一索引（类似数组）对应的结点

Node * List_find(List list, Item const * pitem); //查找链表中是否有某一值,返回最前的结点的地址

void List_delete(List * plist, Node * pos); // 删除某一结点

void List_insert(List * plist, Node * pos, Item const * pitem); // 在某一结点后插入一个新结点

Node * List_succ(List * plist, Node * pos); // 某一结点的下一结点

Node * List_prev(List * plist, Node * pos); // 某一结点的上一结点

void List_Traverse(List list, void (*pfun)(Item * pitem)); //对每个结点执行pfun指向的函数

#endif