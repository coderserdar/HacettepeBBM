main()
{
struct {
   char bas_harf;
   int yas;
   int not;
   } cocuklar[12];

int indeks;

   for (indeks = 0;indeks < 12;indeks++) {
      cocuklar[indeks].bas_harf = 'A' + indeks;
      cocuklar[indeks].yas = 16;
      cocuklar[indeks].not = 84;
   }

   cocuklar[3].yas = cocuklar[5].yas = 17;
   cocuklar[2].not = cocuklar[6].not = 92;
   cocuklar[4].not = 57;

   for (indeks = 0;indeks < 12;indeks++)
      printf("%c is %d years old and got a not of %d\n",
             cocuklar[indeks].bas_harf, cocuklar[indeks].yas,
             cocuklar[indeks].not);
}
