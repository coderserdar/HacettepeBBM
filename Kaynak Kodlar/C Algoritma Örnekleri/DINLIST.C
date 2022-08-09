main()
{
struct hayvan {
   char ismi[25];
   char cinsi[25];
   int yasi;
} *evcil1, *evcil2, *evcil3;

   evcil1 = (struct hayvan *)malloc(sizeof(struct hayvan));
   strcpy(evcil1->ismi,"General");
   strcpy(evcil1->cinsi,"Karisik Birsey");
   evcil1->yasi = 1;

   evcil2 = evcil1;   /* evcil2 simdi yukaridaki veri
                         yapisina karsilik geliyor */

   evcil1 = (struct hayvan *)malloc(sizeof(struct hayvan));
   strcpy(evcil1->ismi,"Bobi");
   strcpy(evcil1->cinsi,"Labrador");
   evcil1->yasi = 3;

   evcil3 = (struct hayvan *)malloc(sizeof(struct hayvan));
   strcpy(evcil3->ismi,"Kristal");
   strcpy(evcil3->cinsi,"Alman Coban");
   evcil3->yasi = 4;

       /* Yukardaki bilgiyi yazalim */

   printf("%s, bir %sdir ve %d yasindadir.\n", evcil1->ismi,
           evcil1->cinsi, evcil1->yasi);

   printf("%s, bir %sdir ve %d yasindadir.\n", evcil2->ismi,
           evcil2->cinsi, evcil2->yasi);

   printf("%s, bir %sdir ve %d yasindadir.\n", evcil3->ismi,
           evcil3->cinsi, evcil3->yasi);

   evcil1 = evcil3;   /* evcil1 simdi evcil3 un gosterdigi
                         yapiyi gosteriyor              */

   free(evcil3);    /* bir structure'u siliyor                 */
   free(evcil2);    /* bu da bir baska structure'u siliyor     */
/* free(evcil1);    bu yapilamaz - niye? anlatacagim!          */
}

