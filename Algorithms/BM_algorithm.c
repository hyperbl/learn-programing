/*BM_algorithm.c -- BM算法示例*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

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
    int i = 0, j;
    int movebC, movegS;
    while (i < len_src)
    {
        for (j = len_pat - 1; j >= 0 && src[i + j] == pat[j]; j--);
        if (j < 0)
        {
            free(bC);
            free(gS);
            return i;
        }
        else
        {
            movebC = j - bC[(int)src[i + j]];
            if (j != len_pat - 1)
                movegS = j + 1 - gS[j + 1];
            else
                movegS = 0;
            i += (movebC < movegS) ? movegS : movebC;
        }
    }
    free(bC);
    free(gS);
    return -1;
}

int * bad_Char(char * pat)
{
    int * bC = (int *) malloc(128 * sizeof (int));
    int len = strlen(pat);
    for (int i = 0; i < 128; i++)
        bC[i] = -1;
    for (int i = 0; i < len; i++)
        bC[(int)pat[i]] = i;
    return bC;
}

// 这是好后缀算法的辅助函数，用以生成suffix数组和prefix数组。
// suffix数组表示模式串中以某一位置为起始坐标的后缀子串在模式中可匹配的另一个子串的起始下标
// prefix数组表示模式串某一位置为起始坐标的后缀子串在模式中是否有可匹配的前缀子串
void get_suffix_and_prefix(char * pat, int * suffix, int * prefix)
{
    int len = strlen(pat);
    // suffix = (int *) malloc(len * sizeof (int));
    // prefix = (int *) malloc(len * sizeof (int));
    int i = len - 1, j, k = 0, count_pre = 0;
    for (j = 0; j < len; j++) suffix[j] = -1;
    while (i + 1)
    {
        for (k = i, j = i - 1; j >= 0; j--)
        {
            if (pat[i] == pat[j])
            {
                suffix[k] = j;
                if (j);
                else
                {
                    count_pre = 1;
                    while (k + count_pre + 1 < len && (suffix[k + count_pre + 1] 
                        == suffix[k + count_pre] + 1))
                        count_pre++;
                }
                k = j;
            }
            else
            {
                if (j + 1 < len && i < len 
                   && pat[j + 1] == pat[i]
                   && suffix[j + 1] + 1)
                    j = suffix[j + 1] + 1;
                else;
            }
        }
        i--;
    }
    if (count_pre)
    {
        for (i = 0; i < len - count_pre; i++)
            prefix[i] = 1;
        for (i = i; i < len; i++)
            prefix[i] = 0;
    }
    else
        for (i = 0; i < len; i++)
            prefix[i] = 0;
    return;
}

int * good_Suffix(char * pat)
{
    int len = strlen(pat);
    int * gS = (int *) malloc(len * sizeof (int));
    int * suffix = (int *) malloc(len * sizeof (int));
    int * prefix = (int *) malloc(len * sizeof (int));
    get_suffix_and_prefix(pat, suffix, prefix);
    int i;
    for (i = 0; i < len; i++)
    {
        gS[i] = suffix[i];
        if (!(gS[i] + 1) && prefix[i])
            gS[i] = 0;
        else;
    }
    free(suffix);
    free(prefix);
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