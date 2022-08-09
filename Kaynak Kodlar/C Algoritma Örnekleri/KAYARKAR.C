float z;   /* Bu bir global degiskendir */

main()
{
int index;
float x,y,sqr(),glsqr();

   for (index = 0;index <= 7;index++){
      x = index;  /* int'i float yapalim  */
      y = sqr(x); /* x'in karesini alalim..   */
      printf("%d in karesi %10.4f dir.\n",index,y);
   }

   for (index = 0; index <= 7;index++) {
      z = index;
      y = glsqr();
      printf("%d in karesi %10.4f dir.\n",index,y);
   }
}

float sqr(deger)  /* float'in karesini al, float dondur. */
float deger;
{
float karesi;

   karesi = deger * deger;
   return(karesi);
}

float glsqr()    /* float'in karesini al, float dondur. */
{
   return(z*z);
}
