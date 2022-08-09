char isim1[] = "Birinci Program basligi";

main()
{
int index;
int ivir[12];
float tuhaf[12];
static char isim2[] = "Ikinci Program Basligi";

   for (index = 0;index < 12;index++) {
      ivir[index] = index + 10;
      tuhaf[index] = 12.0 * (index + 7);
   }

   printf("%s\n",isim1);
   printf("%s\n\n",isim2);
   for (index = 0;index < 12;index++)
      printf("%5d %5d %10.3f\n",index,ivir[index],tuhaf[index]);
}
