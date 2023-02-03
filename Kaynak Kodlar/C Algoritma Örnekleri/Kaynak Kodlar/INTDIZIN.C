main()
{
int degerler[12];
int index;

   for (index = 0;index < 12;index++)  
      degerler[index] = 2 * (index + 4);

   for (index = 0;index < 12;index++)
      printf("Index = %2d deki degeri %3d dir..\n",index,degerler[index]);

}
