#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int main(void)
{
    float x, error, term, result = 1.0;
    int i = 1;

    cout << "x: ";
    cin >> x;
    cout << "Hata: ";
    cin >> error;

    term = 1;
    while (term > error) {
        term = term * x / i;
        result = result + term;
        i++;
    }
    cout << "Hata: " << result << endl;

    return EXIT_SUCCESS;
}
