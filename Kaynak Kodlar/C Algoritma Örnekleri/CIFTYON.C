main()
{
int cevizler,elmalar;

   cevizler = 100;
   elmalar = 101;
   printf("Baslangic degerleri %d %d\n",cevizler,elmalar);

			   /* "degistir" i cagirinca,         */
   degistir(cevizler,&elmalar);  /* cevizlerin DEGERI ve,     */
			   /* elmalarin adresini geciriyoruz  */

   printf("Bitis degerleri ise, %d %d dir..\n",cevizler,elmalar);
}

degistir(kuru_yemis,meyvalar)       /* kuru_yemis tamsayidir   */
int kuru_yemis,*meyvalar;           /* meyvalar bir tamsayi pointer'idir */
{
   printf("Degerler %d %d\n",kuru_yemis,*meyvalar);
   kuru_yemis = 135;
   *meyvalar = 172;
   printf("Sonraki degerler %d %d\n",kuru_yemis,*meyvalar);
}
