/* �lk C program�m.                                             *
 *                                                              *
 * Yar��ap� verilen bir dairenin �evresini ve alan�n� hesaplar. */

#include <iostream>             // cout,cin,endl i�in
#include <stdlib.h>             // EXIT_SUCCESS i�in

using namespace std;

#define PI 3.14

int main(void)
{
    float radius; 
    float circum, area;

    cout << "Yar��ap� yaz�n�z: ";
    cin >> radius;
    circum = 2 * PI * radius;
    area = PI * radius * radius;
    cout << "�evresi: " << circum << endl;
    cout << "Alan�: " << area << endl;
    return EXIT_SUCCESS;
}
