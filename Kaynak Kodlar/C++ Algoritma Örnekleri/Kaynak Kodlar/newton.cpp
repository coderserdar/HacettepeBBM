#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // fabs

using namespace std;

#define MAXDEGREE 50

float newton_raphson(float x, const float a[], int n);

int main(void)
{
    float a[MAXDEGREE];
    int n, i;
    float xi, xj, error;

    cout << "Polinomun derecesi: "; cin >> n;
    for (i = n; i >= 0; i--) {
        cout << "a" << i << ": ";
        cin >> a[i];
    }

    cout << "Hata: "; cin >> error;
    cout << "x0: ";   cin >> xi;
    while (true) {
        xj = newton_raphson(xi, a, n);
        if (fabs(xj - xi) < error)
            break;
        xi = xj;
    }
    cout << "Kök: " << xj << endl;
    return EXIT_SUCCESS;
}

float newton_raphson(float x, const float a[], int n)
{
    float b[MAXDEGREE], c[MAXDEGREE];
    float xn;
    int i;

    b[n] = a[n];
    c[n] = b[n];
    for (i = n - 1; i > 0; i--) {
        b[i] = b[i+1] * x + a[i];
        c[i] = c[i+1] * x + b[i];
    }
    b[0] = b[1] * x + a[0];
    xn = x - b[0] / c[1];
    return xn;
}
