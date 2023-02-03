#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

void selsort(int *numbers, int count);

int main(void)
{
    int *score = NULL;
    float median;
    int no_students, i;

    cout << "Öðrenci sayýsý: ";
    cin >> no_students;
    score = new int[no_students];

    for (i = 0; i < no_students; i++) {
        cout << i + 1 << ". öðrencinin notu: ";
        cin >> score[i];
    }

    selsort(score, no_students);

    median = (no_students % 2 == 1) ?  score[no_students/2] :
                 (score[no_students/2] + score[no_students/2-1]) / 2.0;
    cout << "Orta deðer: " << median << endl;

    delete score;
    return EXIT_SUCCESS;
}

void selsort(int *numbers, int count)
{
    int round, max, i;
    int tmp;

    for (round = 0; round < count - 1; round++) {
        max = 0;
        for (i = 1; i < count - round; i++) {
            if (numbers[max] < numbers[i])
                max = i;
        }
        tmp = numbers[max];
        numbers[max] = numbers[count - 1 - round];
        numbers[count - 1 - round] = tmp;
    }
}
