#include <iostream.h>           // cout,cin
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int combin(int a, int b);
int fact(int x);

int main(void)
{
    int n, r;

    cout << "n ve r deðerlerini yazýnýz: ";
    cin >> n >> r;
    cout << combin(n, r) << endl;
    return EXIT_SUCCESS;
}

int combin(int a, int b)
{
    int f1, f2, f3;

    f1 = fact(a);
    f2 = fact(b);
    f3 = fact(a - b);
    return f1 / (f2 * f3);
}

int fact(int x)
{
    int fx = 1;
    int i;

    for (i = 2; i <= x; i++)
        fx = fx * i;
    return fx;
}
