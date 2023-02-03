main()  /* Ana program burada.  */
{
int x,y;

   for(x = 0;x <= 7;x++) {
      y = squ(x);  			/* x*x i hesaplayalim.. */
      printf("%d nin karesi %d dir...\n",x,y);
   }

   for (x = 0;x <= 7;++x) 
      printf("%d nin karesi %d dir...\n",x,squ(x));
}

squ(in)  /* Bir rakamin karesini bulan fonksiyon */
int in;
{
int kare;

   kare = in * in;
   return(kare);  	/* Yeni buldugumuz deger donduruluyor.. */
}
