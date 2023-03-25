
/* my attempt at a three-way merge sort */

void merge_sort(int *a, int *aux, int length)
{   int i, j1, j2, j3, tmp;
    if( length <= 1)
       return;
    if( length == 2)
    {  if( a[0] > a[1] )
	{  tmp = a[0]; a[0] = a[1]; a[1] = tmp;
	}
       return;
    }
    else /* length >=3 */
      {  int empty1=0, empty2=0, empty3=0, min, *min_index;
       merge_sort(a, aux, (length/3) ); /* recursive calls */
       merge_sort(a + (length/3), aux, (length/3) );
       merge_sort(a + 2*(length/3), aux, (length - 2*(length/3)) );
       for( i=0, j1=0, j2=(length/3), j3=2*(length/3) ; i<length; )/*merging*/
       {  if( j1== length/3) empty1 = 1;
	  if( j2== 2*(length/3)) empty2 = 1;
          if( j3== length) empty3 = 1;
          if( !empty1 ) { min=a[j1]; min_index =&j1; }        
          if( !empty2 ) { min=a[j2]; min_index =&j2; }        
          if( !empty3 ) { min=a[j3]; min_index =&j3; }        
          /* now min is valid value, and min_index points to it */
          if( !empty1 && a[j1] < min )
                    { min=a[j1]; min_index =&j1; }        
          if( !empty2 && a[j2] < min )
                    { min=a[j2]; min_index =&j2; }        
          if( !empty3 && a[j3] < min )
                    { min=a[j3]; min_index =&j3; }        
	  aux[i++] = a[(*min_index)++];
         
        }
        for( i = 0; i< length; i++) /* copying back */
           a[i] = aux[i]; 
    }
}

