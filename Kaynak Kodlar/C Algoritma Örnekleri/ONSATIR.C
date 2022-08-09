#include <stdio.h>
main()
{
FILE *fp;
char ivir[25];
int index;

   fp = fopen("ONSATIR.TXT","w");   /* yazmak icin acalim */
   strcpy(ivir,"Bu bir ornek satirdir.");

   for (index = 1;index <= 10;index++)
      fprintf(fp,"%s  Satir no: %d\n",ivir,index);

   fclose(fp);    /* Kutugu kapayalim */
}
