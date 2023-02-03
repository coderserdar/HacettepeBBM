#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int next_prime(int prime);

int main(void)
{
    int number, factor = 2;

    cout << "Sayýyý yazýnýz: ";
    cin >> number;
    while (number > 1) {
        while (number % factor == 0) {
            cout << factor << " ";
            number = number / factor;
        }
        factor = next_prime(factor);
    }
    cout << endl;
    return EXIT_SUCCESS;
}

bool is_prime(int cand)
{
    int count;

    if (cand == 2)
        return true;
    if (cand % 2 == 0)
        return false;
    for (count = 3; count * count <= cand; count += 2) {
        if (cand % count == 0)
            return false;
    }
    return true;
}

int next_prime(int prime)
{
    int cand = (prime == 2) ? 3 : prime + 2;

    while (!is_prime(cand))
        cand += 2;
    return cand;
}
