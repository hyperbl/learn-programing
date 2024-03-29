#ifndef LIST_H
#define LIST_H

struct Node;
typedef int ElementType;
typedef struct Node * PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;
struct Node
{
    ElementType Element;
    Position Next;
};
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
Position Previous(Position P, List L);
ElementType Retrieve(Position P);

#endif
