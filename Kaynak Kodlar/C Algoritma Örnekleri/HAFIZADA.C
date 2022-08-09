main()
{
int rakam[5], sonuc[5], index;
char satir[80];

   rakam[0] = 5;
   rakam[1] = 10;
   rakam[2] = 15;
   rakam[3] = 20;
   rakam[4] = 25;

   sprintf(satir,"%d %d      %d %d %d\n",rakam[0],rakam[1],
	   rakam[2],rakam[3],rakam[4]);

   printf("%s",satir);

   sscanf(satir,"%d %d %d %d      %d",&sonuc[4],&sonuc[3],
	   (sonuc+2),(sonuc+1),sonuc);


   for (index = 0;index < 5;index++)
      printf("Sonuc %d dir. \n",sonuc[index]);

}
