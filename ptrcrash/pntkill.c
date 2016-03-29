#include<stdio.h>
#include<stdlib.h>
int main() {
    long long int *a,*b,i=0;
    b=NULL;
    //*b=10;

    throw 1;
    a=(int*)malloc(100*sizeof(int));
    a=NULL;
    //printf("%d",&b);
    while(1) {
        a[i++]=100;
        printf("\n%d   %d\n",&i,&a[i]);
    }
}

