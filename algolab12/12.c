#include<stdio.h>
#include<stdlib.h>
void addEdge(int **g,int i,int j) {
    g[i][j]=1;
}
void gsort(int *a,int **g,int *v,int in,int n,int m) {
    int i,j;
    for(i=0;i<n;i++)
        if(g[in][i]==1&&v[i]==0) {
            gsort(a,g,v,i,n,m);
            v[i]=1;
            gsort(a,g,v,in,n,m);
            return;
        }
    if(m==in) printf("%d",a[in]);
    else printf("%d, ",a[in]);
}
int main(int argc,int **argv) {
    int n=argc-1;
    int i,j,cc=n;
    if(cc==0) {
        printf("Enter value of n : ");
        scanf("%d",&n);
        printf("Enter the %d values :\n",n);
    }
    if(n==0) { printf("Zero Size!\n"); return 0; }
    int *a;
    a=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        if(cc==0) scanf("%d",&a[i]);
        else a[i]=atoi(argv[i+1]);
    }
    int **g;
    g=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++) {
        g[i]=(int*)malloc(n*sizeof(int));
        for(j=0;j<n;j++) g[i][j]=0;
    }
    for(i=0;i<n;i++) {
        for(j=i+1;j<n;j++)
            if(a[i]==a[j]) { printf("Non-Distinct Numbers!\n"); return 0; }
            else if(a[i]>a[j]) addEdge(g,i,j);
            else addEdge(g,j,i);
    }
    int max=0;
    for(i=1;i<n;i++) if(a[max]<a[i]) max=i;
    int *v;
    v=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) v[i]=0;
    printf("Sorted List :\n");
    gsort(a,g,v,max,n,max);
}
