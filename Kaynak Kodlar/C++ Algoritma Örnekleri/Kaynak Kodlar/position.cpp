#include <iostream>             // cout,cin,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

typedef struct point_s {
    float x, y;
} point_t;

typedef struct circle_s {
    point_t center;
    float radius;
} circle_t;

int main(void)
{
    circle_t circle1;
    point_t point1;
    float p, deltaX, deltaY;

    cout << "Daire merkezinin koordinatlarýný yazýn (x y): ";
    cin >> circle1.center.x >> circle1.center.y;
    cout << "Dairenin yarýçapýný yazýn: ";
    cin >> circle1.radius;
    cout << "Noktanýn koordinatlarýný yazýn (x y): ";
    cin >> point1.x >> point1.y;
    deltaX = point1.x - circle1.center.x;
    deltaY = point1.y - circle1.center.y;
    p = deltaX * deltaX + deltaY * deltaY;
    if (p < circle1.radius * circle1.radius)
        cout << "Nokta dairenin içinde." << endl;
    else {
        if (p > circle1.radius * circle1.radius)
            cout << "Nokta dairenin dýþýnda." << endl;
        else
            cout << "Nokta dairenen üzerinde." << endl;
    }
    return EXIT_SUCCESS;
}
