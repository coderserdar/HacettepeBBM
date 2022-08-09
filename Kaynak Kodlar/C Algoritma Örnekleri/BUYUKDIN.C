main()
{
struct hayvan {
   char ismi[25];
   char cinsi[25];
   int yasi;
} *evcil[12], *point;       /* bu, 13 tane pointer ve
                              0 degisken tanimliyor */
	
int index;

               /* ilk once, dinamik sahayi tanimlayip, 
                  ivir zivirla dolduralim.          */
	
   for (index = 0;index < 12;index++) {
     evcil[index] = (struct hayvan *)malloc(sizeof(struct hayvan));
     strcpy(evcil[index]->ismi,"General");
     strcpy(evcil[index]->cinsi,"Karisik cins");
     evcil[index]->yasi = 4;
   }

   evcil[4]->yasi = 12;        /* Bu atamalar, bazi sahalara  */
   evcil[5]->yasi = 15;        /*      nasil luzumsuz bilgi   */
   evcil[6]->yasi = 10;        /*  yazilabilecegini gosterir. */

       /* yukarida tanimladiklarimizi yazalim.   */

   for (index = 0;index <12;index++) {
      point = evcil[index];
      printf("%s, bir %s, ve %d yasindadir.\n", point->ismi,
              point->cinsi, point->yasi);
   }

   /* Iyi programlama teknigi, dinamik yaratilmis sahanin, */
   /* sisteme iade edilmesini soyler..                     */

   for (index = 0;index < 12;index++)
      free(evcil[index]);
}
