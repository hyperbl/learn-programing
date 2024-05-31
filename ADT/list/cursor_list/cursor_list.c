#include "cursor_list.h"
#include <stdio.h>

#define SpaceSize 100

struct Node
{
    ElementType Element;
    Position Next;
};

static struct Node CursorSpace[SpaceSize];

void InitializeCursorSpace(void)
{
    int i;
    for (i = 0; i < SpaceSize - 1; i++)
        CursorSpace[i].Next = i + 1;
    CursorSpace[i].Next = 0;
}

static Position CursorAlloc(void)
{
    Position P;

    P = CursorSpace[0].Next;
    CursorSpace[0].Next = CursorSpace[P].Next;

    return P;
}

static void CursorFree(Position P)
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

List MakeEmpty()
{
    List L = CursorAlloc();
    CursorSpace[L].Next = 0;
    return L;
}

int IsEmpty(const List L)
{
    return CursorSpace[L].Next == 0;
}

int IsLast(const Position P, const List L)
{
    return CursorSpace[P].Next == 0;
}

Position Find(ElementType X, const List L)
{
    Position P = L;
    while (P && CursorSpace[P].Element != X)
        P = CursorSpace[P].Next;
    return P;
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    
    P = FindPrevious(X, L);
    
    if (!IsLast(P, L))
    {
        TmpCell = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

Position FindPrevious(ElementType X, const List L)
{
    Position P = L;

    while (CursorSpace[P].Next && CursorSpace
            [CursorSpace[P].Next].Element != X)
        P = CursorSpace[P].Next;

    return P;
}

void Insert(ElementType X, List L, Position P)
{
    Position Tmp = CursorAlloc();
    if (Tmp)
    {
        CursorSpace[Tmp].Element = X;
        CursorSpace[Tmp].Next = CursorSpace[P].Next;
        CursorSpace[P].Next = Tmp;
    }
    else
        return;
}

void DeleteList(List L)
{
    Position save = L;
    while (L)
    {
        CursorFree(save);
        L = CursorSpace[L].Next;
        save = L;
    }
}

Position Header(const List L)
{
    return L;
}
 
Position First(const List L)
{
    return CursorSpace[L].Next;
}

Position Advance(const Position P)
{
    return CursorSpace[P].Next;
}

Position Previous(const Position P, const List L)
{
    Position Tmp = L;
    while (CursorSpace[Tmp].Next != P)
        Tmp = CursorSpace[Tmp].Next;
    return Tmp;
}

ElementType Retrieve(const Position P)
{
    return CursorSpace[P].Element;
}

void PrintList(const List L)
{
    Position P = CursorSpace[L].Next;
    printf("[ ");
    while (P)
    {
        printf(PRIelem " ", CursorSpace[P].Element);
        P = CursorSpace[P].Next;
    }
    puts("]");
}
