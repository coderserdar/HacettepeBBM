#include "stdio.h"

main()
{
FILE *fp1;
char birkelime[100];
int c;

   fp1 = fopen("ONSATIR.TXT","r");

   do {
      c = fscanf(fp1,"%s",birkelime); /* kutukten bir kelime okuyalim */
      printf("%s\n",birkelime);       /* ekrana yazalim               */
   } while (c != EOF);              /* ta ki EOF olana kadar          */

   fclose(fp1);
}
