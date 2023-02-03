#include <dos.h>

ekranayar(tip)      /* Bu fonksiyon, ekrani istegimiz tipe ayarlar */
short tip;
{
	union REGS giris,cikis;

	giris.h.ah = 0;  /* 0 inci servis - mod degistirmek */
	giris.h.al = tip;   /* CGA; 0: b/w text 40x25,    1: 16 renk 40x25
						   2: b/w text 80x25     3: 16 renk 80x25
						   4: 4 renk Gra 320x200 5: 4 gri Gra 320x200
						   6: b/w Gra 640x200
					   MONO: 7: b/w text 80x25    */

	int86(16,&giris,&cikis); /* ayarlayalim */
}

