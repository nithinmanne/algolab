#include<stdio.h>
#include<stdlib.h>
int lps(int n) { if(n==1) return(1); return(2*lps(n/2)-1); }
int main() {
    printf("Enter value of n : ");
    int n,l;
    scanf("%d",&n);
    l=lps(n);
    printf("Last Person Standing = %d",l);
}
