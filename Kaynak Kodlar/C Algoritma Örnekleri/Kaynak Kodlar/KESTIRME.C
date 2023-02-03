main()          /* Kestirme.C - C nin kestirme yonleri */
{
int x = 0,y = 2,z = 1025;
float a = 0.0,b = 3.14159,c = -37.234;

                                       /* Arttirma     */
   x = x + 1;       /* Bu x i bir arttirir */
   x++;             /* Bu da..           */
   ++x;             /*        Bu da..    */
   z = y++;         /* z = 2, y = 3 */
   z = ++y;         /* z = 4, y = 4 */


                                       /* Azaltma      */
   y = y - 1;       /* Bu y nin degerini bir azaltir */
   y--;             /* Bu da..           */
   --y;             /*          Buddah.. */
   y = 3;
   z = y--;         /* z = 3, y = 2 */
   z = --y;         /* z = 1, y = 1 */


                                 /* aritmetik islemler */
   a = a + 12;      /* a ya 12 eklemek        */
   a += 12;         /* 12 daha eklemek..      */
   a *= 3.2;        /* a yi 3.2 ile carpmak     */
   a -= b;          /* b yi a dan cikarmak      */
   a /= 10.0;       /* a yi ona bolmek          */

                                 /* sartli islemler      */
   a = (b >= 3.0 ? 2.0 : 10.5 );     /* Bu islem.......  */


   if (b >= 3.0)                     /* ve bu islemler..   */
      a = 2.0;                       /* birbiri ile aynidir*/
   else                              /* ve ayni sonucu     */
      a = 10.5;                      /* saglarlar.         */


   c = (a > b?a:b);        /* c, a yada b nin max ini alir */
   c = (a > b?b:a);        /* c, a yada b nin min ini alir.*/
}
