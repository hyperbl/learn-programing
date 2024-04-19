/*BM_algorithm.c -- BM算法示例*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 25

// BM函数,如果pat是src的子串，则返回pat的首元在src串中的首位置
int BM(char * src, char * pat);

// 返回一个坏字符表
int * bad_Char(char * pat);

// 返回好后缀表
int * good_Suffix(char * pat);

char * s_gets(char * st, int n);

int main()
{
    char *src, *pat;
    src = (char *) malloc(SIZE * sizeof (char));
    pat = (char *) malloc(SIZE * sizeof (char));
    printf("source string: ");
    s_gets(src, SIZE);
    printf("pattern string: ");
    s_gets(pat, SIZE);
    int loc = BM(src, pat);
    if (loc + 1)
        printf("First Found at Index %d\n", loc);
    else
        puts("Not Found");
    free(src);
    free(pat);
    return 0;
}

int BM(char * src, char * pat)
{
    int len_src = strlen(src);
    int len_pat = strlen(pat);
    int * bC = bad_Char(pat);
    int * gS = good_Suffix(pat);
    int i = len_pat - 1, j = 0, k = 0;
    while (i < len_src && j < len_pat)
    {
        for (j = len_pat - 1, k = 0; j >= k && src[i - k] == pat[j - k]; k++);
        if (j < k)
            return i - len_pat + 1;
        else
        {
            int movebC = j - k - bC[src[i - k]];
            int movegS = 0;
            if (k)
                movegS = j - k + 1 - gS[j - k + 1];
            else;
            int move = (movebC < movegS) ? movegS : movebC;
            i += move;
            // i += movebC;
        }
    }
    return -1;
}

int * bad_Char(char * pat)
{
    int * bC = (int *) malloc(128 * sizeof (int));
    int len = strlen(pat);
    for (int i = 0; i < 128; i++)
        bC[i] = -1;
    for (int i = 0; i < len; i++)
        bC[pat[i]] = i;
    return bC;
}

int * good_Suffix(char * pat)
{
    int len = strlen(pat);
    int * gS = (int *) malloc(len * sizeof (int));
    int i, j;
    for (i = 0; i < len; i++)
        gS[i] = -1;
    for (i = len - 2; i >= 0; i--)
    {  
        for (j = i; j >= 0 && pat[j] == pat[len - 1 - i + j]; j--)
            if (pat[len - 1 + i - j] + 1)
                gS[len - 1 + i - j] = j;
            else; 
    }
    return gS;
}

char * s_gets(char * st, int n)
{
    char * ret_val = NULL;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        char * f = strchr(ret_val, '\n');
        if (f)
            *f = '\0';
        else
            while (getchar() != '\n');
    }
    else;
    return ret_val;
}