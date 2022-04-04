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

    /********************************サンプルファイルから読み込み*************************************/
    string matsize_file = "set_model/set_matrixsize.txt";
    string filename = "set_model/set_filename.txt";

    /**********************************行列サイズの取得**********************************/
    ifstream set_matsize(matsize_file);
    if (!(set_matsize))
    {
        cerr << "Could not open the file(line 31) - '" << matsize_file << "'"
             << endl;
        return EXIT_FAILURE;
    }
    set_matsize >> n;
    cout << n << endl;
    set_matsize.close();

    double *A = new double[n * n];
    double *eigen_value = new double[n];
    double *lw = new double[n];

    vec_init(n * n, A);
    vec_init(n, eigen_value);
    vec_init(n, lw);

    /**************************************ファイル名の取得***************************************/
    ifstream set_file(filename);
    if (!(set_file))
    {
        cerr << "Could not open the file(line 31) - '" << filename << "'"
             << endl;
        return EXIT_FAILURE;
    }
    int file_line_count = 0;
    string filename_tmp;
    string SampleFile_name, OutputFile_name;
    string ground_state_check = "ground_state_check.txt";
    while (!set_file.eof())
    {
        getline(set_file, filename_tmp);
        if (file_line_count == 0)
        {
            SampleFile_name = filename_tmp;
            // cout << "Sample file name :" << SampleFile_name << endl;
            file_line_count += 1;
        }
        else if (file_line_count == 1)
        {
            OutputFile_name = filename_tmp;
            // cout << "Output file name :" << OutputFile_name << endl;
        }
    }
    set_file.close();

    /*Hamiltonianの行列要素の情報の取得(密行列形式)*/
    int dim2 = 0;
    int num = 0;
    double number;
    ifstream sample_file(SampleFile_name);
    while (sample_file >> number)
    {
        A[num] = number;
        num++;
    }
    sample_file.close();
    printmat(n, A);

    ofstream output(OutputFile_name);
    ofstream ground_state(ground_state_check);
    fprintmat(output, n, A);

    /*Lanczos法とLAPACKで対角化*/
    calc_ab(output, n, A, eigen_value);

    /*行列そのものをLAPACKに投げる*/
    LAPACKE_dsyev(LAPACK_COL_MAJOR, 'N', 'U', n, A, n, lw);
    // printf("LAPACKE's ANSWER\n");
    // printf("eigen value = \n");
    // printvec(n, lw);

    // fprintf(OutputFile_name, "LAPACKE's ANSWER\n");

    // fprintf(OutputFile_name, "eigen value = \n");
    output << "LAPACKE's ANSWER\n";
    output << "Eigen Value\n";
    fprintvec(output, n, lw);
    output.close();
    /*メモリの開放*/
    delete[] A;
    delete[] eigen_value;
    delete[] lw;
}