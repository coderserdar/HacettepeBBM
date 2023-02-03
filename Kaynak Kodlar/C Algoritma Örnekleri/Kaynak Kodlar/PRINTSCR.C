#include <dos.h>
main()
{
    union REGS in;      /* buna ihtiyacimiz yok, ama tanimlamamiz lazim */

    int86(5,&in,&in);        /* print-screen yapalim */

}

