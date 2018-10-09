/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : sort.c
 * author      : qiuyang Zhang
 * created     : 2018/10/09
 * description : 
 *
 */
#include <stdlib.h>
#include <string.h>
#include "../Header/sort.h"

/*
 * 函数名称：sort
 * 函数功能：普适排序函数
 * 函数输入：void *array           : 待排序数组
 *           size_t count          : 数组中包含的元素个数
 *           size_t size           : 每个数组元素的大小
 *           sort_type_e sort_type : 枚举，代表排序类型
 *                                  （升序 SORT_ASCENDING 或降序 SORT_DESCENDING）
 *           sort_cmp_fn_t compare : 元素比较函数
 * 函数输出：无
 * 函数说明：compare 函数定义详见 Header/sort.h
 *           使用该函数需要包含 Header/sort.h 头文件
 * 创建时间：2018/10/09
 *
 */

void sort_merge(void *A, size_t size, int p, int q, int r, sort_type_e sort_type, sort_cmp_fn_t cmp)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    void *L, *R;
    L = malloc(size * n1);
    R = malloc(size * n2);

    int i, j, k;
    for (i = 0; i < n1; ++i)
        memcpy((L + i * size), (A + (p + i) * size), size);
    for (i = 0; i < n2; ++i)
        memcpy((R + i * size), (A + (q + i) * size), size);

    i = 0;
    j = 0;
    if (sort_type == SORT_ASCENDING)
    {
        for (k = p; k <= r; ++k)
        {
            if (j == n2 || cmp((L + i * size), (R + j * size)) <= 0)
            {
                memcpy((A + k * size), (L + i * size), size);
                ++i;
            }
            else
            {
                memcpy((A + k * size), (R + j * size), size);
                ++j;
            }
        }
    }
    else // sort_type == SORT_DESCENDING
    {
        for (k = p; k <= r; ++k)
        {
            if (j == n2 || cmp((L + i * size), (R + j * size)) >= 0)
            {
                memcpy((A + k * size), (L + i * size), size);
                ++i;
            }
            else
            {
                memcpy((A + k * size), (R + j * size), size);
                ++j;
            }
        }

    }
}

void sort_merge_sort(void *A, size_t size, int p, int r, sort_type_e sort_type, sort_cmp_fn_t cmp)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        sort_merge_sort(A, size, p, q, sort_type, cmp);
        sort_merge_sort(A, size, q + 1, r, sort_type, cmp);
        sort_merge(A, size, p, q, r, sort_type, cmp);
    }
}

void sort(void *array, size_t count, size_t size, sort_type_e sort_type, sort_cmp_fn_t compare)
{
    // 实现采用归并排序
    sort_merge_sort(array, size, 0, count, sort_type, compare);
}
