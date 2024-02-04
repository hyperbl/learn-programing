/*Sorting_Algorithms.c -- 记录各种各样的排序算法
注：本文中对数组进行的都是升序排序*/
#include <stdio.h>
#include <stdlib.h>

void selection_sort(int ar[], int size);    /*选择排序*/
void direct_insert_sort(int ar[], int size);    /*直接插入排序*/
void bubble_sort(int ar[], int size);   /*冒泡排序*/
void merge_sort(int ar[], int copy[], int start, int end);  /*归并排序*/
void quick_sort(int ar[], int start, int end); /*快速排序*/

int main()
{
    int n_input;
    scanf("%d", &n_input);
    int array[n_input], array_copy[n_input];

    for (int i = 0; i < n_input; i++)   /*读取数组*/
        scanf("%d", array + i);

    //selection_sort(array, n_input);
    //direct_insert_sort(array, n_input);
    //bubble_sort(array, n_input);
    merge_sort(array, array_copy, 0, n_input - 1);
    //quick_sort(array, 0, n_input - 1);

    for (int i = 0; i < n_input; i++)   /*输出结果*/
        printf("%d ", array[i]);
    printf("\b\n");

    system("pause");
    return 0;
}

void selection_sort(int ar[], int size)
{
    int temp, p;
    for (int i = 0; i < size - 1; i++)
    {
        p = i;
        for (int j = i + 1; j < size; j++)
            if (ar[p] > ar[j])
                p = j;
        if (i != p)
        {
            temp = ar[p];
            ar[p] = ar[i];
            ar[i] = temp;
        }
    }
}

void direct_insert_sort(int ar[], int size)
{
    int temp, i, j;

    for (i = 1; i < size; i++)
    {
        temp = ar[i];
        for (j = i - 1; j >= 0 && ar[j] > temp; j--)
            ar[j + 1] = ar[j];
        ar[j + 1] = temp;
    }
}

void bubble_sort(int ar[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (ar[j] > ar[j + 1])
            {
                temp = ar[j];ar[j] = ar[j + 1]; ar[j + 1] = temp;
            }
}

void merge_sort(int ar[], int copy[], int start, int end)
{
    if (end <= start) return;
    int mediate = start + ((end - start) >> 1);
    merge_sort(ar, copy, start, mediate);
    merge_sort(ar, copy, mediate + 1, end);
    int pi = start, index_l = start, index_r = mediate + 1;
    while ((index_l <= mediate) && (index_r <= end))
        if (ar[index_l] < ar[index_r])
            copy[pi++] = ar[index_l++];
        else
            copy[pi++] = ar[index_r++];
    while (index_l <= mediate)
        copy[pi++] = ar[index_l++];
    while (index_r <= end)
        copy[pi++] = ar[index_r++];
    for (int i = start; i <= end; i++)  
        ar[i] = copy[i];
}

void quick_sort(int ar[], int start, int end)
{   
    if (start >= end)
        return;
    int base = ar[start], index = start;
    int left = start, right = end;
    while (left < right)
    {
        while (right > left)
        {
            if (ar[right] < base)
            {
                index = right;
                ar[left++] = ar[right];
                break;
            }
            right--;
        }
        while (left < right)
        {
            if (ar[left] > base)
            {
                index = left;
                ar[right--] = ar[left];
                break;
            }
            left++;
        }
    }
    ar[index] = base;
    quick_sort(ar, start, index - 1);
    quick_sort(ar, index + 1, end);
}