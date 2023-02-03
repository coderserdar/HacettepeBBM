#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

#define MAXSIZE 30

int main(void)
{
    int left[MAXSIZE][MAXSIZE], right[MAXSIZE][MAXSIZE];
    int product[MAXSIZE][MAXSIZE] = { 0 };
    int rl, cl, cr;
    int &rr = cl;
    int i, j, k;

    cout << "Sol matrisin sat�r say�s�: "; cin >> rl;
    cout << "Sol matrisin s�tun say�s�: "; cin >> cl;
    cout << "Sa� matrisin s�tun say�s�: "; cin >> cr;

    cout << "Sol matris: " << endl;
    for (i = 0; i < rl; i++) {
        for (j = 0; j < cl; j++) {
            cout << "  [" << i + 1 << "," << j + 1<< "]: ";
            cin >> left[i][j];
        }
    }

    cout << "Sa� matris: " << endl;
    for (j = 0; j < rr; j++) {
        for (k = 0; k < cr; k++) {
            cout << "  [" << j + 1 << "," << k + 1 << "]: ";
            cin >> right[j][k];
        }
    }

    for (i = 0; i < rl; i++) {
        for (j = 0; j < cr; j++) {
            for (k = 0; k < cl; k++)
                product[i][j] = product[i][j] + left[i][k] * right[k][j];
        }
    }

    cout << "�arp�m sonucu:" << endl;
    for (i = 0; i < rl; i++) {
        for (k = 0; k < cr; k++)
            cout << "\t" << product[i][k];
        cout << endl;
    }

    return EXIT_SUCCESS;
}
