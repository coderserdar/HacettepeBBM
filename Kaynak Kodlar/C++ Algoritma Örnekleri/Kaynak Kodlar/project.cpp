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
        std::cout << "Sayý 1: " << num1 << std::endl;
        std::cout << "Sayý 2: " << num2 << std::endl << std::endl;
        std::cout << "1. Sayý 1'i deðiþtir" << std::endl;
        std::cout << "2. Sayý 2'yi deðiþtir" << std::endl;
        std::cout << "3. Sayý 1'in çarpanlarýný göster" << std::endl;
        std::cout << "4. En büyük ortak bölen bul" << std::endl;
        std::cout << "5. En küçük ortak kat bul" << std::endl;
        std::cout << "6. Çýk" << std::endl << std::endl;
        std::cout << "Seçiminiz: ";
        std::cin >> choice;
        if (choice == 6)
            exit(EXIT_SUCCESS);
        switch (choice) {
            case 1:
            case 2:
                std::cout << "Sayýyý yazýnýz: ";
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
                std::cout << "En büyük ortak bölen: " << gcd(num1, num2) << std::endl;
                break;
            case 5:
                std::cout << "En küçük ortak kat: " << lcm(num1, num2) << std::endl;
                break;
        }
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}
