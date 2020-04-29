#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(nullptr));
    for (int i = 0; i < rand() % 100; i++)
    {
        cout << ' ' << rand() % 24;
    }  
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << i << '\r';
    }
    cout << endl;
}