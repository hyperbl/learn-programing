/*stack.c -- 盛放stack.h中函数原型的定义*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int Stack_isEmpty(Stack S)
{
    return S->next == NULL;
}

void Stack_init(Stack * pS)
{
    *pS = (Stack) malloc(sizeof (Node));
    if (*pS)
    {
        (*pS)->next = NULL;
        (*pS)->item = -1;
    }
    else
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Initialization Failed.\n", __LINE__ - 8, __func__, __FILE__);
}

void Stack_free(Stack * pS)
{
    Node * save = *pS;
    while (*pS)
    {
        save = *pS;
        (*pS) = (*pS)->next;
        free(save);
    }
}

void Stack_push(Stack * pS, Item item)
{
    Node * ptr = (Node *) malloc(sizeof (Node));
    if (ptr)
    {
        ptr->item = item;
        ptr->next = (*pS)->next;
        (*pS)->next = ptr;
    }
    else
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Initialization Failed.\n", __LINE__ - 9, __func__, __FILE__);
}

Item Stack_pop(Stack * pS)
{
    Node * ptr;
    Item item = -1;
    if (Stack_isEmpty(*pS))
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Nothing Can be Popped out.\n", __LINE__ - 2, __func__, __FILE__);
    else
    {
        ptr = (*pS)->next;
        item = ptr->item;
        (*pS)->next = ptr->next;
        free(ptr);
    }
    return item;
}

Item Stack_top(Stack S)
{
    if (Stack_isEmpty(S))
    {
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Nothing in the Stack.\n", __LINE__ - 2, __func__, __FILE__);
        return S->item;
    }
    else
        return S->next->item;
}