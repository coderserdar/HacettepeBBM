#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int cand = 2;

void next_prime(void);

int main(void)
{
    int number;

    cout << "Sayýyý yazýnýz: ";
    cin >> number;
    while (number > 1) {
        while (number % cand == 0) {
            cout << cand << " ";
            number = number / cand;
        }
        next_prime();
    }
    cout << endl;
    return EXIT_SUCCESS;
}

bool is_prime(void)
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

void next_prime(void)
{
    cand = (cand == 2) ? 3 : cand + 2;
    while (!is_prime())
        cand += 2;
}
