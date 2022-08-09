/* SortNum.C - Verilen degerleri siralamak. */

#include <stdio.h>

main()
{
     int i,n,t;
     int a[100];
     
     printf(" Rakamlar giriniz - (bitirmek icin Q yazin) ");
     n=0;
     
     while (scanf("%d",&t)!=0)
          a[n++]=t;
     
     sortn(a,n);
     
     for (i=0;i<n;i++)
          printf(" %d",a[i]);
}

sortn(x,nx)           /* Bir dizini siraya sokar */
int x[];              /* 'selection sort'        */
int nx;
{
     int i,j,pick;
     
     for (i=0 ; i < (nx-1) ; i++)
     {
          pick = i;
          for(j=i+1 ; j<nx; j++)
          {
               if (x[j]<x[pick])
                    pick=j;
          }
          swap( &x[pick], &x[i]);
     }
}

int swap(p1,p2)
int *p1 , *p2;
{
     int temp;
     
     temp = *p1;
     *p1 = *p2;
     *p2 = temp;
}
