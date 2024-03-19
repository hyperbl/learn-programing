#include <stdlib.h>
#include <stdio.h>
#include "stack_l.h"

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack()
{
    Stack S;
    S = (Stack) malloc(sizeof (Node));
    if (S == NULL)
       fprintf(stderr, "Out of space!!!\n");
    MakeEmpty(S);
    return S;
}

void DisposeStack(Stack S)
{
    PtrToNode save = S;
    while (S)
    {
        save = S;
        S = S->Next;
        free(save);
    }
}

void MakeEmpty(Stack S)
{
    if (S)
        while (! IsEmpty(S))
            Pop(S);
    else
        fprintf(stderr, "Must use CreateStack first\n");
}

void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;
    TmpCell = (PtrToNode) malloc(sizeof (Node));
    if (TmpCell)
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
    else
        fprintf(stderr, "Out of space!!!\n");
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Next->Element;
    fprintf(stderr, "Empty stack\n");
    return 0;
}

void Pop(Stack S)
{
    PtrToNode FirstCell;
    if (IsEmpty(S))
        fprintf(stderr, "Empty stack\n");
    else
    {
        FirstCell = S->Next;
        S = FirstCell->Next;
        free(FirstCell);
    }
}
