#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // pow

using namespace std;

int main(void)
{
    float x, error, term, result = 1.0;
    int i = 1, f;
    float fact;

    cout << "x: ";
    cin >> x;
    cout << "Hata: ";
    cin >> error;

    term = error + 1;
    while (term > error) {
        fact = 1.0;
        for (f = 2; f <= i; f++)
            fact = fact * f;
        term = pow(x, i) / fact;
        result = result + term;
        i++;
    }
    cout << "Sonuç: " << result << endl;

    return EXIT_SUCCESS;
}
