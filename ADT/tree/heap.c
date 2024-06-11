/* heap.c -- 堆的实现*/
#include "heap.h"
#define _SMALL_HEAP_
#ifdef _SMALL_HEAP_
void Heap_insert(Heap H, ElementType * e)
{
    // elem_init(H->elems);
    if (!Heap_isFull(H))
    {
        int i;
        for (i = ++H->size; elem_compare(H->elems + i / 2, e) == GT; i /= 2)
            elem_copy(H->elems + i, H->elems + i / 2);
        elem_copy(H->elems + i, e);
    }
}

ElementType * Heap_del(Heap H)
{
    // elem_init(H->elems);
    int i, child;
    static ElementType minElem, lastElem;
    if (!Heap_isEmpty(H))
    {
        elem_copy(minElem, H->elems + 1);
        elem_copy(&lastElem, H->elems + H->size--);
        for (i = 1; i * 2 <= H->size; i = child)
        {
            // 找到最小的孩子结点
            child = i * 2;
            if (child != H->size && elem_compare(H->elems + child + 1,
                                                 H->elems + child) == LT)
                child++;
            
            if (elem_compare(&lastElem, H->elems + child) == GT)
                elem_copy(H->elems + i, H->elems + child);
            else
                break;
        }
        elem_copy(H->elems + i, lastElem);
        return &minElem;
    }
    else
        return H->elems;
}

#else
#ifdef _BIG_HEAP_
void Heap_insert(Heap H, ElementType * e)
{
    if (!Heap_isFull(H))
    {
        int i;
        for (i = ++H->size; elem_compare(H->elems + i / 2, e) == LT; i /= 2)
            elem_copy(H->elems + i, H->elems + i / 2);
        elem_copy(H->elems + i, e);
    }
}

ElementType * Heap_del(Heap H)
{
    int i, child;
    static ElementType maxElem, lastElem;
    if (!Heap_isEmpty(H))
    {
        elem_copy(&maxElem, H->elems + 1);
        elem_copy(&lastElem, H->elems + H->size--);
        for (i = 1; i * 2 <= H->size; i = child)
        {
            // 找到最大的孩子结点
            child = i * 2;
            if (child != H->size && elem_compare(H->elems + child + 1,
                                        H->size + child) == GT)
                child++;
            
            if (elem_compare(&lastElem, H->elems + child) == LT)
                elem_copy(H->elems + i, H->elems + child);
            else
                break;
        }
        elem_copy(H->elems + i, lastElem);
        return &maxElem;
    }
    else
        return H->elems;
}
#else
#error KIND OF HEAP NOT DECIDED
#endif
#endif

ElementType * Heap_find(Heap H)
{
    return H->elems + 1;
}