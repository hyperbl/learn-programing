/*listADT 的测试文件*/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void showlist(List list)
{
    Node * move = list;
    puts("Here are the value of the list:");
    for (int i = 0; i < List_size(list); i++)
    {

        printf("No %d: %d\n", i, move->item);
        move = move->next;
    }
}

void plusTheItem(Item * pitem)
{
    *pitem *= 2;
}

int main(int argc, char const * argv[])
{
    List list;
    Item value;
    unsigned int index;
    char ch;
    List_init(&list);

    puts("test.c -- test the list ADT");
    do
    {
        printf("Enter characters to do somwthing.\n");
        printf("r - reset       E - isEmpty\n");
        printf("s - size        H - Header\n");
        printf("T - Tailer      a - at\n");
        printf("f - find        d - delete\n");
        printf("i - insert      S - succ\n");
        printf("P - prev        t - plusTheItem\n");
        printf("p - show        q - quit\n");
        printf("\n>>>");
        ch = getchar();
        while (getchar() != '\n') continue;
        switch (ch)
        {
            case 'r' : List_reset(&list); break;
            case 'E' : if (List_isEmpty(list)) puts("Yes");
                       else puts("No");
                       break;
            case 's' : printf("%d\n", List_size(list)); break;
            case 'H' : printf("%p\n", List_Header(list)); break;
            case 'T' : printf("%p\n", List_Tailer(list)); break;
            case 'a' : printf("index : ");
                       scanf("%u", &index);
                       printf("No %u: %d\n", index, List_at(&list, index)->item);
                       break;
            case 'f' : printf("which item do you want to find?\n");
                       Item_get(&value);
                       if (List_find(list, &value))
                           puts("Yes");
                       else
                           puts("No");
                        break;
            case 'd' : printf("which node do you want to delete?\n");
                       scanf("%u", &index);
                       List_delete(&list, List_at(&list, index));
                       break;
            case 'i' : printf("where do you want to insert in?\n");
                       scanf("%u", &index);
                       printf("item of new node :");
                       Item_get(&value);
                       List_insert(&list, List_at(&list, index), &value);
                       break;
            case 'S' : printf("which node ?\n");
                       scanf("%d", &index);
                       printf("The next node is:\n");
                       printf("No %u : %d\n", index + 1, List_succ(&list, List_at(&list, index))->item);
                       break;
            case 'P' : printf("which node ?\n");
                       scanf("%d", &index);
                       printf("The node before is:\n");
                       printf("No %u : %d\n", index - 1, List_prev(&list, List_at(&list, index))->item);
                       break;
            case 't' : List_Traverse(list, plusTheItem); break;
            case 'p' : showlist(list); break;
            case 'q' : break;
            default  : printf("Input Error!\nTry again!\n"); break;
        }
    }while (ch != 'q');

    List_free(&list);
    puts("Bye!");
    system("pause");
    return 0;
}