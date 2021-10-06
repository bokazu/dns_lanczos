#include "all.h"

using namespace std;

void gso(int n, int k, double** u)
{
    double cef;
    for (int try_num = 0; try_num < k - 1; try_num++)
    {
        cef = -1.0 * cblas_ddot(n, u[try_num], 1, u[k + 1], 1);
        cblas_daxpy(n, cef, u[try_num], 1, u[k + 1], 1);
    }
}

void sdz(int n, double* v)
{
    double a = 1. / cblas_dnrm2(n, v, 1);
    cblas_dscal(n, a, v, 1);

    // Check norm
    double norm = cblas_dnrm2(n, v, 1);
    double eps = abs(1.0 - norm);
    if (eps > 1.0e-14)
    {
        printf("\x1b[31m NORM ERROR\x1b[39m\n");
    }
}