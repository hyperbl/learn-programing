/*integer.c -- define the methods for Integer*/
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 整数的加法  C = A + B
void IntAdd(Integer * p_A, Integer * p_B, Integer * p_C);    

// 整数的减法  C = A - B
void IntSub(Integer * p_A, Integer * p_B, Integer * p_C);  

// 整数的乘法  C = A * B  
void IntMul(Integer * p_A, Integer * p_B, Integer * p_C);    

// 整数的除法  C = A / B
void IntDiv(Integer * p_A, Integer * p_B, Integer * p_C);

// 整数的绝对值  C = |A|
void IntAbs(Integer * p_A, Integer * p_C);  

// 整数的相反数  C = -A
void IntOps(Integer * p_A, Integer * p_C);  

// 从输入中获取整数
void GetInt(Integer * p_A);    

// 输出整数
void PrintInt(Integer * p_A);    


// 虚函数调用
static void IntAdd_(void * p_A, void * p_B, void * p_C)
{
    IntAdd((Integer *)p_A, (Integer *)p_B, (Integer *)p_C);
}
static void IntSub_(void * p_A, void * p_B, void * p_C)
{
    IntSub((Integer *)p_A, (Integer *)p_B, (Integer *)p_C);
}
static void IntMul_(void * p_A, void * p_B, void * p_C)
{
    IntMul((Integer *)p_A, (Integer *)p_B, (Integer *)p_C);
}
static void IntDiv_(void * p_A, void * p_B, void * p_C)
{
    IntDiv((Integer *)p_A, (Integer *)p_B, (Integer *)p_C);
}
static void IntAbs_(void * p_A, void * p_C)
{
    IntAbs((Integer *)p_A, (Integer *)p_C);
}
static void IntOps_(void * p_A, void * p_C)
{
    IntOps((Integer *)p_A, (Integer *)p_C);
}
static void GetInt_(void * p_A)
{
    GetInt((Integer *)p_A);
}
static void PrintInt_(void * p_A)
{
    PrintInt((Integer *)p_A);
}

// 虚函数表
static Numerical vir = 
{
    &vir,
    &IntAdd_,
    &IntSub_,
    &IntMul_,
    &IntDiv_,
    &IntAbs_,
    &IntOps_,
    &GetInt_,
    &PrintInt_
};

#define WARNING 'W'
#define ERROR 'E'
// 异常处理
static void raise(char kind, char * msg)
{
    switch (kind)
    {
        case WARNING : fprintf(stderr, "[WARNING]: %s", msg); break;
        case ERROR : fprintf(stderr, "[ERROR]: %s", msg);
                     exit(EXIT_FAILURE);
        default : break;
    }
}

void IntAdd(Integer * p_A, Integer * p_B, Integer * p_C)
{
    Integer tmp; Integer_Init(&tmp);  // 用于存储临时结果
    if (p_A->sign == ZERO || p_B->sign == ZERO)       // 如果存在零元，自然不用算了
    {
        if (p_A->sign != ZERO)
            tmp = *p_A;
        else
            tmp = *p_B;
    }
    else
    {
        if (p_A->sign + p_B->sign)     // 如果两个整数同号
        {
            tmp.sign = p_A->sign;
            tmp.size = (p_A->size > p_B->size) ? p_A->size : p_B->size;
            tmp.val = (unsigned char *) malloc(sizeof (unsigned char) * (tmp.size + 1));
            for (int i = 0; i <= tmp.size; i++) tmp.val[i] = '0';
            int cur = 0;
            while (cur < p_A->size && cur < p_B->size)
            {
                tmp.val[cur] += p_A->val[cur] - '0' + p_B->val[cur] - '0';
                while (tmp.val[cur] > '9')
                {
                    tmp.val[cur + 1] += 1;
                    tmp.val[cur] -= 10;
                }
                cur++;
            }
            while (cur < p_A->size)
            {
                tmp.val[cur] += p_A->val[cur] - '0';
                while (tmp.val[cur] > '9')
                {
                    tmp.val[cur + 1] += 1;
                    tmp.val[cur] -= 10;
                }
                cur++;
            }
            while (cur < p_B->size)
            {
                tmp.val[cur] += p_B->val[cur] - '0';
                while (tmp.val[cur] > '9')
                {
                    tmp.val[cur + 1] += 1;
                    tmp.val[cur] -= 10;
                }
                cur++;
            }
            if (tmp.val[tmp.size] > '0')
            {
                tmp.size++;
                unsigned char * save = (unsigned char *) malloc(sizeof (unsigned char) * tmp.size);
                memcpy(save, tmp.val, sizeof (unsigned char) * tmp.size);
                free(tmp.val);
                tmp.val = (unsigned char *) malloc(sizeof (unsigned char) * (tmp.size + 1));
                memcpy(tmp.val, save, sizeof (unsigned char) * tmp.size);
                tmp.val[tmp.size] = '\0';
            }
            else;
        }
        else             // 两个整数异号
        {
            if (p_A->sign == POSITIVE)
            {
                Ops(p_B, &tmp);
                Sub(p_A, &tmp, &tmp);
            }
            else
            {
                Ops(p_A, &tmp);
                Sub(p_B, &tmp, &tmp);
            }
        }
    }
    if (p_C->size)       // 把运算最终结果存入C中
        free(p_C->val);
    else;
    p_C->val = (unsigned char *) malloc(sizeof (unsigned char) * (tmp.size + 1));
    memcpy(p_C, &tmp, sizeof (tmp));
}

