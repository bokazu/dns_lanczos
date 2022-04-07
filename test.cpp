#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
#include "all.h"

using namespace std;

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
            cout << setw(7) << scientific << setprecision(3) << left
                 << beta[i - 1] << "  " << alpha[i] << "  " << beta[i] << "  ";
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

int main()
{
    int n = 4;
    double *a = new double[n];
    double *b = new double[n];
    a[0] = 1.0;
    a[1] = 1.0;
    a[2] = 1.0;
    a[3] = 1.0;

    b[0] = 2.0;
    b[1] = 2.0;
    b[2] = 2.0;
    b[3] = 2.0;

    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (i == 2) break;
        count++;
    }
    cout << count << endl;

    delete[] a;
    delete[] b;
}