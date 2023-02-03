#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

#define MAXEQUATIONS 5

int main(void)
{
    float a[MAXEQUATIONS][MAXEQUATIONS], b[MAXEQUATIONS];
    float x[MAXEQUATIONS];
    float pivot, f;
    int n;
    int i, j, k;

    cout << "Denklem sayýsý: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "Denklem " << i + 1 << ": ";
        for (j = 0; j < n; j++) {
            cin >> a[i][j];
        }
        cin >> b[i];
    }

    for (j = 0; j < n - 1; j++) {
        pivot = a[j][j];
        for (i = j + 1; i < n; i++) {
            f = a[i][j] / pivot;
            for (k = j + 1; k < n; k++)
                a[i][k] = a[i][k] - f * a[j][k];
            b[i] = b[i] - f * b[j];
        }
    }

    x[n-1] = b[n-1] / a[n-1][n-1];
    for (i = n - 2; i >= 0; i--) {
        f = b[i];
        for (k = i + 1; k < n; k++)
            f = f - a[i][k] * x[k];
        x[i] = f / a[i][i];
    }

    for (i = 0; i < n; i++)
        cout << "x" << i + 1 << ": " << x[i] << endl;

    return EXIT_SUCCESS;
}
