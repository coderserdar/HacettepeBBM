main()
{
struct insan {
   char isim[25];
   int yas;
   char durum;        /* E = Evli , B = Bekar */
} ;

struct tumveri {
   int not;
   struct insan ozellikler;
   char yemek[25];
} ogrenci[53];

struct tumveri hoca,asistan;

hoca.not = 94;
hoca.ozellikler.yas = 34;
hoca.ozellikler.durum = 'E';
strcpy(hoca.ozellikler.isim,"Mary Smith");
strcpy(hoca.yemek,"Salamli sandvic");

asistan.ozellikler.yas = 87;
asistan.ozellikler.durum = 'E';
strcpy(asistan.ozellikler.isim,"Old Lady Brown");
asistan.not = 73;
strcpy(asistan.yemek,"Yogurt ve ekmek");

ogrenci[1].ozellikler.yas = 15;
ogrenci[1].ozellikler.durum = 'B';
strcpy(ogrenci[1].ozellikler.isim,"Billy Boston");
strcpy(ogrenci[1].yemek,"Findik ezmesi");
ogrenci[1].not = 77;

ogrenci[7].ozellikler.yas = 14;
ogrenci[12].not = 87;

}
