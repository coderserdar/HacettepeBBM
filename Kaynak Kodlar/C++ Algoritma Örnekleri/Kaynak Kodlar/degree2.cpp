#include <iostream>             // cout,cin,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // sqrt

using namespace std;

int main(void)
{
    float a, b, c;
    float disc;
    float x1, x2;

    cout << "a, b ve c katsayýlarýný yazýnýz: ";
    cin >> a >> b >> c;
    disc = b * b - 4 * a * c;
    if (disc < 0)
      cout << "Gerçel kök yok." << endl;
    else {
      if (disc == 0) {
        x1 = -b / (2 * a);
        cout << x1 << " noktasýnda çakýþan iki kök var. " << endl;
      } else {
        x1 = (-b + sqrt(disc)) / (2 * a);
        x2 = (-b - sqrt(disc)) / (2 * a);
        cout << x1 << " ve " << x2
             << " noktalarýnda iki gerçel kök var." << endl;
      }
    }
    return EXIT_SUCCESS;
}
