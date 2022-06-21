#include <iostream>             // cout,cin.endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // exp

using namespace std;

#define PI 3.14

int main(void)
{
    float x, y;

    cout << "x: ";
    cin >> x;
    y = exp(-PI * x);
    cout << "y: " << y << endl;
    return EXIT_SUCCESS;
}
