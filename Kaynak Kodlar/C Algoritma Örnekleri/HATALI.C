#define HATALI(A) A*A*A     /* Kup icin hatali makro */
#define KUP(A) (A)*(A)*(A)  /* Dogusu ...            */
#define KARE(A) (A)*(A)     /* Karesi icin dogru makro */
#define START 1
#define STOP  9

main()
{
int i,offset;

   offset = 5;

   for (i = START;i <= STOP;i++) {
      printf("%3d in karesi %4d dir, ve kubu ise %6d dir..\n",
              i+offset,KARE(i+offset),KUP(i+offset));

      printf("%3d in HATALIsi ise %6d dir.\n",i+offset,HATALI(i+offset));
   }
}
