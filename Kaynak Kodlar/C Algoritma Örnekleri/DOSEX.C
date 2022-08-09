/******************************************************************/
/* Bu ornek program, sunlarin nasil yapildigini gosterir:         */
/*  1. DOS dan saat ve tarihin okunmasi                           */
/*  2. Cursor'un ekranda herhangi bir yere konmasi                */
/*  3. Klavyeden karakterler okunmasi, ve kodlarinin gosterilmesi */
/*  4. Ekrandaki bir pencerenin scroll edilmesi                   */
/*  5. Okunmasini kolaylastirmak icin programi iyi duzenlemek     */
/******************************************************************/

#include "stdio.h"
#include "dos.h"

main()
{
int saat, dakika, saniye, eski_san;
int karakter;

   kutu_ciz();              /* Window'un cevresine kutu cizer   */
   eski_san = 0;             /* Bu degisken eski zamani saklar   
                               - ki degisti mi diye bakabilelim */

   do {
      if (kbhit()) {                     /* Bir tusa mi basildi?*/
         karakter = getch();             /* karakteri oku       */
         goster_kar(karakter);           /* goster              */
      }

      zamani_al(&saat,&dakika,&saniye);      /* zamani ogrenelim    */ 
      if (saniye != eski_san) {              /* degistiyse,         */
         goster_zaman_tarih();               /* ekrani goster       */
         eski_san = saniye;                  /* yeni zamani sakla   */
      }

   } while (karakter != 'Q');        /* Q ya basilinca dur.    */

   cursoru_koy(0,0);              /* Ekrana cursor u koy         */
}


/* **************************************************** kutu_ciz*/
/* Bu rutin, ekrana bir kutu cizer. Basilan tuslar, saat ve     */
/* tarih bu kutularda gorunur. Ozel bir numara yok burada,      */
/* sadece standart printf ile cizilen kutular..                 */
/* ************************************************************ */
kutu_ciz()
{
int index;
char satir[81];

   for (index = 0;index < 80;index++)       /* 3 bos satir      */
      satir[index] = ' ';
   satir[80] = NULL;                            /* katarin sonu  */
   for (index = 0;index < 3;index++)
      printf("%s",satir);

   satir[8] = 201;                       /* kutunun ust satiri    */
   for (index = 9;index < 70;index++)
      satir[index] = 205;
   satir[70] = 187;
   printf("%s",satir);

   satir[8] = 186;                    /* buyuk pencerenin ustu   */
   for (index = 9;index < 70;index++)
      satir[index] = ' ';
   satir[70] = 186;
   for (index = 0;index < 15;index++)
      printf("%s",satir);

   satir[8] = 204;                    /* pencereler arasindaki cizgi */
   for (index = 9;index < 70;index++)
      satir[index] = 205;
   satir[70] = 185;
   printf("%s",satir);

   satir[8] = 186;                    /* tarih/saat'in kenari    */
   for (index = 9;index < 70;index++)
      satir[index] = ' ';
   satir[70] = 186;
   printf("%s",satir);

   satir[8] = 200;                     /* kutunun alti            */
   for (index = 9;index < 70;index++)
      satir[index] = 205;
   satir[70] = 188;
   printf("%s",satir);

   for (index = 0;index < 80;index++)       /* 3 bos satir      */
      satir[index] = ' ';
   for (index = 0;index < 3;index++)
      printf("%s",satir);

}


/* ************************************************** goster_kar*/
/* Bu rutin, basilan tusu ekranda gosterir. Sayet ilk karakter  */
/* sifir ise, ozel bir tusa basilmis demektir. O zaman, bundan  */
/* sonraki tus okunur, ve sonuc ekrana yazilir.                 */
/* ************************************************************ */
goster_kar(tus)
int tus;
{
   pencere_scroll();
   cursoru_koy(17,15);          /* mesajin yerini ayarlayalim    */

   if(tus == 0) {
      printf(" 00 ");            /* ozel bir tusa basilmis!     */
      tus = getch();          /* bundan sonraki tusu oku     */
      switch (tus) {
         case 59  :
         case 60  :
         case 61  :
         case 62  :
         case 63  :              /* bunlar fonksiyon tuslari    */
         case 64  :
         case 65  :
         case 66  :
         case 67  :
         case 68  : printf("%4d Fonksiyon tusu F%d\n",tus,tus-58);
                    break;

         case 94  :
         case 95  :
         case 96  :
         case 97  :
         case 98  :         /* bunlar ctrl-fonksiyon tuslari    */
         case 99  :
         case 100 :
         case 101 :
         case 102 :
         case 103 : printf("%4d Fonksiyon tusu Ctrl-F%d\n",tus,
                       tus-93);
                    break;

         case 84  :
         case 85  :
         case 86  :
         case 87  :        /* bunlar SHIFT-fonksiyon tuslari    */
         case 88  :
         case 89  :
         case 90  :
         case 91  :
         case 92  :
         case 93  : printf("%4d Fonksiyon tusu SHIFT-F%d\n",tus,
                       tus-83);
                    break;

         case 104 :
         case 105 :
         case 106 :
         case 107 :
         case 108 :          /* bunlar da alt-fonksiyon tuslari */
         case 109 :
         case 110 :
         case 111 :
         case 112 :
         case 113 : printf("%4d Fonksiyon tusu Alt-F%d\n",tus,
                       tus-103);
                    break;

         default  : printf("%4d Ozel tusa basildi\n",tus);
      }

   } else                        /* normal bir tusa basilmis    */ 
      printf("    %4d (%c) Tusuna basildi\n",tus,tus);

   cursoru_koy(25,1);        /* cursor'u 26. satira saklayalim    */
}


/* *************************************************** zamani_al*/
/* Bu rutin, DOS u cagirarak, gunun zamanini ogrenir. Cagiran   */
/* programa kendisine gecirilmis olan 3 pointer'da bu bilgiyi   */
/* dondurur..                                                   */
/* ************************************************************ */
zamani_al(saat,dakika,saniye)
int *saat, *dakika, *saniye;
{
union REGS gir_reg;
union REGS cik_reg;

   gir_reg.h.ah = 44;               /* Hex 2C - Simdiki zamani al */
   int86(0x21,&gir_reg,&cik_reg);
   *saat = cik_reg.h.ch;
   *dakika = cik_reg.h.cl;
   *saniye = cik_reg.h.dh;
}


/* *******************************************goster_zaman_tarih*/
/* Bu rutin, zamani ve tarihi ekranda sabit bir noktada         */
/* gosterir. Zamani zamani_al fonksiyonundan ogrenir, ve tarihi,*/
/* kendi icindeki bir DOS cagirimindan alir. Iyi programlama    */
/* teknigi, tarihin de ayri bir rutine konmasini soyler, ama biz*/
/* sadece islerin nasil yapildigini degisik yollardan gostermek */
/* amaci ile yapiyoruz. Bu rutin ayni zamanda cursor_koy ile    */
/* saat ve tarihi sabit bir yere koyar.                         */
/* ************************************************************ */
goster_zaman_tarih()
{
int saat, dakika, saniye;
union REGS gir_reg;
union REGS cik_reg;

   cursoru_koy(19,19);  /* Saat ve takvim icin yer               */

   gir_reg.h.ah = 42;              /* hex 2A - tarih nedir?      */
   int86(0x21,&gir_reg,&cik_reg);  /* interrupt 21               */      
   printf("Tarih= %2d/%2d/%2d    ",
      cik_reg.h.dh,                 /* ay  - 1 den 12           */
      cik_reg.h.dl,                 /* gun - 1 den 31           */
      cik_reg.x.cx);                /* yil - 1980 den 2099      */

   zamani_al(&saat, &dakika, &saniye);
   printf("Saat = %2d:%2d:%2d\n",saat, dakika, saniye);

   cursoru_koy(25,1);        /* cursoru 26. satira saklayalim    */
}

/* *************************************************cursoru_koy */
/* Bu rutin, cursoru istenilen yere koyar. Sol ust kose, satir 0*/
/* ve kolon 0 dir.                                              */
/* ************************************************************ */
cursoru_koy(satir,kolon)
char satir, kolon;
{
union REGS gir_reg;
union REGS cik_reg;

   gir_reg.h.ah = 2;        /* servis 2 - cursoru yerlestir      */
   gir_reg.h.dh = satir;
   gir_reg.h.dl = kolon;
   gir_reg.h.bh = 0;
   int86(0x10,&gir_reg,&cik_reg);                /* interrupt 10 */
}


/* ********************************************** pencere_scroll*/
/* Basilan tus penceresindeki herseyi bir satir yukari kaydirir,*/
/* yeni yazilacak seylere yer acar.                             */
/* ************************************************************ */
pencere_scroll()
{
union REGS gir_reg;
union REGS cik_reg;

   gir_reg.h.ah = 6;      /* servis  6 - pencereyi scroll        */
   gir_reg.h.al = 1;      /* kac satir kayacagi                  */
   gir_reg.h.ch = 3;      /* pencerenin ust satiri               */
   gir_reg.h.cl = 9;      /* pencerenin sol kolonu               */
   gir_reg.h.dh = 17;     /* pencerenin alt satiri               */
   gir_reg.h.dl = 69;     /* pencerenin sag kolonu               */
   gir_reg.h.bh = 7;      /* acilan bos satir(larin) 'rengi'     */
   int86(0x10,&gir_reg,&cik_reg);                /* interrupt 10 */

}
