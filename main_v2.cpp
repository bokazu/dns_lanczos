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
    string matsize_file = "set_matrixsize.txt";
    string filename = "set_filename.txt";

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

    double *A = new double[n * n];
    double *eigen_value = new double[n];
    double *lw = new double[n];

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
    while (!set_file.eof())
    {
        getline(set_file, filename_tmp);
        if (file_line_count == 0)
        {
            SampleFile_name = filename_tmp;
            cout << "Sample file name :" << SampleFile_name << endl;
            file_line_count += 1;
        }
        else
        {
            OutputFile_name = filename_tmp;
            cout << "Output file name :" << OutputFile_name << endl;
        }
    }
}