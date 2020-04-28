#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(nullptr));
    for (int i = 0; i < rand() % 50; i++)
    {
        cout << '\t' << rand() % 24;
    }
    cout << endl;
}