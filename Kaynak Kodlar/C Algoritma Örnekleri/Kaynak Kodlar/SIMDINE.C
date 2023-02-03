/* *************************************************************** */
/* Bu program, komut satirindan kelimeler okur, ve en sonuncusu    */
/* haric hepsini ekrana gosterir. En sonuncusu, klavyeden okunan   */
/* karakterlerle karsilastirmada kullanilir. Klavyeden bir tus     */
/* okunur. Sayet o tus karsilastirma listesinde varsa, onun        */
/* degeri, DOS'a ERRORLEVEL komutu ile dondurulur. Sayet basilan   */
/* tus listede yoksa, geriye 0 degeri dondurur.                    */
/* Bir Ornek:                                                      */
/*                                                                 */
/* SIMDINE Hangi Modeli istersiniz? ALR%3T                         */
/*                                                                 */
/* Hangi Modeli istersiniz?     <---- ekrana yazilir               */
/*    Sayet  a yada A ya basilirsa, errorlevel 1 doner.            */
/*    Sayet  l yada L ye basilirsa, errorlevel 2 doner.            */
/*    Sayet  r yada R ye basilirsa, errorlevel 3 doner.            */
/*    Sayet  % ye basilirsa, errorlevel 4 doner.                   */
/*    Sayet  3 e basilirsa, errorlevel 5 doner.                    */
/*    Sayet  t yada T ye basilirsa, errorlevel 6 doner.            */
/*    Sayet herhangi baska bir tusa basilirsa, 0 doner.            */
/*                                                                 */
/*  En fazla dokuz tus kontrol edilebilir. ERRORLEVEL ise, bir     */
/*  yigit (batch) kutugunde kontrol edilebilir.                    */
/*  Not: Bu programi, bu pakette gelen SIMDI.BAT ile               */
/*       kullanabilirsiniz  -turgut                                */
/* *************************************************************** */

#include "stdio.h"
#include "ctype.h"

main(rakam,kelime)
int rakam;               /* Komut satirinda kac kelime oldugu    */
char *kelime[];
{
int index;                 /* bir sayac ve artirma degiskeni       */
int c;                     /* karsilastirma yapilacak karakter     */
int code;                  /* sonucta donecek errorlevel degeri    */
char bir_sonraki_kar;      /* karsilastirmada kullanilir           */
char *point;               /* rahatlik icin kullanilan bir pointer */

                     /* Ilk kelime,hep kutuk ismi olur, ve en az   */
                     /* iki sahaya daha ihtiyac var. Yani, 3 den   */
                     /* az ise, programi terk.                     */
   if (rakam < 3) {
      printf("Komut satirinda soru verilmedi\n");
      exit(0);
   }

                       /* ikinciden n-1 e kadar kelimeleri yazalim */
   rakam--;
   for(index = 1;index < rakam;index++)
      printf("%s ",kelime[index]);
  
                /* kullanicinin cevabini alalim, buyuk harf yapalim */
   c = getch();
   printf("%c\n",c);

   if (islower(c))
      c = toupper(c);

   point = kelime[rakam]; /* En son yazilan kelimeyi gostersin      */

   code = 0;
   index = 0;
   do {             /* en son kelimedeki cevaplara bakalim          */
      bir_sonraki_kar = *(point + index);
	 
      if (islower(bir_sonraki_kar))
         bir_sonraki_kar = toupper(bir_sonraki_kar);  /* Buyuk harf */
	    
      if(bir_sonraki_kar == c)                  /* Sayet bulunduysa */
         code = index + 1;           /* bulunan degeri saklayalim   */
	    
      index++;
   } while (*(point + index));       /* ta ki NULL gorununceye kadar*/

   exit(code);                /* Bulunan degeri sisteme dondurelim  */
}