void IntSub(Integer * p_A, Integer * p_B, Integer * p_C)
{
    ;
}

void IntMul(Integer * p_A, Integer * p_B, Integer * p_C)
{
    ;
}

void IntDiv(Integer * p_A, Integer * p_B, Integer * p_C)
{
    ;
}

void Mod(Integer * p_A, Integer * p_B, Integer * p_C)
{
    ;
}

void Pow(Integer * p_A, Integer * p_B, Integer * p_C)
{
    ;
}

void IntAbs(Integer * p_A, Integer * p_C)
{
    ;
}

void IntOps(Integer * p_A, Integer * p_C)
{
    if (p_C->size)
    {
        raise(WARNING, "Override Existing");
        free(p_C->val);
    }else;
    p_C->val = (unsigned char *) malloc(sizeof (unsigned char) * (p_A->size + 1));
    memcpy(p_C, p_A, sizeof (*p_A));
    switch (p_A->sign)
    {
        case POSITIVE : p_C->sign = NEGATIVE; break;
        case NEGATIVE : p_C->sign = POSITIVE; break;
        case ZERO : p_C->sign = ZERO;
        default : break;
    }
}

void GetInt(Integer * p_A)
{
    FILE * pf = fopen("history", "a+");
    char * buffer = (char *) malloc(sizeof (char));
    setvbuf(pf, buffer, _IONBF, 1);
    char ch;
    while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\t'); 
    fputc(ch, pf);
    if (ch == '-')
    {
        p_A->sign = NEGATIVE;
        ch = getchar(); fputc(ch, pf);
    }
    else;
    while ('0' <= ch && ch <= '9')
    {
        p_A->size++;
        ch = getchar();
        fputc(ch, pf);
    }
    int index = p_A->size - 1;
    p_A->val = (unsigned char *) malloc(sizeof (unsigned char) * (p_A->size + 1));
    fseek(pf, -p_A->size - 2, SEEK_CUR);
    ch = fgetc(pf);
    while ('0' <= ch && ch <= '9')
    {
        if (!p_A->sign && ch != '0')
            p_A->sign = POSITIVE;
        else;
        p_A->val[index--] = ch;
        ch = fgetc(pf);
    }
    p_A->val[p_A->size] = '\0';
    free(buffer);
    fclose(pf);
}

void PrintInt(Integer * p_A)
{
    switch (p_A->sign)
    {
        case NEGATIVE : putchar('-');
        case POSITIVE : int end;
                        for (end = p_A->size - 1; end >= 0; end--)
                            putchar(p_A->val[end]);
                        break;
        case ZERO : putchar('0');
        default : break;
    }
    
}

void Integer_Init(Integer * p_A)
{
    if (p_A)
    {
        p_A->sign = ZERO;
        p_A->size = 0;
        p_A->val = NULL;
        p_A->inherit = &vir;
    }
    else
    {
        raise(ERROR, "Initialization Failed");
    }
}

void Integer_Del(Integer * p_A)
{
    if (p_A)
    {
        p_A->sign = ZERO;
        free(p_A->val);
        p_A->val = NULL;
    }
    else
    {
        raise(ERROR, "Deletion Failed");
    }
}