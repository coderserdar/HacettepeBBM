main()
{
	int a;              /* basit tamsayi tipi              */
	long int b;         /* uzun tamsayi tipi               */
	short int c;        /* kisa tamsayi tipi               */
	unsigned int d;     /* isaretsiz (+ - siz) tamsayi     */
	char e;             /* karakter tipi                   */
	float f;            /* kayar nokta tipi                */
	double g;           /* cift hassasiyet kayar nokta     */
 
	a = 1023;
	b = 2222;
	c = 123;
	d = 1234;
	e = 'X';
	f = 3.14159;
	g = 3.1415926535898;
 
	printf("a = %d\n",a);      /* desimal               */
	printf("a = %o\n",a);      /* oktal                 */
	printf("a = %x\n",a);      /* heksadesimal          */
	printf("b = %ld\n",b);     /* uzun desimal          */
	printf("c = %d\n",c);      /* kisa desimal          */
	printf("d = %u\n",d);      /* isaretsiz             */
	printf("e = %c\n",e);      /* karakter              */
	printf("f = %f\n",f);      /* kayar nokta           */
	printf("g = %f\n",g);      /* cift hassasiyet k.n   */
	printf("\n");
	printf("a = %d\n",a);      /* basit 'int' cikti          */
	printf("a = %7d\n",a);     /* 7 uzunlukta bir saha kullan*/
	printf("a = %-7d\n",a);    /* sola dayali 7 lik saha     */
	printf("\n");
	printf("f = %f\n",f);      /* basit kayan nokta     */
	printf("f = %12f\n",f);    /* 12 lik bir saha kullan*/
	printf("f = %12.3f\n",f);  /* noktadan sonra 3 hane */
	printf("f = %12.5f\n",f);  /* noktadan sonra 5 hane */
	printf("f = %-12.5f\n",f); /* sola yapisik 12 hane  */
}
