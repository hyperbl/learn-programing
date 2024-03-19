#include "list.h"
#include <stdlib.h>

List MakeEmpty(List L)
{
    L = (List) malloc(sizeof (struct Node));
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P = L->Next;
    while (P != NULL && P->Element != X)
        P = P->Next;
    return P;
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if ( !IsLast(P, L))
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

Position FindPrevious(ElementType X, List L)
{
    Position P = L;
    while (P->Next != NULL && P->Next->Element != X)
        P = P->Next;
    return P;
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = (Position) malloc(sizeof (struct Node));
    if (TmpCell == NULL)
        system("echo 'Out of Space!!!'");
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Position save = L;
    while (L != NULL)
    {
        L = L->Next;
        free(save);
        save = L;
    }
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
	if (P == NULL)
		return NULL;
	else
		return P->Next;
}

Position Previous(Position P, List L)
{
    Position Tmp = L;
    while (Tmp != NULL && Tmp->Next != P)
        Tmp = Tmp->Next;
    return Tmp;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}



