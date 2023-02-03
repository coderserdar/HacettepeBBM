main()	/* Santigrad'dan Fahrenheite cevrim tablosu */
{
	int count; /* for degiskeni             */
	int fahr;	 /* fahrenheit degerini tutar */
	int cen;	 /* Santigrat degerini tutar  */
	
	printf("Santigrad -> Fahrenheit karsilik tablosu\n\n");
	
	for (count=-2;count<=12;count=count+1)
	{
		cen = 10 * count;
		fahr = 32 + (cen * 9) / 5;
		printf(" C = %4d  F = %4d  ",cen,fahr);
		if (cen == 0)
			printf(" Suyun donma noktasi");
		if (cen == 100)
			printf(" Suyun kaynama noktasi");
		printf("\n");
	}
}
