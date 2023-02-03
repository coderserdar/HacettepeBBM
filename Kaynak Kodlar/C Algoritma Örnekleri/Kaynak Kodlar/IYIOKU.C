#include "stdio.h"

main()
{
FILE *fp1;
char birkelime[100];
int c;

   fp1 = fopen("onsatir.txt","r");

   do {
      c = fscanf(fp1,"%s",birkelime); /* kutukten bir kelime oku... */
      if (c != EOF)
         printf("%s\n",birkelime);    /* ekrana yaz...            */
   } while (c != EOF);              /* ta ki EOF olana dek..      */

   fclose(fp1);                      /* kutugu kapa       */
}
