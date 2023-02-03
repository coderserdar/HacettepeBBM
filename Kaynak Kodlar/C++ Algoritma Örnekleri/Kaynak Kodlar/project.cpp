#include <iostream>             // std::xxx
#include <stdlib.h>             // EXIT_SUCCESS
#include "ops.h"                // gcd,lcm,...

int main(void)
{
    int num1 = 0, num2 = 0;
    factor_t factors[MAXFACTOR];
    int n, i;
    int choice;

    while (true) {
        std::cout << "Say� 1: " << num1 << std::endl;
        std::cout << "Say� 2: " << num2 << std::endl << std::endl;
        std::cout << "1. Say� 1'i de�i�tir" << std::endl;
        std::cout << "2. Say� 2'yi de�i�tir" << std::endl;
        std::cout << "3. Say� 1'in �arpanlar�n� g�ster" << std::endl;
        std::cout << "4. En b�y�k ortak b�len bul" << std::endl;
        std::cout << "5. En k���k ortak kat bul" << std::endl;
        std::cout << "6. ��k" << std::endl << std::endl;
        std::cout << "Se�iminiz: ";
        std::cin >> choice;
        if (choice == 6)
            exit(EXIT_SUCCESS);
        switch (choice) {
            case 1:
            case 2:
                std::cout << "Say�y� yaz�n�z: ";
                if (choice == 1)
                    std::cin >> num1;
                else
                    std::cin >> num2;
                break;
            case 3:
                factorize(num1, factors, n);
                for (i = 0; i < n; i++)
                    std::cout << factors[i].base << "^" << factors[i].power << " ";
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "En b�y�k ortak b�len: " << gcd(num1, num2) << std::endl;
                break;
            case 5:
                std::cout << "En k���k ortak kat: " << lcm(num1, num2) << std::endl;
                break;
        }
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}
