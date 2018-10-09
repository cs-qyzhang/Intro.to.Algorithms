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
#include "../Header/point.h"
#include "../Header/sort.h"

inline double point_distance(struct point *a, struct point *b);
int point_x_compare(const void *a, const void *b);
int point_y_compare(const void *a, const void *b);
void find_min_distance(struct point *P_x_sort[], struct point *P_y_sort[], int num,
                       struct point *a, struct point *b, double *distance);
void find_min_cross_line(struct point *P_y_sort[], int num,
                         struct point *a, struct point *b, double *distance);

/*
 * 函数名称：find_min_distance_between_two_points
 * 函数功能：寻找给定点集中的最近点对及其距离
 * 函数输入：struct point *P[] : 二维点集
 * 　　　　　int num           : 点集中的点数
 * 函数输出：struct point *a   : 最近点对中的一个点
 *           struct point *b   : 最近点对中的另一个点
 *           double *distance  : 最近点对的距离
 * 函数说明：无
 * 创建时间：2018/10/09
 *
 */
void find_min_distance_between_two_points(struct point *P[], int num, struct point *a, struct point *b, double *distance)
{
    struct point **P_x_sort, **P_y_sort;

    P_x_sort = (struct point **)malloc(sizeof(struct point *) * num);
    P_y_sort = (struct point **)malloc(sizeof(struct point *) * num);

    int i;
    for (i = 0; i < num; ++i)
    {
        P_x_sort[i] = P[i];
        P_y_sort[i] = P[i];
    }

    sort(P_x_sort, num, sizeof(struct point), SORT_ASCENDING, point_x_compare);
    sort(P_y_sort, num, sizeof(struct point), SORT_DESCENDING, point_y_compare);

    find_min_distance(P_x_sort, P_y_sort, num, a, b, distance);
}

/*
 * 函数名称：point_x_compare
 * 函数功能：二维点x坐标比较函数
 * 函数输入：const void *a : 待比较的第一个点
 *           const void *b : 待比较的第二个点
 * 函数输出：int, 返回值的含义如下
 *           <  0 : 点a的x坐标小于点b的x坐标
 *           == 0 : 点a的x坐标等于点b的x坐标
 *           >  0 : 点a的x坐标大于点b的x坐标
 * 函数说明：该函数用于sort函数的参数
 * 创建时间：2018/10/09
 *
 */
int point_x_compare(const void *a, const void *b)
{
    struct point *pa, *pb;
    pa = (struct point *)a;
    pb = (struct point *)b;

    return (pa->x - pb->x);
}

/*
 * 函数名称：point_y_compare
 * 函数功能：二维点y坐标比较函数
 * 函数输入：const void *a : 待比较的第一个点
 *           const void *b : 待比较的第二个点
 * 函数输出：int, 返回值的含义如下
 *           <  0 : 点a的y坐标小于点b的y坐标
 *           == 0 : 点a的y坐标等于点b的y坐标
 *           >  0 : 点a的y坐标大于点b的y坐标
 * 函数说明：该函数用于sort函数的参数
 * 创建时间：2018/10/09
 *
 */
int point_y_compare(const void *a, const void *b)
{
    struct point *pa, *pb;
    pa = (struct point *)a;
    pb = (struct point *)b;

    return (pa->y - pb->y);
}

/*
 * 函数名称：point_distance
 * 函数功能：求二维平面中两点的距离
 * 函数输入：struct point *a : 第一个点
 *           struct point *b : 第二个点
 * 函数输出：double, 代表两点间的距离
 * 函数说明：无
 * 创建时间：2018/10/09
 *
 */
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
 * 函数说明：无
 * 创建时间：2018/10/08
 */
void find_min_cross_line(struct point *P_y_sort[], int num,
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
            a_b_dis = point_distance(P_y_sort[i],
                                     P_y_sort[j]);
            if (a_b_dis <= *distance)
            {
                a         = P_y_sort[i];
                b         = P_y_sort[j];
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
 * 函数说明：无
 * 创建时间：2018/10/08
 */
void find_min_distance(struct point *P_x_sort[], struct point *P_y_sort[], int num,
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
        a         = P_x_sort[0];
        b         = P_x_sort[0];
        *distance = 0.0;
    }
    else if (num == 2)
    {
        a = P_x_sort[0];
        b = P_x_sort[1];
        *distance = point_distance(a, b);
    }
    else if (num <= 3)
    {
        double a_b_dis;
        double b_c_dis;
        double a_c_dis;

        a_b_dis = point_distance(P_x_sort[0], P_x_sort[1]);
        a_c_dis = point_distance(P_x_sort[0], P_x_sort[2]);
        b_c_dis = point_distance(P_x_sort[1], P_x_sort[2]);

        if (a_b_dis >= a_c_dis && a_b_dis >= b_c_dis)
        {
            a         = P_x_sort[0];
            b         = P_x_sort[1];
            *distance = a_b_dis;
        }
        else if (a_c_dis >= a_b_dis && a_c_dis >= b_c_dis)
        {
            a         = P_x_sort[0];
            b         = P_x_sort[2];
            *distance = a_c_dis;
        }
        else
        {
            a         = P_x_sort[1];
            b         = P_x_sort[2];
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
        find_min_distance(P_x_sort, P_y_sort, left_num,
                          left_a, left_b, &left_min);
        find_min_distance(P_x_sort + left_num, P_y_sort, right_num,
                          right_a, right_b, &right_min);

        double known_min;
        struct point *cross_y_sort_index[200];
        int i, j;
        double line_x;

        known_min = (left_min <= right_min) ? left_min : right_min;
        line_x    = P_x_sort[left_num - 1]->x;
        j         = 0;
        for (i = 0; i < num; ++i)
        {
            if (P_y_sort[i]->x >= line_x - known_min
                    && P_y_sort[i]->x <= line_x + known_min)
                cross_y_sort_index[j++] = P_y_sort[i];
        }

        find_min_cross_line(cross_y_sort_index, j,
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

