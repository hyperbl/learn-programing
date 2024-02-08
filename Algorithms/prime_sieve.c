/*prime_sieve.c -- 记录各种素数筛法*/
#include <stdio.h>
#include <stdlib.h>

// 厄拉多塞筛法
void eratosthenes_sieve(int num, int arr[]);

// 辛达拉姆筛法
void sundaram_sieve(int num, int arr[]);

int main()
{
    int num;
    puts("Enter an integer:");
    scanf("%d", &num);
    int * array = (int *) malloc(sizeof (int) * num);
    for (int i = 0; i < num; i++)
        array[i] = 1;
    printf("prime numbers between 1 and %d are listed as follows:\n", num);
    // eratosthenes_sieve(num, array);
    sundaram_sieve(num, array);
    for (int i = 2; i <= num; i++)
        if (array[i - 1])
            printf("%d\n", i);
    free(array);
    return 0;
}

void eratosthenes_sieve(int num, int arr[])
{
    int i, j;
    for (i = 2; i * i <= num; i++)
        if (arr[i - 1])
            for (j = i * i; j <= num; j += i)
                arr[j - 1] = 0;
}

void sundaram_sieve(int num, int arr[])
{
    int i, j;
    for (i = 3; i < num; i += 2)  // 除去所有的非2偶数
        arr[i] = 0;
    for (i = 1; (2 * i + 1) * (2 * i + 1) <= num; i++)  // 除去奇合数
        for (j = (2 * i + 1) * (2 * i + 1); j <= num; j += 2 * i + 1)
                arr[j - 1] = 0;
}