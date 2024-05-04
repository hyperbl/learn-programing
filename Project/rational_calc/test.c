#include "integer.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Integer A, B, C;
    Integer_Init(&A);
    Integer_Init(&B);
    Integer_Init(&C);
    printf("Number A is: ");
    Get(&A);
    printf("Number B is: ");
    Get(&B);
    printf("A + B = ");
    Add(&A, &B, &C);
    Print(&C);puts("");
    Integer_Del(&A);
    Integer_Del(&B);
    Integer_Del(&C);
    system("pause");
    return 0;
}