#include "all.h"
#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
using namespace std;

void printmat(int n, double *A)
{
    double mtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        cout << "[";
        // printf("[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            mtmp = A[col_num + n * row_num];
            // printf("%5.8e", mtmp);
            cout << scientific << setprecision(5) << mtmp;
            if (col_num < n - 1)
            {
                cout << "  ";
                // printf(",");
            }
        }
        if (row_num < n - 1)
        {
            cout << "];" << endl;
            // printf("];\n ");
        }
        else
        {
            cout << "]";
            // printf("]");
        }
    }
    cout << "]" << endl;
    // printf("]\n");
}

void fprintmat(ofstream &file, int n, double *A)
{
    // ofstream file(OutputFile_name, ios::app);
    double mtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        // file << "[";
        // fprintf(file, "[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            mtmp = A[col_num + n * row_num];
            file << setw(5) << setprecision(15) << left << mtmp;
            // fprintf(file, "%5.8e", mtmp);
            if (col_num < n - 1)
            {
                file << "  ";
                // fprintf(file, ",");
            }
        }
        if (row_num < n - 1)
        {
            file << endl;
            // fprintf(file, "];\n ");
        }
        else
        {
            // file << "]";
            // fprintf(file, "]");
        }
    }
    file << endl;
    // fprintf(file, "]\n");
}

void printvec(int n, double *B)
{
    double vtmp;
    cout << "[";
    // printf("[");
    for (int col_num = 0; col_num < n; col_num++)
    {
        vtmp = B[col_num];
        cout << setw(7) << scientific << setprecision(5) << left << vtmp;
        // printf("%5.8e", vtmp);
        if (col_num < n - 1)
        {
            cout << "  ";
            // printf(",");
        }
    }
    cout << "]" << endl;
    // printf("]\n");
}

void fprintvec(ofstream &file, int n, double *B)
{
    // ofstream file(OutputFile_name, ios::app);
    double vtmp;
    // fprintf(file, "[");
    for (int col_num = 0; col_num < n; col_num++)
    {
        vtmp = B[col_num];
        file << setw(17) << setprecision(15) << setw(5) << vtmp;
        // fprintf(file, "%5.8e", vtmp);
        if (col_num < n - 1)
        {
            file << "  ";
            // fprintf(file, ",");
        }
    }
    file << "\n" << endl;
    // fprintf(file, "]\n");
}

/*ベクトルを列ベクトル表示する*/
void fprintvec_col(ofstream &file, int n, double *B)
{
    // ofstream file(OutputFile_name, ios::app);
    double vtmp;
    // fprintf(file, "[");
    for (int col_num = 0; col_num < n; col_num++)
    {
        vtmp = B[col_num];
        file << setw(17) << setprecision(15) << setw(5) << vtmp << endl;
        // fprintf(file, "%5.8e", vtmp);
        if (col_num < n - 1)
        {
            file << "  ";
            // fprintf(file, ",");
        }
    }
    file << "\n" << endl;
    // fprintf(file, "]\n");
}

void print2dvec(int n, double **C)
{
    double vtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        cout << "[";
        // printf("[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            vtmp = C[row_num][col_num];
            cout << setw(7) << scientific << setprecision(5) << left << vtmp;
            // printf("%5.8e", vtmp);
            if (col_num < n - 1)
            {
                cout << "  ";
                // printf(",");
            }
        }
        if (row_num < n - 1)
        {
            cout << "];" << endl;
            // printf("];\n ");
        }
        else
        {
            cout << "]";
            printf("]");
        }
    }
    cout << "]" << endl;
    // printf("]\n");
}

void fprint2dvec(ofstream &file, int n, double **C)
{
    // ofstream file(OutputFile_name, ios::app);
    double vtmp;
    for (int row_num = 0; row_num < n; row_num++)
    {
        // fprintf(file, "[");
        for (int col_num = 0; col_num < n; col_num++)
        {
            vtmp = C[row_num][col_num];
            file << setw(17) << scientific << setprecision(15) << left << vtmp;
            // fprintf(file, "%5.8e", vtmp);
            if (col_num < n - 1)
            {
                file << "  ";
                // fprintf(file, ",");
            }
        }
        if (row_num < n - 1)
        {
            file << endl;
            // fprintf(file, "];\n ");
        }
        else
        {
            file << endl;
            // fprintf(file, "]");
        }
    }
    file << endl;
    // fprintf(file, "]\n");
}

void print_tri_diag_vec(int n, double *alpha, double *beta)
{
    double dtmp, subdtmp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i - 2; j++)
        {
            cout << setw(7) << scientific << setprecision(3) << left << 0.0
                 << "  ";
        }
        if (i == 0)
        {
            cout << setw(7) << scientific << setprecision(3) << left << alpha[i]
                 << "  " << beta[i] << "  ";
        }
        else if (i == n - 1)
        {
            cout << setw(7) << scientific << setprecision(3) << left << beta[i]
                 << "  " << alpha[i] << "  ";
        }
        else
        {
            cout << setw(7) << scientific << setprecision(3) << left << beta[i]
                 << "  " << alpha[i] << "  " << beta[i] << "  ";
        }
        for (int k = i + 2; k < n; k++)
        {
            if (k > 0)
            {
                cout << setw(7) << scientific << setprecision(3) << left << 0.0
                     << "  ";
            }
        }
        cout << endl;
    }
}

void fprint_tri_diag_vec(ofstream &file, int n, double *alpha, double *beta)
{
    double dtmp, subdtmp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i - 2; j++)
        {
            file << setw(7) << scientific << setprecision(3) << left << 0.0
                 << "  ";
        }
        if (i == 0)
        {
            file << setw(7) << scientific << setprecision(3) << left << alpha[i]
                 << "  " << beta[i] << "  ";
        }
        else if (i == n - 1)
        {
            file << setw(7) << scientific << setprecision(3) << left
                 << beta[i - 1] << "  " << alpha[i] << "  ";
        }
        else
        {
            file << setw(7) << scientific << setprecision(3) << left
                 << beta[i - 1] << "  " << alpha[i] << "  " << beta[i] << "  ";
        }
        for (int k = i + 2; k < n; k++)
        {
            if (k > 0)
            {
                file << setw(7) << scientific << setprecision(3) << left << 0.0
                     << "  ";
            }
        }
        file << endl;
    }
}