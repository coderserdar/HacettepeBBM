/* Ýlk C programým.                                             *
 *                                                              *
 * Yarýçapý verilen bir dairenin çevresini ve alanýný hesaplar. */

#include <iostream>             // cout,cin,endl için
#include <stdlib.h>             // EXIT_SUCCESS için

using namespace std;

#define PI 3.14

int main(void)
{
    float radius; 
    float circum, area;

    cout << "Yarýçapý yazýnýz: ";
    cin >> radius;
    circum = 2 * PI * radius;
    area = PI * radius * radius;
    cout << "Çevresi: " << circum << endl;
    cout << "Alaný: " << area << endl;
    return EXIT_SUCCESS;
}
