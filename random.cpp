#include <iostream>
#include <random>
using namespace std;

int main()
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_real_distribution<> rand01(0, 1);
    cout << "1st" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << rand01(mt) << endl;
    }
    cout << "2nd" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << rand01(mt) << endl;
    }
}