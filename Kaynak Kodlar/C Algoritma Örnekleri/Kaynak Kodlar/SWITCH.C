main()
{
	int kamyon;
	
	for (kamyon = 3;kamyon<13;kamyon = kamyon + 1)
	{
		switch (kamyon)
		{
			case 3:	printf("Degeri simdi uc.\n");
					break;
			case 4: printf("Degeri simdi dort.\n");
					break;
			case 5:
			case 6:
			case 7:
			case 8:	printf("Degeri simdi 5 le 8 arasinda.\n");
					break;
			case 11:printf("Degeri simdi onbir.\n");
					break;
			default:printf("Tanimsiz degerlerden biri.\n");
					break;
		}
	}
}
