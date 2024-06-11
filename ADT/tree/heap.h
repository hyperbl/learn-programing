/* heap.h -- 堆ADT*/
#ifndef HEAP_H_
#define HEAP_H_

#define _ARRAY_BIN_TREE_
#include "bin_tree.h"

typedef BinTree Heap;

// 决定使用小顶堆还是大顶堆
// #define _SMALL_HEAP_
// #define _BIG_HEAP_

// 初始化堆
static inline Heap Heap_init(int maxElements)
{
    Heap H;
    H = (Heap) BinTree_init(maxElements);
#ifdef _BIG_HEAP_
    elem_copy(H->elems, &ELEM_MAX);
#endif
}

// 删除堆
static inline void Heap_free(Heap H)
{
    return BinTree_free(H);
}

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