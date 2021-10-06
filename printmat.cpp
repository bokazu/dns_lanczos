#include "all.h"
#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
using namespace std;

void printmat(int n, double *A)
{
    double mtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        printf("[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            mtmp = A[col_num + n * row_num];
            printf("%5.8e", mtmp);
            if (col_num < n - 1)
            {
                printf(",");
            }
        }
        if (row_num < n - 1)
        {
            printf("];\n ");
        }
        else
        {
            printf("]");
        }
    }
    printf("]\n");
}

void fprintmat(FILE *file, int n, double *A)
{
    double mtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        fprintf(file, "[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            mtmp = A[col_num + n * row_num];
            fprintf(file, "%5.8e", mtmp);
            if (col_num < n - 1)
            {
                fprintf(file, ",");
            }
        }
        if (row_num < n - 1)
        {
            fprintf(file, "];\n ");
        }
        else
        {
            fprintf(file, "]");
        }
    }
    fprintf(file, "]\n");
}

void printvec(int n, double *B)
{
    double vtmp;
    printf("[");
    for (int col_num = 0; col_num < n; col_num++)
    {
        vtmp = B[col_num];
        printf("%5.8e", vtmp);
        if (col_num < n - 1)
        {
            printf(",");
        }
    }
    printf("]\n");
}

void fprintvec(FILE *file, int n, double *B)
{
    double vtmp;
    fprintf(file, "[");
    for (int col_num = 0; col_num < n; col_num++)
    {
        vtmp = B[col_num];
        fprintf(file, "%5.8e", vtmp);
        if (col_num < n - 1)
        {
            fprintf(file, ",");
        }
    }
    fprintf(file, "]\n");
}

void print2dvec(int n, double **C)
{
    double vtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        printf("[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            vtmp = C[row_num][col_num];
            printf("%5.8e", vtmp);
            if (col_num < n - 1)
            {
                printf(",");
            }
        }
        if (row_num < n - 1)
        {
            printf("];\n ");
        }
        else
        {
            printf("]");
        }
    }
    printf("]\n");
}

void fprint2dvec(FILE *file, int n, double **C)
{
    double vtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        fprintf(file, "[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            vtmp = C[row_num][col_num];
            fprintf(file, "%5.8e", vtmp);
            if (col_num < n - 1)
            {
                fprintf(file, ",");
            }
        }
        if (row_num < n - 1)
        {
            fprintf(file, "];\n ");
        }
        else
        {
            fprintf(file, "]");
        }
    }
    fprintf(file, "]\n");
}