#include <stdio.h>

main()
{
FILE *tuhaf;
int c;

   tuhaf = fopen("ONSATIR.TXT","r");

   if (tuhaf == NULL) printf("Boyle bir kutuk yok\n");
   else {
      do {
         c = getc(tuhaf);    /* Bir karakter oku  */
         putchar(c);         /* ekranda goster    */
      } while (c != EOF);    /* Kutuk sonuna (END OF FILE) a kadar devam */
   }
   fclose(tuhaf);
}
