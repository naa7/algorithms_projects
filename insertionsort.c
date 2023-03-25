#include <stdio.h>
#include <stdlib.h>
/* insertionsort sample code. insertionsort maintains a sorted array */
/* that grows by having the array elements inserted in it one by one */


/* insertionsort: sort integer array a[length] */
/* inserts a[i] in sorted array a[0]...a[i-1] */
void insertionsort(int *a, int length)
{  int i, j, tmp, breakflag;
   for( i=1; i< length; i++) /* insert a[i] in sorted array a[0]..a[i-1]*/
   {  tmp = a[i];  /*create gap at a[i] */
      breakflag = 0;
      for( j=i-1;  j>=0; j--)
      {  if(a[j] > tmp) 
	    a[j+1] = a[j]; /* move a[j] up, gap now at a[j] */
         else
	 {  a[j+1] = tmp; breakflag = 1; 
  	    break;
         }
      }
      if( ! breakflag ) /* gap is at a[0] */
	 a[0] = tmp;
   }
}

/*-------------------------------------------------------------------------*/
/*---demonstration test code ---------------------------------------------*/

main()
{  int e[10000]; int i;
   for(i=0; i< 10000; i++)
   {  
      e[(47*i+4123)%10000] = 11*i;
   }
   printf("prepared array.\n"); 
   printf("running insertionsort.\n");
   insertionsort(e,10000); printf("completed sorting, now testing.\n");
   for(i=0; i<10000; i++)
     if( e[i] != 11*i )
       {  printf("insertionsort failed.\n");
          break;
       }
   printf("finished test.\n");
}
