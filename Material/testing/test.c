#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// #include <common.h>
#include "cblas.h"

void print_arr(int N, char * name, double * array);
void init_arr(int N, double * a);
void Dgemm_multiply(double * a, double * b, double * c, int N);
void Dgemv_multiply(double * a, double * b, double * c, int N);
void Ddot_multiply(double * a, double * b, double * c, int N);
void Yours_multiply(double * a, double * b, double * c, int N);

int main(int argc, char const * argv[])
{
    clock_t start, stop;
    int i, j;
    int N;
    double * a;
    double * b;
    double * c;
    if (argc < 2)
    {
        printf("Enter matrix size N=");
        scanf("%d", &N);
    }
    else
        N = atoi(argv[1]);
    a = (double *) malloc(sizeof (double) * N * N);
    b = (double *) malloc(sizeof (double) * N * N);
    c = (double *) malloc(sizeof (double) * N * N);
    
    init_arr(N, a);
    init_arr(N, b);
    
    start = clock();
    Yours_multiply(a, b, c, N);
    stop = clock();
    printf("roll your own multiply(). Elapsed time = %g seconds.\n"
            , ((double) (stop - start)) / CLOCKS_PER_SEC);
    if (N < 7)
    {
        print_arr(N, "a", a);
        print_arr(N, "b", b);
        print_arr(N, "c", c);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}

void Yours_multiply(double * a, double * b, double * c, int N)
{
    Dgemm_multiply(a, b, c, N);
}

void Dgemm_multiply(double * a, double * b, double * c, int N)
{
    int i;
    double alpha = 1.0, beta = 0;
    int incx = 1, incy = N;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N,
            alpha, b, N, a, N, beta, c, N);
}

void init_arr(int N, double * a)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {

            a[i * N + j] = (i + j + 1) % 10;
        }
    }
}

void print_arr(int N, char * name, double * array)
{
    int i, j;
    printf("\n%s\n", name);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%g\t", array[N * i + j]);
        }
        puts("");
    }
}

