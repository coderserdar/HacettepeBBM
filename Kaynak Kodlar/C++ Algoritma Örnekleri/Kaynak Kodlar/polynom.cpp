#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

#define MAXDEGREE 50

int main(void)
{
    float a[MAXDEGREE];
    float x, b;
    int n, i;
    char response = 'E';

    cout << "Polinomun derecesi: ";
    cin >> n;

    cout << "Katsayýlar: " << endl;
    for (i = n; i >= 0; i--) {
        cout << "a" << i << ": ";
        cin >> a[i];
    }

    while (true) {
        cout << "x: ";
        cin >> x;
        b = a[n];
        for (i = n - 1; i >= 0; i--)
            b = b * x + a[i];
        cout << "p(x): " << b << endl;
        cout << "Devam etmek istiyor musunuz (E/H)? ";
        cin >> response;
        if ((response == 'H') || (response == 'h'))
            break;
    }

    return EXIT_SUCCESS;
}
