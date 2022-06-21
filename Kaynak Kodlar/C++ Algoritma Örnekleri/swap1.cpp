#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

void swap(int x, int y)
{
    int tmp;

    tmp = x;
    x = y;
    y = tmp;
}

int main(void)
{
    int m = 32, n = 154;

    cout << m << " " << n << endl;
    swap(m, n);
    cout << m << " " << n << endl;
    return EXIT_SUCCESS;
}
