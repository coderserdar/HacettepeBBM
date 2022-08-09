#include <stdio.h>

main()
{
int index;

   for (index = 0;index < 6;index++) {
      printf("Bu satir, standart ciktiya gidiyor.\n");
      fprintf(stderr,"Bu satir ise standart hataya gidiyor.\n");
   }

   exit(4);  /* Bu komut, DOS 'un ERRORLEVEL komutu ile bir batch file'da
		(yigit kutugunde) kontrol edilebilir. Bu programin
		d”nd£rd£g£ deger, soyle kontrol edilebilir:

		A> COPY CON: DENE.BAT   <RETURN>

		OZEL
		IF ERRORLEVEL 4 GOTO DORT
		(Dortten kucukse, buraya devam eder..)
                .
                .
		GOTO BITTI
		:DORT
		(dort yada buyukse, buraya devam eder)
                .
                .
		:BITTI

		<F6> <RETURN>

								  */
}
