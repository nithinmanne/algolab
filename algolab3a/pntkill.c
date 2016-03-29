#include<stdio.h>
#include<stdlib.h>
int main() {
    int *a,*b,i=0;
    b=NULL;
    //*b=10;
    a=(int*)malloc(1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000*sizeof(int));
    //printf("%d",&b);
    while(1) {
        a[i++]=100;
        printf("%d",&a[i]);
    }



}
