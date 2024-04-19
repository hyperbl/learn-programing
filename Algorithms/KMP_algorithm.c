/*KMP_algorithm.c -- KMP算法示例*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25 // 界定最大字符串长度

// KMP() 利用模式串pat的next函数求pat在主串src中pos位置之后
// 的位置的KMP算法。
int KMP(char src[], char pat[]);

//求模式串pat的next数组
int * get_next(char pat[]);

char * s_gets(char * st, int n);


int main()
{
    char src[SIZE] = {'\0'}, pat[SIZE] = {'\0'};
    printf("source string: ");
    s_gets(src, SIZE);
    printf("pattern string: ");
    s_gets(pat, SIZE);
    int loc = KMP(src, pat);
    if (loc + 1)
        printf("First Found at Index %d\n", loc);
    else
        puts("Not Found");
    return 0;
}

int KMP(char src[], char pat[])
{
    int * next = get_next(pat);
    int len_src = strlen(src);
    int len_pat = strlen(pat);
    int i = 0, j = 0;
    while (i < len_src && j < len_pat)
    {
        if (j == -1 || src[i] == pat[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j == len_pat)
        return i - j;
    else
        return -1;
}

int * get_next(char pat[])
{
    int i = 0, j = -1, len = strlen(pat);
    int * next = (int *) malloc(len * sizeof (int));
    if (len)
        next[i] = j;
    else;
    while (i < len)
    {
        if (j == -1 || pat[i] == pat[j])
        {
            i++; j++;
            if (pat[i] != pat[j])
            {
                next[i] = j;
            }
            else
                next[i] = next[j];
        }
        else
            j = next[j];
    }
    return next;
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        char * find = strchr(ret_val, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n');
    }
    else;
    return ret_val;
}