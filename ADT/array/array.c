#include <stdlib.h>
#include "array.h"

Status Array_init(Array * pA, int dim, ...)
{
    if (dim < 1 || dim > MAX_ARRAY_DIM) return error;
    else;
    pA->dim = dim;
    pA->bounds = (int *) malloc(dim * sizeof (int));
    if (!pA->bounds) return overflow;
    else;
    int elemtotal = 1;
    va_list ap;
    va_start(ap, dim);
    for (int i = 0; i < dim; i++)
    {
        pA->bounds[i] = va_arg(ap, int);
        if (pA->bounds[i] < 0) return underflow;
        elemtotal *= pA->bounds[i];
    }
    va_end(ap);
    pA->base = (ElemType *) malloc(elemtotal * sizeof (ElemType));
    if (!pA->base) return overflow;
    pA->constants[dim - 1] = 1;
    for (int i = dim - 2; i >= 0; i--)
        pA->constants[i] = pA->bounds[i + 1] * pA->constants[i + 1];
    return success;
}

Status Array_del(Array * pA)
{
    if (!pA->base) return error;
    else
    {
        free(pA->base);
        pA->base = NULL;
    }
    if (!pA->bounds) return error;
    else
    {
        free(pA->bounds);
        pA->bounds = NULL;
    }
    if (!pA->constants) return error;
    else
    {
        free(pA->constants);
        pA->constants = NULL;
    }
    return success;
}

Status Array_loc(Array A, va_list ap, int * off)
{
    int i, ind;
    *off = 0;
    for (i = 0; i < A.dim; i++)
    {
        ind = va_arg(ap, int);
        if (ind < 0 || ind > A.bounds[i]) return overflow;
        else *off += A.constants[i] * ind;
    }
    return success;
}

Status Array_getVal(Array A, ElemType * pe, ...)
{
    va_list ap;
    int off;
    va_start(ap, *pe);
    if (Array_loc(A, ap, &off)) return error;
    else
        *pe = *(A.base + off);
    return success;
}

Status Array_assign(Array * pA, ElemType e, ...)
{
    va_list ap;
    int off;
    va_start(ap, e);
    if (Array_loc(*pA, ap, &off)) return error;
    else
        *(pA->base + off) = e;
    return success;
}