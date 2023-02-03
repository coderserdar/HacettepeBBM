#include <iostream>             // std::xxx
#include <stdlib.h>             // EXIT_SUCCESS

int gcd(int a, int b);

int main(void)
{
    int num1, num2;

    std::cout << "Say�lar� yaz�n�z: ";
    std::cin >> num1 >> num2;
    std::cout << "En b�y�k ortak b�len: " << gcd(num1, num2) << std::endl;
    return EXIT_SUCCESS;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return (gcd(b, a % b));
}
