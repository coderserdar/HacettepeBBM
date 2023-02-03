#include <stdio.h>
#include <string.h>
#include <malloc.h>

short int sortcolumn=0;		/* Which column will we sort from? */

strcmpn(first, second)		/* reverse order sort */
char    *first;
char    *second;
{
    while (*first == *second) {
       if (*first) {
           first++;
           second++;
       }
       else return 0;
    }
    return *second - *first;
}

void show_help()
{
 fputs("\nThis program can sort large ASCII files, very quickly.\n",stderr);
 fputs("Recommended input file size: 0 - 600K \n",stderr);
 fputs("\nThe syntax is : BIGSORT [/+nn][/I|/R] < infile > outfile\n\n",stderr);
 fputs("where:\n",stderr);
 fputs("* infile: the name of your input file (default, keyboard)\n",stderr);
 fputs("* outfile:the name of your output file(default, screen)\n\n",stderr);
 fputs("Options: /I makes BIGsort case-insensitive.\n",stderr);
 fputs("         /R Reverses the sort order (Z->A)\n",stderr);
 fputs("         /+nn begins sorting at column 'nn'\n\n",stderr);
 fputs("If you find this program valuable, please contribute to the\n",stderr);
 fputs("public domain idea - Send a $10 check to the above address.\n",stderr);
 fputs("Thank You!\n",stderr);
 exit(0);
}

/****************************************************/
/* Quick Sort on a string array                     */
/****************************************************/
/* Inputs: an array (pa) of pointers to the data  - any kind of data.
   NA: number of items
   pcomp: the address of a function of comparison
*/
 
int qsort(pa,na, pcomp)
char *pa[];
int na;
int (*pcomp) ();
{
        int i,j,temp,nr;
        char *ptemp,*ppart;
 
        if (na<2) return;
 
        ppart = pa[na/2];
        i = -1; j = na;
 
        while (1)
        {
          do { i++; } while ((*pcomp)(pa[i]+sortcolumn,ppart+sortcolumn)<0);
          do { j--; } while ((*pcomp)(pa[j]+sortcolumn,ppart+sortcolumn)>0);
 
          if (i>=j) break;
 
          ptemp = pa[i];    pa[i] = pa[j];
          pa[j] = ptemp;
 
        }
 
        nr = na - i;
 
        if (i<na/2)
        {       qsort(pa,i,pcomp);
                qsort (&(pa[i]), nr, pcomp);
        }
        else
        {
                qsort (&(pa[i]),nr, pcomp);
                qsort (pa , i, pcomp);
        }
}
 
void main(argc,argv)
int argc;
char *argv[];
{
     int i,j;
     int (*fun) ();
     char *p[5000];
     char buffer[1024];
     
     fputs("BIGsort V2.0 (C)1988 Turgut Kalfaoglu, 1378 Sok.8/10, Izmir 35210, Turkey\n",stderr);
     fputs("Use BIGSORT HELP for info\n",stderr);

     fun = strcmp;

     for (i=1;i<argc;i++)
     {    if (strcmpi("/I",argv[i])==0)
               fun = strcmpi;

          if (*(argv[i])=='/' && *(argv[i]+1)=='+')
               sortcolumn=atoi(argv[i]+2)-1;

          if (strcmpi("HELP",argv[i])==0)
               show_help();
			
		if (strcmpi("/R",argv[i])==0)
			fun = strcmpn;

     }
     i=0;
     while (gets(buffer))   /* Read in file */
     {
        if (i>4998 || ( p[i] = (char *) calloc(strlen(buffer)+1, sizeof(char))) == NULL)
        {    fputs("BIGtrouble: Out of memory",stderr);
              exit(1);
        }
        strcpy(p[i++],buffer);
     }
     qsort(p,i, fun);
     for (j=0;j<i;j++) puts(p[j]);
}
