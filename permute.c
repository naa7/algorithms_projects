#include <stdio.h>

void array();

void permute (int* a,int n, int limit);

int main() {
    
    array();
    return 0;
}

void array() {

    int length;

    printf("Enter size of array : ");
    while(scanf("%d",&length)) break; 
    if(length <= 0) {
        printf("Try again! please, enter a number greater than [0]\n");
        array(); }
    else {
    
        int b[length];

        printf("Enter elements of array : ");
        for (int i = 0; i < length; i++)
        {
            while (scanf("%d",&b[i])) break;
            printf("value of a[%d] : %d\n",i,b[i]);
        }
        int limit = b[length-1];
        printf("###################\n");

        int *a = b;
    
        permute(a,length,limit);
    }
}

void permute (int* a,int n, int limit) {

    int i, tmp;

    tmp = a[0];
    for (int i = 0; i < n-1; i++)
     a[i] = a[i+1];  

    a[n-1] = tmp;
    for (int i = 0; i < n; i++)
        printf("value of a[%d] : %d\n",i,a[i]);

    printf("###################\n");
    if (a[0] < limit)
        permute(a,n,limit);
    else {
        
        int again;
        
        printf("Do you want to try again?\nEnter [1] for Yes and [0] for NO : ");
        while(scanf("%d",&again)) break;
        if(again == 1) array();
        else return;
    }
}   