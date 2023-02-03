main()
{
char isim1[12],isim2[12],karisik[25];
char baslik[20];

   strcpy(isim1,"Rosalinda");
   strcpy(isim2,"Zeke");
   strcpy(baslik,"Bu bir basliktir.");

   printf("     %s\n\n",baslik);
   printf("isim 1:  %s \n",isim1);
   printf("isim 2:  %s \n",isim2);

   if(strcmp(isim1,isim2)>0)  /* sayet isim1 > isim2 ise, 1 dondurur */
      strcpy(karisik,isim1);
   else
      strcpy(karisik,isim2);

   printf("Alfabetik olarak en buyuk isim %s dir.\n",karisik);

   strcpy(karisik,isim1);
   strcat(karisik,"  ");
   strcat(karisik,isim2);
   printf("Iki isim birden %s\n",karisik);
}
