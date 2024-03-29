/*KMP_algorithm.c -- KMP算法示例*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 25 // 界定最大字符串长度

int next[SIZE];

// KMP() 利用模式串pat的next函数求pat在主串src中pos位置之后
// 的位置的KMP算法。
int KMP(char src[], char pat[], int pos);

//求模式串pat的next数组并存入数组next
void get_next(char pat[], int next[]);

void str_get(char str[]);


int main()
{
    char src[SIZE] = {'\0'}, pat[SIZE] = {'\0'};
    str_get(src);
    str_get(pat);
    printf("%d\n",KMP(src, pat, 0));
    return 0;
}

int KMP(char src[], char pat[], int pos)
{
    int i = pos, j = 1;
    get_next(pat, next);
    while (i <= src[0] && j <= pat[0])
        if (!j || src[i] == pat[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    if (j > pat[0]) return i - pat[0];
    else return 0;
}

void get_next(char pat[], int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < pat[0])
        if (!j || pat[i] == pat[j])
        {
            i++; j++;
            next[i] = j;
        }
        else
            j = next[j];
}

void str_get(char str[])
{
    int i;
    scanf("%s", str + 1);
    while (getchar() != '\n');
    for (i = 1; str[i]; i++);
    str[0] = i;
}