#include <stdio.h>

main()
{
char c;

   printf("Herhangi bir tusa basin.  X = Programi durdurur. \n");

   do {
      c = getch();                     /* bir tus oku          */
      putchar(c);                  /* basilan tusu goster      */
   } while (c != 'X');             /* ta ki c == 'X' olana dek */

   printf("\nProgramin sonu.\n");
}
