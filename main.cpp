#define _CRT_SECURE_NO_WARNINGS /*fopen関数を呼び出すためのstdio.hをincludeする前にこれが必要。*/
#include "all.h"

using namespace std;

lapack_int LAPACKE_dsyev(int matrix_layout, char jobz, char uplo, lapack_int n,
                         double *a, lapack_int lda, double *w);

lapack_int LAPACKE_dstev(int matrix_order, char jobz, lapack_int n, double *d,
                         double *e, double *z, lapack_int ldz);

int main()
{
    int n;
    double *A = new double[n * n];
    double *eigen_value = new double[n];
    double *lw = new double[n];

    // Setting Matrix(Column Major)
    /************************************Method1****************************************/
    /**************************サンプルファイルから読み込む*******************************/
    string set_matsize_file = "set_matrixsize.txt";
    string set_filename = "set_filename.txt";

    ifstream set_matsize(set_matsize_file);
    ifstream set_file(set_filename);

    string sample_filename;
    string output_filename;
    ofstream output_file(output_filename);
    // ifstream setting_file(setting_filename);
    if (!(set_matsize))
    {
        cerr << "Could not open the file(line 31) - '" << set_matsize_file
             << "'" << endl;
        return EXIT_FAILURE;
    }
    set_matsize >> n;
    if (!(set_file))
    {
        cerr << "Could not open the file(line 31) - '" << set_filename << "'"
             << endl;
        return EXIT_FAILURE;
    }
    int count = 0;
    while (!set_file.eof())
    {
        string tmp;
        getline(set_filename, tmp);
        if (count == 0)
        {
            sample_filename = tmp;
        }
        else
        {
            output_filename = tmp;
        }
        count++;
    }

    double number;

    ifstream sample_file(sample_filename);
    if (!sample_file.is_open())
    {
        cerr << "Could not open the file - '" << sample_filename << "'" << endl;
        return EXIT_FAILURE;
    }

    int dim2 = 0;
    int num = 0;
    while (sample_file >> number)
    {
        A[num] = number;
        num++;
    }
    sample_file.close();

    if (!output_file)
    {
        cerr << "Could not open the file - '" << sample_filename << "'" << endl;
        return EXIT_FAILURE;
    }

    /**********************************Method2****************************************/
    /******************乱数を使用して実対称行列を作成する。******************************/
    // make_mat(n, A);
    // printf("A = \n");
    // // printmat(n, A);
    // // printf("\n");
    // fprintf(file, "A = \n");
    // fprintmat(file, n, A);
    // fprintf(file, "\n");
    /**************************Lanczos法使用&lapackで対角化***************************/
    calc_ab(file, n, A, eigen_value);

    /********************行列そのものをlapackeに投げる。*****************/
    // LAPACKE_dsyev(LAPACK_COL_MAJOR, 'N', 'U', n, A, n, lw);
    // printf("LAPACKE's ANSWER\n");
    // printf("eigen value = \n");
    // printvec(n, lw);

    // fprintf(file, "LAPACKE's ANSWER\n");
    // fprintf(file, "eigen value = \n");
    // fprintvec(file, n, lw);

    delete[] A;
    delete[] eigen_value;
    delete[] lw;
    fclose(file);
}