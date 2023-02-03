 int toplam;             /* Global degisken tanimlaniyor */

main()
{
int index;

   baslik();  /* Baslik isimli fonksiyonu cagirir */

   for (index = 1;index <= 7;index++)
     kare(index);    /* Bu, kare fonksiyonunu cagirir.  */

   bitis();   /* Bu da, bitis isimli fonksiyonu cagirir */
}


baslik()     /***** baslik fonksiyonu basliyor *****/ 
{
   toplam = 0;          /* "Toplam" isimli degiskene 0 
                           degeri atanir.. */

   printf("Bu, kare programinin basligidir\n\n");
}

kare(rakam)   /*** Bu, kare fonksiyonunun baslangicidir ***/
int rakam;
{
int karesi;             /* Yerel degisken tanimlaniyor */

   karesi = rakam * rakam;  /* Karesini olusturuyor. */
   toplam += karesi;        /* toplama ekleniyor */
   printf("%d nin karesi %d dir.\n",rakam,karesi);
}

bitis()       /***** Bitis fonksiyonu tanimlaniyor.  *****/
{
   printf("\nKarelerin toplami: %d dir..\n",toplam);
}


      (Bu programin ciktisi, soyle gorunur:)

      Bu, kare programinin basligidir

      1 nin karesi 1 dir.
      2 nin karesi 4 dir.
      3 nin karesi 9 dir.
      4 nin karesi 16 dir.
      5 nin karesi 25 dir.
      6 nin karesi 36 dir.
      7 nin karesi 49 dir.

      Karelerin toplami: 140 dir..
