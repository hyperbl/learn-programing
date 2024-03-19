#ifndef CURSOR_LIST_H
#define CURSOR_LIST_H

#define PRIelem "%d"
#define PRIpos "%d"

typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

void InitializeCursorSpace(void);

List MakeEmpty();
int IsEmpty(const List L);
int IsLast(const Position P, const List L);
Position Find(ElementType X, const List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, const List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(const List L);
Position First(const List L);
Position Advance(const Position P);
Position Previous(const Position P, const List L);
ElementType Retrieve(const Position P);
void PrintList(const List L);

#endif
