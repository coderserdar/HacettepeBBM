main()
{
char isim[7];       /* Bir karakterler dizisi tanimlayalim */

   isim[0] = 'T';
   isim[1] = 'u';
   isim[2] = 'r';
   isim[3] = 'g';
   isim[4] = 'u';
   isim[5] = 't';
   isim[6] = 0;     /* Bos karakter - katarin sonu  */

   printf("Isim %s dur. \n",isim);
   printf("Icinden bir karakter: %c\n",isim[2]);
   printf("Ismin bir parcasi: %s \n",&isim[3]);
}
