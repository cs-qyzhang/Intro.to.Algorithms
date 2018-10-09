/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : sort.h
 * author      : qiuyang Zhang
 * created     : 2018/10/09
 * description : sort 函数头文件，使用 sort 函数需包含此头文件
 *
 */
#ifndef SORT_H
#define SORT_H

#include <sys/types.h>

/*
 * sort_cmp_fn_t 函数指针类型声明
 * 该函数指针声明了sort函数用于比较数组元素大小的函数原型
 *
 * 函数类型：sort_cmp_fn_t
 * 函数功能：元素比较函数
 * 函数输入：const void *a : 待比较元素a
 *           const void *b : 待比较元素b
 * 函数输出：int，返回值代表的含义为：
 *           >  0 : a > b
 *           == 0 : a == b
 *           <  0 : a < b
 * 函数说明：无
 * 创建时间：18/10/09
 *
 */
typedef int (*sort_cmp_fn_t)(const void *, const void *);

/*
 * sort_type_e 枚举类型定义
 *
 */
typedef enum sort_type
{
    SORT_ASCENDING,     // 升序排序
    SORT_DESCENDING     // 降序排序
}sort_type_e;

/*
 * sort 函数声明
 *
 * 函数名称：sort
 * 函数功能：普适排序函数
 * 函数输入：void *array           : 待排序数组
 *           size_t count          : 数组中包含的元素个数
 *           size_t size           : 每个数组元素的大小
 *           sort_type_e sort_type : 枚举，代表排序类型
 *                                  （升序 SORT_ASCENDING 或降序 SORT_DESCENDING）
 *           sort_cmp_fn_t compare : 元素比较函数
 * 函数输出：无
 * 函数说明：使用该函数需要包含 Header/sort.h 头文件
 * 创建时间：2018/10/09
 *
 */
void sort(void *array, size_t count, size_t size, sort_type_e sort_type, sort_cmp_fn_t compare);

#endif // SORT_H
