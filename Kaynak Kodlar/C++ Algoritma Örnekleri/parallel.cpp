#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

struct rational_s {
    int nom;
    int denom;
};
typedef struct rational_s rational_t;

int main(void)
{
    int res_value;
    rational_t equiv = { 0, 1 };
    int a, b, r;
    int i = 0;

    while (true) {
        i++;
        cout << "R" << i << " (bittiyse 0): ";
        cin >> res_value;
        if (res_value == 0)
            break;
        equiv.nom = equiv.nom * res_value + equiv.denom;
        equiv.denom = equiv.denom * res_value;

        // kesiri basitleþtir
        a = equiv.nom;
        b = equiv.denom;
        while (b > 0) {
            r = a % b;
            a = b;
            b = r;
        }
        equiv.nom = equiv.nom / a;
        equiv.denom = equiv.denom / a;
    }
    if (equiv.nom != 0)
        cout << "Eþdeðer direnç: " << equiv.denom
             << " / " << equiv.nom
             << " = " << (float) equiv.denom / equiv.nom << endl;
    else
        cout << "Hatalý iþlem." << endl;
    return EXIT_SUCCESS;
}
