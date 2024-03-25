#ifndef STACK_A_H
#define STACK_A_H

#define EmptyTOS (-1)
#define MinStackSize (5)

typedef int ElementType;
struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType * Array;
};
typedef struct StackRecord * Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Sack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif
