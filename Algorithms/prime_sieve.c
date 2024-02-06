/*prime_sieve.c -- 记录各种素数筛法*/
#include <stdio.h>
#include <stdlib.h>

// 厄拉多塞筛法
void eratosthenes_sieve(int num, int arr[]);

int main()
{
    int num;
    puts("Enter an integer:");
    scanf("%d", &num);
    int * array = (int *) malloc(sizeof (int) * num);
    for (int i = 0; i < num; i++)
        array[i] = 1;
    printf("prime numbers between 1 and %d are listed as follows:\n", num);
    eratosthenes_sieve(num, array);
    for (int i = 2; i <= num; i++)
        if (array[i - 1])
            printf("%d\n", i);
    free(array);
    system("pause");
    return 0;
}

void eratosthenes_sieve(int num, int arr[])
{
    int i, j;
    for (i = 2; i * i <= num; i++)
    {
        if (arr[i - 1])
            for (j = i * i; j <= num; j += i)
                arr[j - 1] = 0;
    }
}