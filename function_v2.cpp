#include "all.h"

using namespace std;

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

void calc_ab(FILE *file, int n, double *A, double *eigen_value)
{
    cout << "start function_v2\n";
    // setting Initial vector & standarbilization
    double **u = new double *[n];
    for (int i = 0; i < n; i++)
    {
        u[i] = new double[n];
    }
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        u[0][i] = (double)rand() / RAND_MAX;
    }
    sdz(n, u[0]);

    double *v = new double[n];
    double *alpha =
        new double[n];  // Insert diagonal elements of tridiagonal matrix
    double *beta =
        new double[n];  // Insert subdiagonal elements of tridiagonal matrix
    // Insert eigenvalue when k == even & odd
    double *eigenv_even = new double[n];
    double *eigenv_odd = new double[n];
    // Insert eigenvector when k == even & odd
    double *eigenvec_even = new double[n];
    double *eigenvec_odd = new double[n];
    // Use as lapack argument. d = alpha, e = beta
    double *d = new double[n];
    double *e = new double[n];

    double beta_pow2 = 0;
    double eps = 1.0;
    int check = 1;  //"1" means eps > 1.0e-16. "0" means eps < 1.0e-16
    bool checker = true;
    int count = 0;

    for (int k = 0; k < n; k++)
    {
        if (checker)
        {
            if (k == n - 1)
            {
                // calculate v[i] = Au0(k)
                cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1.0, A, n, u[k],
                            1, 0.0, v, 1);
                // calculate alpha & beta
                alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
            }
            else
            {
                // calculate v[i] = Au0(k)
                cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1.0, A, n, u[k],
                            1, 0.0, v, 1);
                if (k == 0)
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    cblas_dscal(n, 1 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                }
                else
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -beta[k - 1], u[k - 1], 1, v, 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    cblas_dscal(n, 1 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                }
            }

            // calculate eigenvalue of A(k)

            cblas_dcopy(n, alpha, 1, d, 1);
            cblas_dcopy(n, beta, 1, e, 1);
            if (k % 2 == 0)
            {
                if (k == n - 1)
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', n, d, e, eigenvec_even,
                                  n);
                    cblas_dcopy(n, d, 1, eigenv_even, 1);
                }
                else
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', k + 2, d, e,
                                  eigenvec_even, k + 2);
                    cblas_dcopy(n, d, 1, eigenv_even, 1);
                }
            }
            else
            {
                if (k == n - 1)
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', n, d, e, eigenvec_odd,
                                  n);
                    cblas_dcopy(n, d, 1, eigenv_odd, 1);
                }
                else
                {
                    LAPACKE_dstev(LAPACK_ROW_MAJOR, 'N', k + 2, d, e,
                                  eigenvec_odd, k + 2);
                    cblas_dcopy(n, d, 1, eigenv_odd, 1);
                }
            }

            // check errors each eigenvalue of groundstates
            if (k > 0)
            {
                eps = abs(eigenv_even[0] - eigenv_odd[0]);
                if (eps > 1.0e-16)
                {
                    checker = true;
                }
                else if (eps < 1.0e-16)
                {
                    checker = false;
                    cout << "break at count = " << k << endl;
                }
            }
            cout << "count = " << k << endl;
        }
        else
        {
            cout << "break at" << k << endl;
            break;
        }
        count++;
    }
    if (count % 2 == 0)
        cblas_dcopy(n, eigenv_odd, 1, eigen_value, 1);
    else
        cblas_dcopy(n, eigenv_even, 1, eigen_value, 1);
    printf("eigen value = \n");
    printvec(n, eigen_value);
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "count = \n");
    fprintf(file, "%d\n", count);
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "eigen value = \n");
    fprintvec(file, n, eigen_value);

    cout << "end\n";
    for (int i = 0; i < n; i++)
    {
        delete u[i];
    }
    delete[] u;
    delete[] v;
    delete[] alpha;
    delete[] beta;
    delete[] eigenv_even;
    delete[] eigenv_odd;
    delete[] eigenvec_even;
    delete[] eigenvec_odd;
    delete[] d;
    delete[] e;
}