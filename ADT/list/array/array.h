/*array.h -- 数组ADT*/
/*代码抄自《数据结构（C语言版）》*/
#include <stdarg.h>

#define MAX_ARRAY_DIM 8   // 假设数组维数的最大值为8

typedef enum         // 函数执行的状态
{
    success,
    error,
    overflow,
    underflow
}Status;

typedef int ElemType;
typedef struct
{
    ElemType * base;     // 数组元素基址, 由Array_init分配
    int dim;             // 数组维数
    int * bounds;        // 数组维界地址，由Array_init分配
    int * constants;     // 数组映像函数常量基址，由Array_init分配
}Array;

// 若维数dim和随后的各维长度合法，则构造相应的数组A，
Status Array_init(Array * pA, int dim, ...);

// 销毁数组A
Status Array_del(Array * pA);

// 若ap指示的各下标值合法，则求出该元素在A中的相对地址
Status Array_loc(Array A, va_list ap, int * off);

// A 是n维数组，e 为元素变量，随后是n个下标值。
// 若各下标不越界，则将e赋值为所指定的A的元素值.
Status Array_getVal(Array A, ElemType * pe, ...);

// A 是n维数组，e 为元素变量，随后是n个下标值。
// 若各下标不越界，则将e的值赋给所指定的A的元素.
Status Array_assign(Array * pA, ElemType e, ...);
