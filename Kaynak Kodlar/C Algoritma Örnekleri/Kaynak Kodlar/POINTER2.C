main()
{
char katar[40],*orada,bir,iki;
int *pt,list[100],index;

   strcpy(katar,"Bu bir karakter kataridir.");

   bir = katar[0];                 /* bir ve iki ayni degeri tasirlar */
   iki = *katar;
   printf("Ilk cikti %c %c\n",bir,iki);

   bir = katar[8];                /* bir ve iki ayni degeri tasirlar */
   iki = *(katar+8);
   printf("Ikinci cikti %c %c\n",bir,iki);

   orada = katar+10;        /* katar+10 ve katar[10] aynidir. */
   printf("Ucuncu cikti %c\n",katar[10]);
   printf("Dorduncu cikti %c\n",*orada);

   for (index = 0;index < 100;index++)
      list[index] = index + 100;
   pt = list + 27;
   printf("Besinci cikti %d\n",list[27]);
   printf("Altinci cikti %d\n",*pt);
}
