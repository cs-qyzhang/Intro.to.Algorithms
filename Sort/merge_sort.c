/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : merge_sort.c
 * author      : qiuyang Zhang
 * created     : 2018/10/08
 * description : MergeSort Implemention
 * page        : P17
 *
 */
#include <stdlib.h>
#include <limits.h>

/*
 * 函数名称：merge
 * 函数功能：将两个连续的排好序的数组合并为一个数组
 * 函数输入：int A[] : 所有数据所在的数组(包括两个排好序的数组)
 *           int p   : 待排序数组起始下标
 *           int q   : 第一个数组的结束下标
 *           int r   : 第二个数组的结束下标
 * 函数输出：int A[] : 排好序后的元素放回原来的A[p]-A[r]中
 * 函数说明：无
 * 创建时间：2018/10/08
 *
 */
void merge(int A[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L, *R;
    L = (int *)malloc(sizeof(int) * (n1 + 1));
    R = (int *)malloc(sizeof(int) * (n2 + 1));

    int i, j, k;
    for (i = 0; i < n1; ++i)
        L[i] = A[p + i];
    for (i = 0; i < n2; ++i)
        R[i] = A[q + i];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0;
    j = 0;
    for (k = p; k <= r; ++k)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            ++i;
        }
        else
        {
            A[k] = R[j];
            ++j;
        }
    }
}

/*
 * 函数名称：merge_sort
 * 函数功能：归并排序
 * 函数输入：int A[] : 待排序的数组
 *           int p   : 待排序的数组的起始下标
 *           int r   : 待排序的数组的结束下标
 * 函数输出：int A[] : 排好序后的元素放回原来的A[p]-A[r]中
 * 函数说明：无
 * 创建时间：2018/10/08
 *
 */
void merge_sort(int A[], int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
