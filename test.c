#include <stdio.h>

void array();

void permute (int* a,int n, int limit);

int main() {
    
    array();
    return 0;
}

void array() {
    printf("Enter size of array: ");
    int length;
    scanf("%d",&length);
    if(length <= 0) {
        printf("Try again! please, enter a number greater than [0]\n");
        array(); }
    else {
        
        int b[length];
        printf("Enter elements of array : ");
        for (int i = 0; i < length; i++)
        {
            while (scanf("%d",&b[i])) break;
        }
        printf("##########\n");
        for (int i = 0; i < length; i++)
        {
            printf("a[%d] = %d\n", i, b[i]);
        }
        int limit = b[length-1];
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
    printf("##########\n");
    for (int i = 0; i < n; i++)
        printf("a[%d] = %d\n", i, a[i]);
    if (a[0] < limit)
        permute(a,n,limit);
    else 
        return;
    }