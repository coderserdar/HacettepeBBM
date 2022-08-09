#include <STDIO.H>
#include <ctype.h>   /* Not: Derleyiciniz bunu gerektirmeyebilir */

main()
{
FILE *fp;
char satir[80], kutukismi[24];
char *c;

   printf("Kutuk ismini girin -> ");
   scanf("%s",kutukismi);
   fp = fopen(kutukismi,"r");

   do {
      c = fgets(satir,80,fp);   /* bir satir oku */
      if (c != NULL) {
         karistir_butun_karakterleri(satir);
      }
   } while (c != NULL);

   fclose(fp);
}

karistir_butun_karakterleri(satir)

/* Bu fonksiyon butun buyuk harfleri kucuge, butun kucukleri 
de buyuge cevirir. Diger butun karakterleri etkilemez. */

char satir[];
{
int index;

   for (index = 0;satir[index] != 0;index++) {
      if (isupper(satir[index]))     /* buyuk harfse,1 doner */
         satir[index] = tolower(satir[index]);
      else {
         if (islower(satir[index]))  /* kucuk harfse,1 doner */
            satir[index] = toupper(satir[index]);
      }
   }
   printf("%s",satir);
}
