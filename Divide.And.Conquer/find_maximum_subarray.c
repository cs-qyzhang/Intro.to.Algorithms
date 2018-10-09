/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : find_maximum_subarray.c
 * author      : qiuyang Zhang
 * created     : 2018/10/08
 * description : Find Maximum Subarray Implemention
 * page        : P40
 *
 */
#include <stdlib.h>
#include <limits.h>

void find_max_crossing_subarray(int A[], int low, int mid, int high,
                                int *max_left, int *max_right, int *max_sum)
{
    /*max_left = (int *)malloc(sizeof(int));*/
    /*max_right = (int *)malloc(sizeof(int));*/
    /*max_sum = (int *)malloc(sizeof(int));*/

    int left_sum  = INT_MIN;
    int right_sum = INT_MIN;
    int sum       = 0;
    int i;

    for (i = mid; i >= low; --i)
    {
        sum += A[i];
        if (sum >= left_sum)
        {
            left_sum  = sum;
            *max_left = i;
        }
    }

    sum = 0;
    for (i = mid; i <= high; ++i)
    {
        sum += A[i];
        if (sum >= right_sum)
        {
            right_sum  = sum;
            *max_right = i;
        }
    }

    *max_sum = left_sum + right_sum;
}

void find_maximum_subarray(int A[], int low, int high,
                           int *left, int *right, int *sum)
{
    if (low == high)
    {
        *left  = low;
        *right = high;
        *sum   = A[low];
    }
    else
    {
        int mid;
        int left_low, left_high, left_sum;
        int right_low, right_high, right_sum;
        int cross_low, cross_high, cross_sum;

        mid = (low + high) / 2;
        find_maximum_subarray(A, low, mid - 1, &left_low, &left_high, &left_sum);
        find_maximum_subarray(A, mid, high, &right_low, &right_high, &right_sum);
        find_max_crossing_subarray(A, low, mid, high, &cross_low, &cross_high, &cross_sum);

        if (left_sum >= right_sum && left_sum >= cross_sum)
        {
            *left  = left_low;
            *right = left_high;
            *sum   = left_sum;
        }
        else if (right_sum >= left_sum && right_sum >> cross_sum)
        {
            *left  = right_low;
            *right = right_high;
            *sum   = right_sum;
        }
        else
        {
            *left  = cross_low;
            *right = cross_high;
            *sum   = cross_sum;
        }
    }
}
