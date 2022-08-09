#include <stdio.h>
#include <ctype.h>  /* Derleyiciniz bunu gerektirmeyebilir */

main()
{
FILE *fp;
char satir[80], kutukismi[24];
char *c;

   printf("Kutukismi -> ");
   scanf("%s",kutukismi);
   fp = fopen(kutukismi,"r");

   do {
      c = fgets(satir,80,fp);   /* bir satir oku */
      if (c != NULL) {
         veriyi_say(satir);
      }
   } while (c != NULL);

   fclose(fp);
}

satiri_say(satir)
char satir[];
{
int beyazlar, kars, rakamlar;
int index;

   beyazlar = kars = rakamlar = 0; 

   for (index = 0;satir[index] != 0;index++) {
      if (isalpha(satir[index]))   /* 1 eger satir[] alfabetik ise   */
          kars++;
      if (isdigit(satir[index]))   /* 1 eger satir[] rakam ise     */
          rakamlar++;
      if (isspace(satir[index]))   /* 1 eger satir[] bosluk ise tab, */
          beyazlar++;               /*           yada yeni satir ise */ 
   }   /* sayan dongunun sonu */

   printf("%3d%3d%3d %s",beyazlar,kars,rakamlar,satir);
}
