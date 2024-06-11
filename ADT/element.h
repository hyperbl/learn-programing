/* element.h -- provide operations on elements of ADTs*/
#ifndef ELEMENT_H_
#define ELEMENT_H_
#include <limits.h>
#include <memory.h>
#include <stdio.h>

#ifndef ElementType
#define ElementType int
#endif

// 设置初始值
static inline int elem_init(ElementType * e)
{
    *e = 0;
    return 0;
}

// 定义最大元素值
static const ElementType _elem_max_ = INT_MAX;
#define ELEM_MAX _elem_max_

// 定义最小元素值
static const ElementType _elem_min_ = 0;
#define ELEM_MIN _elem_min_

// 用于比较大小: LT -> Less Than, EQ -> Equal, GT -> Greater Than
typedef enum {LT = -1, EQ = 0, GT = 1} Order;

// 比较函数
static inline Order elem_compare(ElementType const * e1, ElementType const * e2)
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
static inline void * elem_copy(ElementType * e1, ElementType const * e2)
{
    return memcpy(e1, e2, sizeof (ElementType));
}

// 释放元素所占的内存
static inline void elem_free(ElementType * e)
{
    return;
}

// 输出函数
static inline int elem_show(ElementType const * e)
{
    return printf("%d ", *e);
}

#ifdef _NUMERICAL_ELEMENET_

// 元素的加法 c = a + b
static inline void elem_add(ElementType * a, ElementType * b, ElementType * c)
{
    *c = (*a) + (*b);
}

// 元素的减法 c = a - b
static inline void elem_sub(ElementType * a, ElementType * b, ElementType * c)
{
    *c = (*a) - (*b);
}

// 元素的乘法 c = a * b
static inline void elem_mul(ElementType * a, ElementType * b, ElementType * c)
{
    *c = (*a) * (*b);
}

#endif

#endif