#include "integer.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Integer A;
    Integer_Init(&A);
    Get(&A);
    printf("Number A is: ");
    Print(&A);
    puts("");
    system("pause");
    return 0;
}