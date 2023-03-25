#include <stdio.h>
#include <stdlib.h>
/* selectionsort sample code. selectionsort maintains a sorted array */
/* that grows by having the array elements appended to it in increasing order*/


/* selectionsort0: sort integer array a[length] */
/* finds largest element in a[0]....a[n-i], puts it in a[n-i] */
void selectionsort0(int *a, int length)
{  int i, j, k,tmp;
   for( i=1; i< length; i++) 
   {  tmp = a[0]; k=0;
      for( j=1; j<= length -i; j++)
      {  if( a[j] > tmp )
 	 {  tmp = a[j]; k=j;
         }
      }  /* now tmp=a[k] is the largest element in a[0]...a[length-i] */
      a[k] = a[length -i];
      a[length-i] = tmp; /*move it in the position a[length-i] */ 
   }
}

/* selectionsort1: sort integer array a[length] */
/* extends sorted array a[0]...a[i-1] by finding the smallest element  */
/* among a[i]...a[n-1], and adding that at the end of the sorted array */ 
void selectionsort1(int *a, int length)
{  int i, j, temp;
   for( i=0; i< length-1; i++)
   {  for( j=i+1;  j< length; j++)
      {  if(a[i] > a[j]) 
         {  temp = a[i]; a[i] = a[j]; a[j] = temp; /*exchange*/
         } 
      }
   }
}

/*-------------------------------------------------------------------------*/
/* selectionsort2: sort integer array a[length]; recursive selectionsort */
/* sorts in increasing order, finds largest item first, puts it last, */
/* sorts the rest recursively */
void selectionsort2(int *a, int length)
{  int j, temp;
   for( j = 0; j< length-1; j++)
      if(a[length-1] < a[j]) 
      {  temp = a[j]; a[j] = a[length-1]; a[length-1] = temp;
      }
   if( length > 1) 
      selectionsort2(a,length-1);
}

/*-------------------------------------------------------------------------*/
/*---demonstration test code ---------------------------------------------*/

main()
{  int b[10000], c[10000], d[10000]; int i;
   for(i=0; i< 10000; i++)
   {  b[(37*i+1234)%10000] = 3*i;
      c[(41*i+2341)%10000] = 5*i;
      d[(43*i+3412)%10000] = 7*i;
   }
   printf("prepared arrays.\n"); 
   printf("running selectionsort0.\n");
   selectionsort0(b,10000); printf("running selectionsort1.\n");
   selectionsort1(c,10000); printf("running selectionsort2.\n");
   selectionsort2(d,10000); 
   printf("completed sorting, now testing.\n");
   for(i=0; i<10000; i++)
     if( b[i] != 3*i )
       {  printf("selectionsort0 failed.\n");
          break;
       }
   for(i=0; i<10000; i++)
     if( c[i] != 5*i )
       {  printf("selectionsort1 failed.\n");
          break;
       }
   for(i=0; i<10000; i++)
     if( d[i] != 7*i )
       {  printf("selectionsort2 failed.\n");
          break;
       }
   printf("finished test.\n");
}
