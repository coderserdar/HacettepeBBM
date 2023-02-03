#include <iostream.h>           // cout,cin
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int combin(int a, int b);

int main(void)
{
    int n, r;

    cout << "n ve r de?erlerini yaz?n?z: ";
    cin >> n >> r;
    cout << combin(n, r) << endl;
    return EXIT_SUCCESS;
}

int combin(int a, int b)
{
    int f1 = 1, f2, f3;
    int first = b, second = a - b;
    int i;

    if (b > a - b) {
        first = a - b;
        second = b;
    }

    for (i = 2; i <= first; i++)
        f1 = f1 * i;
    f2 = f1;
    for (i = first + 1; i <= second; i++)
        f2 = f2 * i;
    f3 = f2;
    for (i = second + 1; i <= a; i++)
        f3 = f3 * i;
    return f1 / (f2 * f3);
}
