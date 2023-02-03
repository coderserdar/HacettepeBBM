#include <stdio.h>    /* input/output icin standard header */

main()
{
char c;

   printf("Herhangi bir tusa basin.  X = Programi durdurur. \n");

   do {
      c = getchar();    /* klavyeden bir tus okuyalim         */
      putchar(c);       /* ekranda gosterelim.                */
   } while (c != 'X');  /* ta ki okunan bir X oluncaya dek... */

   printf("\nProgramin sonu.\n");
}
