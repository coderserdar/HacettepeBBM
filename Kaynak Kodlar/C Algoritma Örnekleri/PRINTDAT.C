#include "stdio.h"

main()
{
FILE *guzel,*printer;
int c;

   guzel = fopen("onsatir.txt","r"); /* kutugu acalim        */
   printer = fopen("PRN","w");        /* printeri acalim     */

   do {
      c = getc(guzel);    /* kutukten bir karakter okuyoruz  */
      if (c != EOF) {
	 putchar(c);      /* ekranda goruntuleyelim          */
	 putc(c,printer); /* ve yaziciya yollayalim          */
      }
   } while (c != EOF);    /* ta ki (End Of File) kutuk bitene kadar */

   fclose(guzel);
   fclose(printer);
}
