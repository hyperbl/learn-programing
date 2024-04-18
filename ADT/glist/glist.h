/*glist.c -- 广义表ADT*/
/*相对与列表，广义表的每一个结点都可以是原子类型或者子列表*/
#ifndef GLIST_H_
#define GLIST_H_

typedef enum{success, failure} Status;
typedef int AtomType;  // 定义原子结点类型
typedef enum{ATOM, LIST} ElemTag;  // 结点里的元素标签，ATOM:原子; LIST:子表
typedef struct node
{
    ElemTag tag;    // 用于区分原子结点和表结点
    union
    {
        AtomType atom;     // 原子结点的值
        struct node * list;      // 表结点的头指针
    };
    struct node * next;       // 指向下一元素结点
} Node;
typedef Node * Glist;

// 以下定义了一些函数操作，不少函数的具体实现都依赖于递归

// 创建空的广义表L
Glist * Glist_init();

// 由src创建广义表
Glist * Glist_create(char * src);

// 销毁广义表
Status Glist_del(Glist * pL);

// 有广义表L复制到广义表T
Status Glist_cpy(Glist * pT, Glist L);

// 求广义表的元素个数
int Glist_len(Glist L);

// 求广义表的深度
int Glist_dep(Glist L);

// 判断广义表是否为空
int Glist_isEmpty(Glist L);

// 获取广义表的头
Node * Glist_head(Glist L);

// 获取广义表的尾
Node * Glist_tail(Glist L);

// 插入元素e作为广义表L 的第一元素
Status Glist_push(Glist * pL);

// 删除广义表L 的第一元素, 并用e返回其值
Status Glist_pop(Glist * pL);

// 遍历广义表L，用函数pf处理每个元素
Status Glist_traverse(Glist * pL, AtomType (*pf)(AtomType atom));

#endif