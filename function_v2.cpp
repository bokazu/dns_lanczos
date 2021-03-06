#include "all.h"

using namespace std;

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

void calc_ab(ofstream &file, int n, double *A, double *eigen_value)
{
    std::cout << "start function_v2\n";
    // setting Initial vector & standarbilization
    double **u = new double *[n];
    for (int i = 0; i < n; i++)
    {
        u[i] = new double[n];
    }
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            u[i][j] = 0.0;
            u[j][i] = 0.0;
        }
    }

    /*初期ベクトルの決定*/
    random_device rnd;
    mt19937 mt(rnd());  //メルセンヌ・ツイスタを利用
    uniform_real_distribution<> rand01(0, 1);
    for (int i = 0; i < n; i++)
    {
        u[0][i] = rand01(mt);
    }
    sdz(n, u[0]);
    file << "u[0] = " << endl;
    fprintvec(file, n, u[0]);

    double *v = new double[n];
    vec_init(n, v);
    double *alpha =
        new double[n];  // Insert diagonal elements of tridiagonal matrix
    vec_init(n, alpha);
    double *beta =
        new double[n - 1];  // Insert subdiagonal elements of tridiagonal matrix
    vec_init(n - 1, beta);
    // Insert eigenvalue when k == even & odd
    double *eigenv_even = new double[n];
    vec_init(n, eigenv_even);
    double *eigenv_odd = new double[n];
    vec_init(n, eigenv_odd);
    // Insert eigenvector when k == even & odd
    double *eigenvec_even = new double[n];
    vec_init(n, eigenvec_even);
    double *eigenvec_odd = new double[n];
    vec_init(n, eigenvec_odd);
    // Use as lapack argument. d = alpha, e = beta
    double *d = new double[n];
    vec_init(n, d);
    double *e = new double[n - 1];
    vec_init(n - 1, e);

    double beta_pow2 = 0.;
    double eps = 1.0;
    int check = 1;  //"1" means eps > 1.0e-16. "0" means eps < 1.0e-16
    bool checker = true;
    int count = 0;

    for (int k = 0; k < n; k++)
    {
        if (k > 0) count++;
        vec_init(n, v);
        file << "loop count = " << k << endl;
        if (checker)
        {
            if (k == n - 1)
            {
                // calculate v[i] = Au0(k)
                cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1.0, A, n, u[k],
                            1, 0.0, v, 1);
                file << "\n"
                     << "v = Au = " << endl;
                fprintvec(file, n, v);
                // calculate alpha & beta
                alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                file << "\n"
                     << "tri_diag_matrix = " << endl;
                fprint_tri_diag_vec(file, n, alpha, beta);
            }
            else
            {
                // calculate v[i] = Au0(k)
                cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1.0, A, n, u[k],
                            1, 0.0, v, 1);
                file << "v = Au = " << endl;
                fprintvec(file, n, v);
                if (k == 0)
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    file << "\n"
                         << "tri_diag_matrix = " << endl;
                    fprint_tri_diag_vec(file, n, alpha, beta);
                    cblas_dscal(n, 1 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                    file << "\n"
                         << "u[k+1] = " << endl;
                    fprintvec(file, n, u[k + 1]);
                }
                else
                {
                    alpha[k] = cblas_ddot(n, v, 1, u[k], 1);
                    cblas_daxpy(n, -beta[k - 1], u[k - 1], 1, v, 1);
                    cblas_daxpy(n, -alpha[k], u[k], 1, v, 1);
                    beta[k] = cblas_dnrm2(n, v, 1);
                    file << "\n"
                         << "tri_diag_matrix = " << endl;
                    fprint_tri_diag_vec(file, n, alpha, beta);
                    cblas_dscal(n, 1.0 / beta[k], v, 1);
                    cblas_dcopy(n, v, 1, u[k + 1], 1);
                    gso(n, k, u);
                    sdz(n, u[k + 1]);
                    file << "\n"
                         << "u[k+1] = " << endl;
                    fprintvec(file, n, u[k + 1]);
                }
            }

            // calculate eigenvalue of A(k)

            cblas_dcopy(n, alpha, 1, d, 1);
            cblas_dcopy(n - 1, beta, 1, e, 1);
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
                if (eps > 1.0e-15)
                {
                    checker = true;
                }
                else if (eps < 1.0e-15)
                {
                    checker = false;
                    // cout << "break at count = " << k << endl;
                }
            }
            // cout << "count = " << k << endl;
        }
        else
        {
            cout << "break at" << k << endl;
            break;
        }
    }
    if (count % 2 == 0)
        cblas_dcopy(n, eigenv_even, 1, eigen_value, 1);
    else
        cblas_dcopy(n, eigenv_odd, 1, eigen_value, 1);
    // printf("my eigen value = \n");
    printvec(n, eigen_value);
    // fprintf(file, "\n");
    // fprintf(file, "\n");
    file << "count = " << endl;
    // fprintf(file, "count = \n");
    file << count << endl;
    // fprintf(file, "%d\n", count);
    file << endl;
    // fprintf(file, "\n");
    file << endl;
    // fprintf(file, "\n");
    file << "eigen value = " << endl;
    // fprintf(file, "eigen value = \n");

    fprintvec_col(file, n, eigen_value);

    std::cout << "end\n";
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