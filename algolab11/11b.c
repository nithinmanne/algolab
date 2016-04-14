#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int scmp(const void *p,const void *q) {
    int l=((int*)p)[0];
    int r=((int*)q)[0];
    return(l-r);
}

int med(int a[],int l,int lu,int u) {
    if(u<lu||u-l<=5) {
        int s=u-l;
        qsort(&a[l],s,sizeof(int),scmp);
        return(a[l+(s-1)/2]);
    }
    else if(lu-l==5) {
        qsort(&a[l],5,sizeof(int),scmp);
        return(a[l+2]);
    }
    int *b,i,n=(u-l+4)/5;
    b=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) b[i]=med(a,l+5*i,l+5*i+5,u);
    return(med(b,0,0,n));
}

int part(int a[],int l,int u) {
    if(l==u) return(l);
    int m=med(a,l,l,u);//printf("med  %d\n",m);
    int n=u-l,i;
    int *bm,*am,bmn=0,amn=0;
    bm=(int*)malloc(n*sizeof(int));
    am=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        if(a[l+i]<m) { bm[bmn]=a[l+i]; bmn++; }
        else if(a[l+i]>m) { am[amn]=a[l+i]; amn++; }
    }
    for(i=0;i<bmn;i++) a[l+i]=bm[i];
    a[l+i]=m;
    m=l+i;
    for(i=0;i<amn;i++) a[l+i+bmn+1]=am[i];
    return(m);
}

int ksel(int a[],int l,int u,int k) {
    int p=part(a,l,u);//printf("%d  %d  %d  %d\n",l,u,p,a[p]);
    if(k-1>p) return(ksel(a,p+1,u,k));
    else if(k-1<p) return(ksel(a,l,p,k));
    return(p);
}

int tksl(int a[],int b[],int al,int au,int bl,int bu,int k) {
    if(au==al&&bl!=bu) return(b[ksel(b,bl,bu,k)]);
    if(bu==bl&&al!=au) return(a[ksel(a,al,au,k)]);
    if(k<2) {
        if(a[al]>b[bl]) return(b[bl]);
        else return(a[al]);
    }
    int k1=ksel(a,al,au,k/2);
    int k2=ksel(b,bl,bu,k/2);
    if(a[k1]>b[k2]) return(tksl(a,b,al+k1,au,bl,bl+k2+1,k-k2));
    else if(a[k1]<b[k2]) return(tksl(a,b,al,al+k1+1,bl+k2,bu,k-k1));
}

int main(int argc,char **argv) {
    time_t t1;
    srand((unsigned)time(&t1));
    if(argc==2||argc==1) {
        int n=0,i;
        for(i=0;i<strlen(argv[1]);i++) n=n*10+((int)argv[1][i]-48);
        int *a,*b;
        a=(int*)malloc(n*sizeof(int));
        b=(int*)malloc(n*sizeof(int));
        for(i=0;i<n;i++) {
            a[i]=rand();
            b[i]=rand();
        }
        printf("List 1 :\n");
        for(i=0;i<n;i++) printf("%d\n",a[i]);
        printf("List 2 :\n");
        for(i=0;i<n;i++) printf("%d\n",b[i]);
        i=rand()%(2*n);
        printf("%d th largest element : %d",i,tksl(a,b,0,n,0,n,i));
        return 1;
    }
    int k=0,n=0,i;
    for(i=0;i<strlen(argv[1]);i++) k=k*10+((int)argv[1][i]-48);
    for(i=0;i<strlen(argv[2]);i++) n=n*10+((int)argv[2][i]-48);
    int *a,*b,t,j;
    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        t=0;
        for(j=0;j<strlen(argv[i+3]);j++) t=t*10+((int)argv[i+3][j]-48);
        a[i]=t;
    }
    for(i=0;i<n;i++) {
        t=0;
        for(j=0;j<strlen(argv[i+n+3]);j++) t=t*10+((int)argv[i+n+3][j]-48);
        b[i]=t;
    }
    printf("%d th largest element : %d",k,tksl(a,b,0,n,0,n,k));
}
