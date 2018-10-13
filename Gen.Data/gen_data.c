/*
 * Copyright 2018 qiuyang Zhang. All rights reserved.
 * 
 * filename    : gen_data.c
 * author      : qiuyang Zhang
 * created     : 2018/10/13
 * description : 产生随机数据文件
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

inline void
swap(int data[], int a, int b)
{
    if (a == b)
        return;

    data[a] = data[a] ^ data[b];
    data[b] = data[a] ^ data[b];
    data[a] = data[a] ^ data[b];
}

void
gen_data_int(int num, int begin, int end, char *filename)
{
    if (num <= 0 || begin > end)
        return;

    srand(time(NULL));

    FILE *fp;
    fp = fopen(filename, "w+");
    if (fp == NULL)
    {
        fprintf(stderr, "gen_data_int : can't open file : %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    int i, temp;
    for (i = 0; i < num; ++i)
    {
        temp = rand() % (end - begin + 1);
        temp += begin;
        fprintf(fp, "%d\n", temp);
    }

    if (!fclose(fp))
        fprintf(stderr, "gen_data_int : can't close file : %s\n", filename);
}

void
gen_data_int_diff(int num, int begin, int end, char *filename)
{
    if (num <= 0 || begin > end
        || num > (end - begin + 1))
        return;

    srand (time (NULL));

    FILE *fp;
    fp = fopen (filename, "w+");
    if (fp == NULL)
    {
        fprintf (stderr, "gen_data_int_diff : can't open file : %s\n", filename);
        exit (EXIT_FAILURE);
    }

    int data_width = end - begin + 1;
    int *data;
    data = (int *) malloc (data_width);
    if (data == NULL)
    {
        fprintf(stderr, "gen_data_int_diff : malloc error!\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < data_width; ++i)
        data[i] = i + begin;
    for (i = 0; i < data_width; ++i)
        swap(data, i, rand() % data_width);

    for (i = 0; i < num; ++i)
        fprintf(fp, "%d\n", data[i]);

    if (!fclose(fp))
    {
        fprintf(stderr, "gen_data_int_diff : can't close file : %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

