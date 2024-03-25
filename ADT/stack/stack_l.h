#ifndef STACK_L_H
#define STACK_L_H

typedef int ElementType;
struct node;
typedef struct node * PtrToNode;
typedef PtrToNode Stack;
typedef struct node
{
    ElementType Element;
    PtrToNode Next;
}Node;

int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif
