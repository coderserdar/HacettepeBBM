#define OTO 1
#define TEKNE 2
#define UCAK 3
#define GEMI 4

main()
{
struct otomobil {    /* bir otomobil icin structure         */
   int tekerlekler;
   int camurluklar;
   int kapilar;
};

typedef struct {     /* bir gemi yada tekne icin structure  */
   int su_kesimi;
   char boyu;
} TEKNEDEF;

struct {
   char tasit;         /* ne cins tasit ?                   */
   int agirlik;        /* tasitin gros agirligi             */
   union {             /* tipe-bagimli bilgi                */
      struct otomobil oto;      /* union'un birinci kismi   */
      TEKNEDEF tekne;           /* union'un ikinci kismi    */
      struct {
	 char motorlar;
	 int kanat_acikligi;
      } ucak;                   /* union'un 3uncu kismi      */
      TEKNEDEF ship;            /* union'un 4uncu kismi      */
   } tasit_tip;
   int deger;            /* tasitin bin TL olarak degeri     */
   char sahibi[32];      /* sahibinin ismi                   */
} ford, sun_fish, piper_cub;   /* 3 structure degiskeni      */

       /* birkac sahayi tanimlayalim                         */
   ford.tasit = OTO;
   ford.agirlik = 2742;              /* deposu dolu iken     */
   ford.tasit_tip.oto.tekerlekler = 5;  /* istepne dahil     */
   ford.tasit_tip.oto.kapilar = 2;

   sun_fish.deger = 3742;           /* trailer haric */
   sun_fish.tasit_tip.tekne.boyu = 5;
   piper_cub.tasit = UCAK;
   piper_cub.tasit_tip.ucak.kanat_acikligi = 9;

   if (ford.tasit == OTO)      /* evet , oyle  */
      printf("Ford'un %d tekerlegi var.\n",
	               ford.tasit_tip.oto.tekerlekler);

   if (piper_cub.tasit == OTO) /* hayir,degil */
      printf("Ucagin %d tekerlegi var.\n",piper_cub.tasit_tip.
	     oto.tekerlekler);
}
