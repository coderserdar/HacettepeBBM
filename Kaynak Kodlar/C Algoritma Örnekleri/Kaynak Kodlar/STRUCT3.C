main()
{
struct {
   char bas_harf;
   int yas;
   int not;
   } cocuklar[12],*point;

int index;

   for (index = 0;index < 12;index++) {
      point = cocuklar + index;
      point->bas_harf = 'A' + index;
      point->yas = 16;
      point->not = 84;
   }

   cocuklar[3].yas = cocuklar[5].yas = 17;
   cocuklar[2].not = cocuklar[6].not = 92;
   cocuklar[4].not = 57;

   for (index = 0;index < 12;index++) {
      point = cocuklar + index;
      printf("%c is %d years old and got a not of %d\n",
             (*point).bas_harf, cocuklar[index].yas,
             point->not);
   }
}
