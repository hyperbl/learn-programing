#include <stdio.h>
#include <ctype.h>
#include "cursor_list.h"

int main()
{
    InitializeCursorSpace();
    List L = MakeEmpty();
    Position P;
    ElementType X;
    puts("Welcome to test the list ADT!!!");
    char ch = '\0';
    int f = 1;
    while (f && ch != 'q')
    {
        switch (ch)
        {
            case 'e': puts(IsEmpty(L) ? "Yes" : "No"); break;
            case 'l': puts("Which position?");
                      scanf(PRIpos, &P); getchar();
                      puts(IsLast(P, L) ? "Yes" : "No"); break;
            case 'f': puts("Which element do you want to find?");
                      scanf(PRIelem, &X); getchar();
                      P = Find(X, L);
                      if (P) printf("Maybe at position " PRIpos ".\n", P);
                      else puts("It doesn't belong to this list."); break;
            case 'd': puts("Which element do you want to delete?");
                      scanf(PRIelem, &X); getchar();
                      Delete(X, L);
                      PrintList(L);
            case 'F': break;
            case 'i': puts("Where do you want to insert?");
                      scanf(PRIpos, &P);
                      puts("And the value?");
                      scanf(PRIelem, &X); getchar();
                      Insert(X, L, P);
                      PrintList(L); break;
            case 'D': puts("Do you want to delete the list?");
                      printf("It may end the program. [Y/N]");
                      if (toupper(getchar()) == 'Y')
                      {
                         DeleteList(L);
                         PrintList(L);
                         f = 1;
                      }
                      while (getchar() != '\n');
                      break;
            case 'h': printf("The header of the list is " PRIpos " .\n", Header(L));
                      break;
            case 'I': printf("The fist pos of the list is " PRIpos " .\n", First(L));
                      break;
            case 'a': puts("Which position?");
                      scanf(PRIpos, &P); getchar();
                      printf("The next pos of this position is " PRIpos " .\n", Advance(P));
                      break;
            case 'p': puts("Which position?");
                      scanf(PRIpos, &P); getchar();
                      printf("The previous pos of this position is " PRIpos " .\n", Previous(P, L));
                      break;
            case 'r': puts("Which position?");
                      scanf(PRIpos, &P); getchar();
                      printf("The element at this position is " PRIelem " .\n", Retrieve(P));
                      break;
            case 'P': PrintList(L); break;
            default:  puts("Here are functions for you to choose:");
                      printf("e) IsEmpty;		l) IsLast;      f) Find;\n"
                             "d) Delete;      F) FindPrevious;\n"
                             "i) Insert;      D) DeleteList;  h) Header;\n"
                             "I) First;       a) Advance;     p) Previous;\n"
                             "r) Retrieve;    P) PrintList    q) quit;\n");
                      break;
        }
        printf(">>");
        ch = getchar(); getchar();
    }
    printf("Bye!!!\n");
    return 0;
}
