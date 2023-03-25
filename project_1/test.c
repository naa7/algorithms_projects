/*Najeeb Al-Awadhi*/

#include <stdio.h>
#include <stdlib.h>

int quickselect(int *a,int k,int length);

int main(void)
{  
   long i; 
   int *space; int tmp;
   space =  (int *) malloc( 1000000*sizeof(int));
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 500001, 1000000)) != 1000000 )
   {  printf(" Failed test 1. Returned %d instead of 1000000\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test1\n");
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 1, 1000000)) != 0 )
   {  printf(" Failed test 2. Returned %d instead of 0\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test2\n");
   for( i=0; i< 500000; i++ )
   {  *(space + i) = ((139*i)%500000);
       *(space + i + 500000) = 1000000 + ((141*i)%500000);
   }
   if( (tmp = quickselect(  space, 124, 1000000)) != 123 )
   {  printf(" Failed test 3. Returned %d instead of 123\n", tmp); 
      fflush(stdout); exit(-1);
   }
   else printf("passed test3\n");



   printf("Quickselect successful\n");
   exit(0);
}