main()
{
int index;

   index = 8;
   geri_say(index);
}

geri_say(rakam)
int rakam;
{
   rakam--;
   printf("rakam degeri %d dir.\n",rakam);
   if (rakam > 0)
      geri_say(rakam);
   printf("Simdi rakam %d oldu..\n",rakam);
}
