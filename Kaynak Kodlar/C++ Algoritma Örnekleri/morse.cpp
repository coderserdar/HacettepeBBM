#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <stdio.h>              // gets
#include <string.h>             // strcat

using namespace std;

#define MAXLENGTH 80

char *encode(const char *s);

int main(void)
{
    char word[MAXLENGTH];
    char *morse = NULL;

    cout << "Sözcüðü yazýnýz: ";
    cin >> word;
    morse = encode(word);
    cout << "Morse karþýlýðý: " << morse << endl;
    delete morse;
    return EXIT_SUCCESS;
}

char *encode(const char *s)
{
    static char encoding[][5] =
        { ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",
          "....", "..",   ".---", "-.-",  ".-..", "--",   "-.",
          "---",  ".--.", "--.-", ".-.",  "...",  "-",    "..-",
          "...-", ".--",  "-..-", "-.--", "--.." };
    char *morse = new char[MAXLENGTH];
    int i;

    morse[0] = '\0';
    for (i = 0; s[i] != '\0'; i++) {
        strcat(morse, encoding[s[i] - 'a']);
        strcat(morse, " ");
    }
    return morse;
}
