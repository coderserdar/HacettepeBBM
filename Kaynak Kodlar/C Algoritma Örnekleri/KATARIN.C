#include <stdio.h>

main()
{
char big[25];

    printf("Karakter katari girin, en fazla 25 karakter.\n");
    printf("Birinci kolonda X yazarak programi bitirin.\n");

    do {
       scanf("%s",big);
       printf("Yazdiginiz katar -> %s\n",big);
    } while (big[0] != 'X');

    printf("Programin sonu.\n");
}
