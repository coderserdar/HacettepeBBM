main()
{
int i,j;
int buyuk[8][8],dev[25][12];

   for (i = 0;i < 8;i++)
      for (j = 0;j < 8;j++)
         buyuk[i][j] = i * j;       /* Bu bir carpim tablosudur */

   for (i = 0;i < 25;i++)
      for (j = 0;j < 12;j++)
         dev[i][j] = i + j;     /* Bu da bir toplama tablosudur */

   buyuk[2][6] = dev[24][10]*22;
   buyuk[2][2] = 5;
   buyuk[buyuk[2][2]][buyuk[2][2]] = 177;  /* bu,  buyuk[5][5] = 177; demek */

   for (i = 0;i < 8;i++) {
      for (j = 0;j < 8;j++)
         printf("%5d ",buyuk[i][j]);
      printf("\n");               /* Her i nin degeri artinca, bir RETURN */
   }
}