#include <stdio.h>
main()
{
FILE *point;
char digerleri[35];
int index,say;

   strcpy(digerleri,"Additional lines.");
   point = fopen("onsatir.txt","a"); /* eklemek icin acmak */

   for (say = 1;say <= 10;say++) {
      for (index = 0;digerleri[index];index++)
	 putc(digerleri[index],point);  /* bir karakter yaz  */
      putc('\n',point);                /* bir de <RETURN>   */
   }
   fclose(point);
}
