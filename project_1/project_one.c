#include <stdlib.h>
#include <stdio.h>

int randomindex(int k) {
    return (rand() % k);
}

extern int quickselect(int *a,int k,int length) {
    int i,j1,j2,pivot,tmp;
    if (length > 1)
    {
        i = randomindex(length);
        pivot=a[i]; a[i]=a[length-1]; a[length-1]=pivot;
        j1=0; j2=length-1;
        while (j1<j2)
        {
            for(;a[j1]<pivot;j1++);
            for(;a[j2]>=pivot && j2>j1;j2--);
            if(j1!=j2) {
                tmp=a[j1]; a[j1]=a[j2]; a[j2]=tmp;
            }
        }
        a[length-1]=a[j1]; a[j1]=pivot;
        if (k<=j1+1)
            return quickselect(a,k,j1+1);
        else 
            return quickselect(a+j1+1,k-j1-1,length-j1-1);
    }
    else {
        if (k==1)
            return(a[0]);
        else { 
            printf("error. called with array of length %d looking element %d\n", length, k); 
            exit(-1);
        }
    }
}