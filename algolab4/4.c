#include<stdio.h>
#include<stdlib.h>


void lps(int,int,int,int);

int main() {
    int n,m,l,i;
    printf("Enter value of n : ");
    scanf("%d",&n);
    lps(n,1,1,n);
    for(i=1,m=0;i<n;m++,i*=2);
    i/=2;m--;l=n-i;
    printf("\nChecking the Formula\nm = %d",m);
    printf("\nl = %d\nAnswer = 2*(l+1) = %d",l,(2*l+1));
}

void lps(int n,int a,int d,int m) {
    if(n==1) {
        printf("\nLast man standing is %d.",a);
        return;
    }
    int i=a,j=0,l,k;
    while(i+d<=m) {
        j++;
        i=i+d;
        if(i>m) break;
        printf("%d ",i);
        i=i+d;
    }
    if(i<=m) { printf("%d ",a); a=a+2*d; j++; }
    lps(n-j,a,2*d,m);
}
