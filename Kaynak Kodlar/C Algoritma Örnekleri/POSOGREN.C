#include <dos.h>

void posogren(satir, kolon)  /* Bu fonksiyon, cursorun yerini BIOS yardimi */
unsigned *satir, *kolon;     /* ile ogrenir */
{
	union REGS giris,cikis;

	giris.h.ah = 3;     /* fonksiyon 3 - cursorun yerini oku */
	giris.h.bh = 0;     /* 0 inci sayfa.. */

	int86(16,&giris,&cikis);

	*satir = cikis.h.dh;
	*kolon = cikis.h.dl;
}

main()
{
	int a,b;
	posogren(&a,&b);
	printf(" Program calistiginda cursor %d. satir, %d. kolonda idi\n",a,b);
}



