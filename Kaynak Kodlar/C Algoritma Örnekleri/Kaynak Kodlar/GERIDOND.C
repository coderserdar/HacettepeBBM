main()
{
int index;
int matrix[20];

   for (index = 0;index < 20;index++)              /* veriyi uretelim */
      matrix[index] = index + 1;

   for (index = 0;index < 5;index++)         /* orjinal veriyi, ekrana. */
      printf("Baslangic   matrix[%d] = %d\n",index,matrix[index]);

   yapbirsey(matrix);              /* fonksiyona gidip, deger degistirme */

   for (index = 0;index < 5;index++)       /* degismis matrix i yazalim  */
      printf("Geri donen  matrix[%d] = %d\n",index,matrix[index]);
} 

yapbirsey(list)                 /* Veri donusunu gosterir */
int list[];
{
int i;

   for (i = 0;i < 5;i++)                   /* print original matrix */ 
      printf("Onceki  matrix[%d] = %d\n",i,list[i]);

   for (i = 0;i < 20;i++)                   /* add 10 to all values */
      list[i] += 10;

   for (i = 0;i < 5;i++)                   /* print modified matrix */
      printf("Sonraki matrix[%d] = %d\n",i,list[i]);
}
