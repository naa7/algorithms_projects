#include <stdio.h>
#include <stdlib.h>


/* mergesort: sort integer array a[length] ; standard mergesort */
/* sorts in increasing order, requires auxiliary array */
void mergesort(int *a, int *aux, int length)
{ int i, j1, j2;
  if(length>1)
    {  mergesort(a, aux, (length/2) ); /* recursive calls */
       mergesort(a + (length/2), aux, (length - (length/2)));
       for( i = 0, j1 =0, j2= (length/2) ; i< length; ) /* merging */
       {   if( ( j1 < (length/2) && a[j1] < a[j2]) || j2 == length) 
	      aux[i++] = a[j1++];
           else
	      aux[i++] = a[j2++];
         
        }
        for( i = 0; i< length; i++) /* copying back */
           a[i] = aux[i]; 
    }
}

