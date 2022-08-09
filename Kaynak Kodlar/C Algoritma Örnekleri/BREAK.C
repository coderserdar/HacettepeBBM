main()
{
	int xx;
	
	for (xx=5;xx<15; xx=xx+1)
	{
		if (xx==8)
			break;
		printf("Break dongusunun icinde, xx in degeri simdi %d\n",xx);
	}
	
	for (xx=5;xx<15;xx=xx+1)
	{
		if (xx==8)
			continue;
		printf("Continue dongusunun icinde, xx in degeri simdi %d\n",xx);
	}
}
