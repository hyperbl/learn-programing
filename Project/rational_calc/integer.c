/*integer.c -- define the methods for Integer*/
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>

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
    ;
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
    ;
}

void GetInt(Integer * p_A)
{
    int isP = 0, index = 0;
    FILE * pf = fopen("history", "a+");
    char * buffer = (char *) malloc(sizeof (char));
    setvbuf(pf, buffer, _IONBF, 1);
    char ch = getchar(); fputc(ch, pf);
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
    p_A->val = (unsigned char *) malloc(sizeof (unsigned char) * (p_A->size + 1));
    fseek(pf, -p_A->size - 2, SEEK_CUR);
    ch = fgetc(pf);
    while ('0' <= ch && ch <= '9')
    {
        if (!isP && ch != '0')
            p_A->sign = POSITIVE;
        else;
        p_A->val[index++] = ch;
        ch = fgetc(pf);
    }
    p_A->val[index] = '\0';
    free(buffer);
    fclose(pf);
}

void PrintInt(Integer * p_A)
{
    printf("%s", p_A->val);
}

void Integer_Init(Integer * p_A)
{
    p_A->sign = ZERO;
    p_A->size = 0;
    p_A->val = NULL;
    p_A->inherit = &vir;
}

void Integer_Del(Integer * p_A)
{
    p_A->sign = ZERO;
    free(p_A->val);
    p_A->val = NULL;
}