#include <stdlib.h>


/* generates a random integers in interval 0 ... k-1, */
/* using the  rand() function from the standard library */
/* works satisfactorily only if k < RAND_MAX */
int randomindex( int k )
{ return(  rand() % k );
}



/* quicksort: sort integer array a[length] ; standard quicksort */
/* sorts in increasing order */
/* uses the original partition method by Hoare */
void quicksort(int *a, int length)
{  int i, j1, j2, pivot, tmp;
   if(length>1)
     {  i = randomindex(length);
        pivot = a[i]; a[i] = a[length-1]; a[length-1] = pivot;  
        j1 = 0; j2 = length-1;
        while(j1 < j2 )        
	  {  for(; a[j1] < pivot ; j1++) 
	        ; 
 	     for(; a[j2] >= pivot && j2 > j1 ; j2-- )
	        ;
             if( j1 != j2 )
	       {  tmp = a[j1]; a[j1] = a[j2]; a[j2] = tmp;
               }
          }
        /* insert pivot element at correct place */
        a[length-1] = a[j1]; a[j1] = pivot;
	/* recursive calls for smaller and larger subarray */
        quicksort( a, j1);
        quicksort( a +j1+1, length -j1 -1);
     }
}
