main()  /* KARSILAS.C: Bir suru karsilastirma */
{
int x = 11,y = 11,z = 11;
char a = 40,b = 40,c = 40;
float r = 12.987,s = 12.987,t = 12.987;
 
                    /* Birinci grup */
 
   if (x == y) z = -13;   /* z = -13 olacak           */
   if (x > z)  a = 'A';   /* a = 65  olacak           */
   if (!(x > z)) a = 'B'; /* bu hicbir sey yapmayacak */
   if (b <= c) r = 0.0;   /* r = 0.0 olacak           */
   if (r != s) t = c/2;   /* t = 20  olacak           */
 
                    /* Ikinci grup   */
 
   if (x = (r != s)) z = 1000; /* x pozitif olacak, ve
                             z = 1000 olacak       */
   if (x = y) z = 222;   /* bu, x = y, and z = 222 yapar */
   if (x != 0) z = 333;  /* z = 333 olacak   */
   if (x) z = 444;       /* z = 444 olacak */
 
                    /* Ucuncu grup */
 
   x = y = z = 77;
   if ((x == y) && (x == 77)) z = 33; /* z = 33 olur   */
   if ((x > y) || (z > 12))   z = 22; /* z = 22 olacak */
   if (x && y && z) z = 11;           /* z = 11 olur   */
   if ((x = 1) && (y = 2) && (z = 3)) r = 12.00; /* Bu ise,
                     x = 1, y = 2, z = 3, r = 12.00 yapar */

   if ((x == 2) && (y = 3) && (z = 4)) r = 14.56;
                            /* Birsey degistiremez */
 
                   /* Dorduncu grup */
 
if (x == x); z = 27.345;  /* z daima deger degistirir */
if (x != x)  z = 27.345;  /* Hicbirsey degismez    */
if (x = 0)   z = 27.345;  /* x = 0 olur, z degismez */

}
