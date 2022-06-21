#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

#define DISKS 3

void move(int n, int a, int b, int c);

int main(void)
{
    move(DISKS, 1, 3, 2);
    return EXIT_SUCCESS;
}

void move(int n, int a, int b, int c)
{
    if (n > 0) {
        move(n - 1, a, c, b);
        cout << "Bir diski " << a << " direðinden "
             << b << " direðine taþý." << endl;
        move(n - 1, c, b, a);
    }
}
