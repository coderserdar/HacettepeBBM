#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

void quicksort(int arr[], int first, int last);

int main(void)
{
    int numbers[] = { 26, 33, 35, 29, 19, 12, 22 };
    int i;

    quicksort(numbers, 0, 6);
    for (i = 0; i < 7; i++)
        cout << numbers[i] << endl;
    return EXIT_SUCCESS;
}

void swap(int &x, int &y)
{
    int tmp;

    tmp = x; x = y; y = tmp;
}

int partition(int arr[], int first, int last)
{
    int pivotloc = first;
    int pivot = arr[first];
    int i;

    for (i = first + 1; i <= last; i++) {
        if (arr[i] < pivot) {
            pivotloc++;
            swap(arr[pivotloc], arr[i]);
        }
    }
    swap(arr[first], arr[pivotloc]);
    return pivotloc;
}

void quicksort(int arr[], int first, int last)
{
    int pivotloc;

    if (first < last) {
        pivotloc = partition(arr, first, last);
        quicksort(arr, first, pivotloc - 1);
        quicksort(arr, pivotloc + 1, last);
    }
}
