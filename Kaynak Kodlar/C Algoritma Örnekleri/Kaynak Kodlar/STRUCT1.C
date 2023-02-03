main()
{

struct {
   char bas_harf;  /* Soyadin bas harfi   */
   int yas;        /* cocugun yasi        */
   int not;        /* okulda not ortalamasi (100 uzerinden) */
   } oglan,kiz;

   oglan.bas_harf = 'R';
   oglan.yas = 15;
   oglan.not = 75;

   kiz.yas = oglan.yas - 1;  /* o, oglandan bir yas kucuk */
   kiz.not = 82;
   kiz.bas_harf = 'H';

   printf("%d yasindaki %c'nin aldigi not, %d dir.\n",
           kiz.yas, kiz.bas_harf, kiz.not);

   printf("%d yasindaki %c'nin aldigi not, %d dir.\n",
           oglan.yas, oglan.bas_harf, oglan.not);
}
