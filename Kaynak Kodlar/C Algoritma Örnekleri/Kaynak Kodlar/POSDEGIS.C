#include <dos.h>

void yerlestir(satir,kolon)     /* bu fonksiyon, cursorun yerini    */
unsigned satir,kolon;           /* BIOS yardimi ile degistir        */
{
    union REGS giris_register,cikis_register;

    giris_register.h.ah = 2;    /* 2: set-cursor-position fonksiyonu */
    giris_register.h.dh = satir;
    giris_register.h.dl = kolon;
    giris_register.h.bh = 0;    /* hangi sayfayi degistirelim? */

    int86(16,&giris_register,&cikis_register);    /* cagiralim */
}



main()
{
	int i;
	for (i=0;i<24;i++)
		puts("");
	yerlestir(10,50);
	printf("AHA!!");
}

