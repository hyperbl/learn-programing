/* heap.c -- 堆的实现*/
#include "heap.h"
#include <stdlib.h>

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
        elem_copy(&minElem, H->elems + 1);
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
        elem_copy(H->elems + i, &lastElem);
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
        elem_copy(H->elems + i, &lastElem);
        return &maxElem;
    }
    else
        return H->elems;
}
#else
#error KIND OF HEAP NOT DECIDED
#endif
#endif

Heap Heap_init(int maxElements)
{
    Heap H;
    if (maxElements > MIN_TREE_CAPATICITY)
    {
        H = (Heap) malloc(sizeof (heapStruct));
        if (H)
        {
            H->elems = (ElementType *) malloc(sizeof (ElementType) * 
                                                    (maxElements + 1));
            H->capacity = maxElements;
            H->size = 0;
#ifdef _SMALL_HEAP_
            elem_copy(H->elems, &ELEM_MIN);
#else
#ifdef _BIG_HEAP_
            elem_copy(H->elems, &ELEM_MAX);
#endif
#endif
        }
    }
    return H;
}

void Heap_free(Heap H)
{
    if (H)
    {
        for (int i = 0; i <= H->capacity; i++)
            elem_free(H->elems + i);
        free(H->elems);
    }
}

ElementType * Heap_find(Heap H)
{
    return H->elems + 1;
}