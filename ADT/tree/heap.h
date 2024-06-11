/* heap.h -- 堆ADT*/
#ifndef HEAP_H_
#define HEAP_H_
#include "../element.h"

#define MIN_TREE_CAPATICITY (0)

typedef struct heapStruct
{
    int capacity;    // 二叉树的最大结点数
    int size;        // 当前整个二叉树的大小
    ElementType * elems; // 元素数组
} heapStruct;

typedef heapStruct * Heap;

// 决定使用小顶堆还是大顶堆, 默认小顶堆
#ifndef _SMALL_HEAP_
#define _SMALL_HEAP_
#endif
#ifdef _BIG_HEAP_
#undef _SMALL_HEAP_
#endif

// 初始化堆
Heap Heap_init(int maxElements);

// 删除堆
void Heap_free(Heap H);

// 判断堆是否已满
static inline int Heap_isFull(Heap H)
{
    return H->size == H->capacity;
}

// 判断堆是否为空
static inline int Heap_isEmpty(Heap H)
{
    return H->size == 0;
}

// 堆的插入
void Heap_insert(Heap H, ElementType * e);

// 堆的删除，只能是当前堆内最小/最大的元素
ElementType * Heap_del(Heap H);

// 堆的查询，只能是当前堆内最小/最大的元素
ElementType * Heap_find(Heap H);

#endif