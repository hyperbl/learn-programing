#include <stdio.h>
#include <stdlib.h>
#include "stack_a.h"

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
    return  S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements)
{
    Stack S;

    if (MaxElements < MinStackSize)
        fprintf(stderr, "Stack size is too small");

    S = (Stack) malloc(sizeof (struct StackRecord));
    if (S == NULL)
        fprintf(stderr, "Out of space!!!");

    S->Array = (ElementType *) malloc(sizeof (ElementType) * MaxElements);
    MakeEmpty(S);

    return S;
}

void DisposeStack(Stack S)
{
    if (S)
    {
        free(S->Array);
        free(S);
    }
}

void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S))
        fprintf(stderr, "Full stack");
    else
        S->Array[++ S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    fprintf(stderr, "Empty stack");
    return 0;
}

void Pop(Stack S)
{
    if (IsEmpty(S))
        fprintf(stderr, "Empty stack");
    else
        S->TopOfStack--;
}

ElementType TopAndPop(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack--];
    fprintf(stderr, "Empty stack");
    return 0;
}

