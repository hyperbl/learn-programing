/*list.c -- 盛放list.h中函数原型的定义*/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void Item_init(Item * pitem)
{
    *pitem = 0;
}

void Item_copy(Item * pitem, Item const * pitem_src)
{
    *pitem = *pitem_src;
}

int Item_get(Item * pitem)
{
    return scanf("%d", pitem);
}

void List_init(List * plist)
{
    *plist = (Node *) malloc(sizeof (Node));
    if (*plist != NULL)
    {
        Item_init(&(*plist)->item);
        (*plist)->next = NULL;
    }
    else
    {
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Initialization Failed.\n", __LINE__ - 9, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
}

void List_free(List * plist)
{
    Node * psave;
    while (*plist !=  NULL)
    {
        psave = (*plist)->next;
        free(*plist);
        *plist = psave;
    }
}

void List_reset(List * plist)
{
    Node * move = (*plist)->next;
    while (move != NULL)
    {
        Item_init(&move->item);
        move = move->next;
    }
}

int List_isEmpty(List list)
{
    if (list == NULL)
        return 1;
    else
        return 0;
}

int List_size(List list)
{
    Node * move = list;
    int count = 0;
    while (move != NULL)
    {
        count++;
        move = move->next;
    }
    return count;
}

Node * List_Header(List list)
{
    return list;
}

Node * List_Tailer(List list)
{
    Node * last = list;
    while (last->next != NULL)
        last = last->next;
    return last;
}

Node * List_at(List * plist, unsigned int index)
{
    Node * pmove = *plist;
    for (int i = 0; i < index && pmove != NULL; i++)
        pmove = pmove->next;
    if (pmove == NULL)
    {
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Index out of range.\n", __LINE__, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
    else
        return pmove;

}

Node * List_find(List list, Item const * pitem)
{
    Node * pos = list;
    while ((pos != NULL) && (pos->item != *pitem))
        pos = pos->next;
    return pos;
}

void List_delete(List * plist, Node * pos)
{
    Node * ppos;
    ppos = List_prev(plist, pos);
    if (ppos == NULL)
    {
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Can't Delete the Header.\n", __LINE__, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
    else
    {
        ppos->next = pos->next;
        free(pos);
    }
}

void List_insert(List * plist, Node * pos, Item const * pitem)
{
    Node * pnew;
    pnew = (Node *) malloc(sizeof (Node *));
    if (pnew)
    {
        Item_copy(&pnew->item, pitem);
        if (pos->next != NULL)
        {
            pnew->next = pos->next;
            pos->next = pnew;
        }
        else
        {
            pos->next = pnew;
            pnew->next = NULL;
        }
    }
    else
    {   fprintf(stderr, "Error ---- in line %d, fuction %s, filename %s : \n"
                "Allocation Failed.\n", __LINE__ - 17, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
}

Node * List_succ(List * plist, Node * pos)
{
    if (pos != NULL)
        return pos->next;
    else
    {   fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Nothing after NULL.\n", __LINE__, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
}

Node * List_prev(List * plist, Node * pos)
{
    Node * ppos = *plist;
    if (pos == NULL)
    {
        fprintf(stderr, "Error ---- in line %d, function %s, filename %s : \n"
                "Nothing Valid before NULL.\n", __LINE__, __func__, __FILE__);
        List_free(plist);
        system("pause");
        exit(EXIT_FAILURE);
    }
    else if (pos != *plist)
        while (ppos->next != pos)
            ppos = ppos->next;
    else
        ppos = NULL;
    return ppos;
}

void List_Traverse(List list, void (*pfun)(Item  * pitem))
{
    Node * move = list->next;
    while (move != NULL)
    {
        (*pfun)(&move->item);
        move = move->next;
    }
}