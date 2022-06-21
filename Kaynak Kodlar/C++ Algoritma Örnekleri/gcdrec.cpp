#include <iostream>             // std::xxx
#include <stdlib.h>             // EXIT_SUCCESS

int gcd(int a, int b);

int main(void)
{
    int num1, num2;

    std::cout << "Sayýlarý yazýnýz: ";
    std::cin >> num1 >> num2;
    std::cout << "En büyük ortak bölen: " << gcd(num1, num2) << std::endl;
    return EXIT_SUCCESS;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return (gcd(b, a % b));
}
