/*integer.h -- Integer ADT*/
#ifndef _INTEGER_H
#define _INTEGER_H
#include "numerical.h"

typedef enum {ZERO, POSITIVE, NEGATIVE} Sign;   // 整数的符号

typedef struct integer Integer;
struct integer
{
    // 整数的方法
    Numerical const * inherit;

    // 数数的属性

    Sign sign;
    unsigned long size;     // 整数的长度
    unsigned char * val;        // 整数的绝对值
};

// 整数的方法的实现函数原型

// // 整数的加法  C = A + B
// void IntAdd(Integer * p_A, Integer * p_B, Integer * p_C);    

// // 整数的减法  C = A - B
// void IntSub(Integer * p_A, Integer * p_B, Integer * p_C);  

// // 整数的乘法  C = A * B  
// void IntMul(Integer * p_A, Integer * p_B, Integer * p_C);    

// // 整数的除法  C = A / B
// void IntDiv(Integer * p_A, Integer * p_B, Integer * p_C);    

// 整数的取模  C = A % B
void Mod(Integer * p_A, Integer * p_B, Integer * p_C);    

// 整数的幂   C = A ** B
void Pow(Integer * p_A, Integer * p_B, Integer * p_C);    

// // 整数的绝对值  C = |A|
// void IntAbs(Integer * p_A, Integer * p_C);  

// // 整数的相反数  C = -A
// void IntOps(Integer * p_A, Integer * p_C);  

// // 从输入中获取整数
// void GetInt(Integer * p_A);    

// // 输出整数
// void PrintInt(Integer * p_A);    

// 初始化整数
void Integer_Init(Integer * p_A);  

// 删除整数
void Integer_Del(Integer * p_A);   

#endif