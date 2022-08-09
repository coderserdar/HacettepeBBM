#include "stdio.h"

main()
{
FILE *fp1;
char birkelime[100],kutukismi[25];
char *c;

   printf("Kutuk ismini girin -> ");
   scanf("%s",kutukismi);         /* istenilen kutuk ismini alalim */

   fp1 = fopen(kutukismi,"r");

   do {
      c = fgets(birkelime,100,fp1); /* kutukten bir satir okuyalim */
      if (c != NULL)
         printf("%s",birkelime);    /* ekrana yazalim       */
   } while (c != NULL);          /* ta ki NULL olana kadar  */

   fclose(fp1);
}
