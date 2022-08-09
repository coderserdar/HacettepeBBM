#include <dos.h>
ekransil()          /* bu rutin, ekrani siler */
{
	union REGS gir;

	gir.h.ah = 6;       /* servis no su 6 */
	gir.h.al = 0;       /* kac satir scroll edecegi 'donecegi' */
	gir.h.ch = 0;       /* sol ust kosenin satir no su */
	gir.h.cl = 0;       /* sol ust kosenin kolon no su */
	gir.h.dh = 23;      /* sag alt kosenin satir no su */
	gir.h.dl = 79;      /* sag alt kosenin kolon no su */
	gir.h.bh = 7;       /* yeni yaratilacak satirlar icin renk degeri */

	int86(16,&gir,&gir);
}
main()
{
	puts("acaba");
	ekransil();
	puts("Temiz");
}



