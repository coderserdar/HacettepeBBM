int say;        /* Bu bir global degiskendir.  */

main()
{
register int index;          /* Bu degisken sadece "main" 
                                icinde kullanilabilir */
   baslik_1();
   baslik_2();
   baslik_3();
                      /* bu programin ana "for" dongusu  */
   for (index = 8;index > 0;index--)
   {
      int birsey;     /* Bu degisken sadece bu kume 
                         isaretleri arasinda tanimli */
      for (birsey = 0;birsey <= 6;birsey++)
         printf("%d ",birsey);

      printf(" index simdi: %d oldu.\n",index);
    }
}

int sayac;      /* Bu degisken bu noktadan
                   sonra kullanilabilir. */

baslik_1()
{
int index;   /* Bu degisken sadece baslik_1 icinde tanimli */

   index = 23;
   printf("Baslik_1 deki degeri %d\n",index);
}


baslik_2()
{
int say; /* Bu degisken sadece baslik_2 icinde gecerli */
         /* ayni isimli global degiskenin yerini alir.. */

   say = 53;
   printf("Baslik_2 deki degeri %d\n",say);
   sayac = 77;
}


baslik_3()
{
   printf("Baslik_3 deki degeri ise %d\n",sayac);
}

