#include "all.h"

using namespace std;

void make_mat(int n, double *A)
{
    cout << "start" << endl;
    double mtmp;
    srand(time(NULL));
    for (int row_num = 0; row_num < n; ++row_num)
    {
        cout << row_num << endl;
        for (int col_num = row_num; col_num < n; ++col_num)
        {
            mtmp = (double)rand() / RAND_MAX;
            A[col_num + n * row_num] = mtmp;
            if (col_num != row_num)
            {
                A[row_num + n * col_num] = mtmp;
            }
        }
    }
    cout << "finish make mat" << endl;
}