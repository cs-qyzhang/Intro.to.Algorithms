/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : find_min_distance_between_two_points.c
 * author      : qiuyang Zhang
 * created     : 2018/10/08
 * description : 寻找最近点对
 * page        : P610
 *
 */
#include <stdlib.h>
#include <stddef.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include "../Header/declerations.h"
#include "../Header/point.h"

inline double point_distance(struct point *a, struct point *b)
{
    return (sqrt(pow(a->x, 2) + pow(b->x, 2)));
}

/*
 * 函数名称：find_min_distance_between_two_points
 * 函数功能：寻找由左边区域的点和右边区域的点组成的最近点对
 * 函数输入：struct point *P[]  : 平面上的所有点集
 *           int num            : 带状区域中点的数量
 *           int y_sort_index[] : 按照y坐标降序排列的带状区域中的点在点集中的下标
 *           double left_min    : 左边区域中求出的最近点对的距离
 *           double right_min   : 右边区域中求出的最近点对的距离
 * 函数输出：struct point *a    : 在跨界区域找到的最近点对之一
 *           struct point *b    : 在跨界区域找到的最近点对之一
 *           double *distance   : 在跨界区域找到的最近点对的距离
 */
void find_min_cross_line(struct point *P[], int num, int y_sort_index[],
                         struct point *a, struct point *b, double *distance)
{

    double a_b_dis;                // 计算两点间距离的中间变量
    int i, j;
    *distance = DBL_MAX;
    for (i = 0; i < num - 1; ++i)
    {
        for (j = i + 1; j <= i + 7; ++j)
        {
            if (j >= num)
                break;
            a_b_dis = point_distance(P[y_sort_index[i]],
                                     P[y_sort_index[j]]);
            if (a_b_dis <= *distance)
            {
                a         = P[y_sort_index[i]];
                b         = P[y_sort_index[j]];
                *distance = a_b_dis;
            }
        }
    }
}

/*
 * 函数名称：find_min_distance
 * 函数功能：递归寻找给定点集中的最近点对
 * 函数输入：struct point *P[]  : 平面上的所有点集
 *           int num            : 给定点集的数量
 *           int x_sort_index[] : 按照x坐标升序排列的带状区域中的点在点集中的下标
 *           int y_sort_index[] : 按照y坐标降序排列的带状区域中的点在点集中的下标
 * 函数输出：struct point *a    : 在点集中找到的最近点对之一
 *           struct point *b    : 在点集中找到的最近点对之一
 *           double *distance   : 在点集中找到的最近点对的距离
 */
void find_min_distance(struct point *P[], int num, int x_sort_index[], int y_sort_index[],
                       struct point *a, struct point *b, double *distance)
{
    if (num <= 0)
    {
        a         = NULL;
        b         = NULL;
        *distance = -1.0;
    }
    else if (num == 1)
    {
        a         = P[x_sort_index[0]];
        b         = P[x_sort_index[0]];
        *distance = 0.0;
    }
    else if (num == 2)
    {
        a = P[x_sort_index[0]];
        b = P[x_sort_index[1]];
        *distance = point_distance(a, b);
    }
    else if (num <= 3)
    {
        double a_b_dis;
        double b_c_dis;
        double a_c_dis;

        a_b_dis = point_distance(P[x_sort_index[0]], P[x_sort_index[1]]);
        a_c_dis = point_distance(P[x_sort_index[0]], P[x_sort_index[2]]);
        b_c_dis = point_distance(P[x_sort_index[1]], P[x_sort_index[2]]);

        if (a_b_dis >= a_c_dis && a_b_dis >= b_c_dis)
        {
            a         = P[x_sort_index[0]];
            b         = P[x_sort_index[1]];
            *distance = a_b_dis;
        }
        else if (a_c_dis >= a_b_dis && a_c_dis >= b_c_dis)
        {
            a         = P[x_sort_index[0]];
            b         = P[x_sort_index[2]];
            *distance = a_c_dis;
        }
        else
        {
            a         = P[x_sort_index[1]];
            b         = P[x_sort_index[2]];
            *distance = b_c_dis;
        }
    }
    else
    {
        int left_num, right_num;
        left_num  = (num + 1) / 2;
        right_num = num - left_num;

        double left_min, right_min, cross_min;
        struct point *left_a, *left_b, *right_a, *right_b, *cross_a, *cross_b;
        find_min_distance(P, left_num, x_sort_index, y_sort_index,
                          left_a, left_b, &left_min);
        find_min_distance(P, right_num, x_sort_index + left_num, y_sort_index,
                          right_a, right_b, &right_min);

        double known_min;
        int cross_y_sort_index[200];
        int i, j;
        double line_x;

        known_min = (left_min <= right_min) ? left_min : right_min;
        line_x    = P[x_sort_index[left_num - 1]]->x;
        j         = 0;
        for (i = 0; i < num; ++i)
        {
            if (P[y_sort_index[i]]->x >= line_x - known_min
                    && P[y_sort_index[i]]->x <= line_x + known_min)
                cross_y_sort_index[j++] = y_sort_index[i];
        }

        find_min_cross_line(P, j, cross_y_sort_index,
                            cross_a, cross_b, &cross_min);

        if (left_min <= right_min && left_min <= cross_min)
        {
            a         = left_a;
            b         = left_b;
            *distance = left_min;
        }
        else if (right_min <= left_min && right_min <= cross_min)
        {
            a         = right_a;
            b         = right_b;
            *distance = right_min;
        }
        else
        {
            a         = cross_a;
            b         = cross_b;
            *distance = cross_min;
        }
    }
}

void find_min_distance_between_two_points(struct point *P, struct point *a, struct point *b, double *distance)
{

}
