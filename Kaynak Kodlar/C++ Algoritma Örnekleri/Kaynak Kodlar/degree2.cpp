#include <iostream>             // cout,cin,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // sqrt

using namespace std;

int main(void)
{
    float a, b, c;
    float disc;
    float x1, x2;

    cout << "a, b ve c katsay�lar�n� yaz�n�z: ";
    cin >> a >> b >> c;
    disc = b * b - 4 * a * c;
    if (disc < 0)
      cout << "Ger�el k�k yok." << endl;
    else {
      if (disc == 0) {
        x1 = -b / (2 * a);
        cout << x1 << " noktas�nda �ak��an iki k�k var. " << endl;
      } else {
        x1 = (-b + sqrt(disc)) / (2 * a);
        x2 = (-b - sqrt(disc)) / (2 * a);
        cout << x1 << " ve " << x2
             << " noktalar�nda iki ger�el k�k var." << endl;
      }
    }
    return EXIT_SUCCESS;
}
