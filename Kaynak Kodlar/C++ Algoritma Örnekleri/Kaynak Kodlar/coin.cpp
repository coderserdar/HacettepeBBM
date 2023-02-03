#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS,srand,rand,RAND_MAX
#include <time.h>               // time

using namespace std;

int main(void)
{
    int count, i;
    float number;
    int heads = 0, tails = 0;

    cout << "Ka� kere at�lacak? ";
    cin >> count;
    srand(time(NULL));
    for (i = 1; i <= count; i++) {
        number = (float) rand() / RAND_MAX;
        if (number < 0.5) {
            cout << "Tura" << endl;
            heads++;
        } else {
            cout << "Yaz�" << endl;
            tails++;
        }
    }
    cout << "  Tura say�s�: " << heads
         << ", Y�zdesi: %" << 100.0 * heads / count << endl;
    cout << "  Yaz� say�s�: " << tails
         << ", Y�zdesi: %" << 100.0 * tails / count << endl;
    return EXIT_SUCCESS;
}
