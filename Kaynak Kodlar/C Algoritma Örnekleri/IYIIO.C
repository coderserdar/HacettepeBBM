#include "stdio.h"
#define CR 13       /* CR sembolunu 13 olarak tanimlar */
#define LF 10       /* LF sembolunu 10 olarak tanimlar */

main()
{
char c;

   printf("Tuslara basin. Durmak icin X e basin.\n");

   do {
      c = getch();                    /* Bir karakter oku        */
      putchar(c);                     /* basilan tusu ekrana yaz */
      if (c == CR) putchar(LF);       /* sayet basilan RETURN tusu ise,
					 bir SATIR ATLAMA karakteri yolla */
   } while (c != 'X');

   printf("\nProgramin sonu.\n");
}

