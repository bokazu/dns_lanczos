#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
#include "all.h"

using namespace std;

lapack_int LAPACKE_dsyev(int matrix_layout, char jobz, char uplo, lapack_int n,
                         double *a, lapack_int lda, double *w);

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

int main()
{
    int n = 1000;
    double *A = new double[n * n];
    double *eigen_value = new double[n];
    double *lw = new double[n];

    // Setting Matrix(Column Major)
    /************************************Method1****************************************/
    /**************************サンプルファイルから読み込む*******************************/
    // string filename("sample/sample1.txt");
    // double number;

    // ifstream sample_file(filename);
    // if (!sample_file.is_open())
    // {
    //     cerr << "Could not open the file - '" << filename << "'" << endl;
    //     return EXIT_FAILURE;
    // }

    // int dim2 = 0;
    // int num = 0;
    // while (sample_file >> number)
    // {
    //     A[num] = number;
    //     num++;
    // }
    // sample_file.close();

    FILE *file;
    file = fopen("output3.txt", "w");
    if (file == NULL)
    {
        // fopen失敗
        // streamにstdout指定なので実質printfと同じ
        fprintf(stdout, "fopen error fp[%p]\n", file);
        return -1;
    }

    /**********************************Method2****************************************/
    /******************乱数を使用して実対称行列を作成する。******************************/
    make_mat(n, A);
    printf("A = \n");
    // printmat(n, A);
    // printf("\n");
    fprintf(file, "A = \n");
    fprintmat(file, n, A);
    fprintf(file, "\n");
    /**************************Lanczos法使用&lapackで対角化***************************/
    calc_ab(file, n, A, eigen_value);

    /********************行列そのものをlapackeに投げる。*****************/
    LAPACKE_dsyev(LAPACK_ROW_MAJOR, 'N', 'U', n, A, n, lw);
    printf("LAPACKE's ANSWER\n");
    printf("eigen value = \n");
    printvec(n, lw);

    fprintf(file, "LAPACKE's ANSWER\n");
    fprintf(file, "eigen value = \n");
    fprintvec(file, n, lw);

    delete[] A;
    delete[] eigen_value;
    delete[] lw;
    fclose(file);
}