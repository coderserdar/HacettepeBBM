main()                      /* Pointer kullanimi ornegi */
{
int index,*pt1,*pt2;

   index = 39;                      /* herhangi bir deger  */
   pt1 = &index;                   /* 'index' in adresi    */
   pt2 = pt1;

   printf("Deger simdi %d %d %d dir.\n",index,*pt1,*pt2);

   *pt1 = 13;           /* 'index' in degerine degisiklik yapalim */

   printf("Degistikten sonra ise %d %d %d\n",index,*pt1,*pt2);
}
