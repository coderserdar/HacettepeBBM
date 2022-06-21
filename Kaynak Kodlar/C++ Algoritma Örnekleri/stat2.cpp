#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // fabs,sqrt

using namespace std;

int main(void)
{
    int *score = NULL;
    int no_students = 0;
    float mean, variance, std_dev, abs_dev;
    float total = 0.0, sqr_total = 0.0, abs_total = 0.0;
    int i = 0;

    cout << "Kaç öðrenci var? ";
    cin >> no_students;
    score = new int[no_students];
    for (i = 0; i < no_students; i++) {
        cout << i + 1 << ". öðrencinin notu: ";
        cin >> score[i];
        total = total + score[i];
    }
    mean = total / no_students;
    for (i = 0; i < no_students; i++) {
        sqr_total = sqr_total + (score[i] - mean) * (score[i] - mean);
        abs_total = abs_total + fabs(score[i] - mean);
    }
    variance = sqr_total / (no_students - 1);
    std_dev = sqrt(variance);
    abs_dev = abs_total / no_students;
    cout << "Ortalama: " << mean << endl;
    cout << "Varyans: " << variance << endl;
    cout << "Standart sapma: " << std_dev << endl;
    cout << "Mutlak sapma: " << abs_dev << endl;
    delete score;
    return EXIT_SUCCESS;
}
