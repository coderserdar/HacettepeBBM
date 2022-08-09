main()
{
union {
   int deger;     /* Union'un birinci parcasi   */
   struct {
      char ilk;   /* Bu iki deger ise, ikinci.. */
      char ikinci;
   } yarim;
} rakam;

long index;

   for (index = 12;index < 300000;index += 35231) {
      rakam.deger = index;
      printf("%8x %6x %6x\n",rakam.deger, rakam.yarim.ilk,
	      rakam.yarim.ikinci);
   }
}

