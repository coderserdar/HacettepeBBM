#include <stdio.h>

main()
{
int deger;

   printf("0 ila 32767 arasinda bir rakkam yazin, durmak icin 100 girin.\n");

   do {
      scanf("%d",&deger);   /* bir tamsayi oku */
      printf("Okunan deger %d idi. \n",deger);
   } while (deger != 100);

   printf("Programin sonu\n");
}

