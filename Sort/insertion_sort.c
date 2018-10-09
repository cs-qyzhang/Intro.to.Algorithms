/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : insertion_sort.c
 * author      : qiuyang Zhang
 * created     : 2018/10/08
 * description : InsertionSort Implemention
 * page        : P10
 *
 */

/*
 * 函数名称: insertion_sort
 * 函数功能: 插入排序
 * 函数输入: int A[]: 待排序数组
 *           length:  数组长度
 * 函数输出: 无
 * 函数说明: 无
 * 创建时间：2018/10/08
 *
 */
void insertion_sort(int A[], int length)
{
    int key, i;

    /*******************************
     *           算法开始
     *******************************/
    for (int j = 2; j < length; ++j)
    {
        key = A[j];
        i = j - 1;

        while (i > 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            --i;
        }
        
        A[i] = key;
    }
    /*******************************
     *           算法结束
     *******************************/
}

