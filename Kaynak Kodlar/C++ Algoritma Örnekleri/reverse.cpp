#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <stdio.h>              // gets
#include <string.h>             // strlen

using namespace std;

#define MAXLENGTH 80

int main(void)
{
    char sentence[MAXLENGTH];
    int len, i;
    char tmp;

    cout << "Tümce: ";
    gets(sentence);
    len = strlen(sentence);
    for (i = 0; i < len / 2; i++) {
        tmp = sentence[i];
        sentence[i] = sentence[len - 1 - i];
        sentence[len - 1 - i] = tmp;
    }
    cout << "Tersi: " << sentence << endl;
    return EXIT_SUCCESS;
}
