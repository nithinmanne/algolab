#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
float l;
float r;
float lh;
float rh;
}bld;

int lsrt(const void *p,const void *q) {
    float l1=((bld*)p)->l;
    float l2=((bld*)q)->l;
    return(l1-l2);
}
int magic(bld *c,int n,bld *a) {
    if(n==1) {
        a[0].l=c[0].l;
        a[0].lh=0;
        a[1].l=c[0].l;
        a[1].lh=c[0].lh;
        a[2].l=c[0].r;
        a[2].lh=c[0].rh;
        a[3].l=c[0].r;
        a[3].lh=0;
        return(4);
    }
    bld *c1,*c2,*a1,*a2,*at;
    c1=(bld*)malloc(n*sizeof(bld));
    c2=(bld*)malloc(n*sizeof(bld));
    a1=(bld*)malloc(5*n*sizeof(bld));
    a2=(bld*)malloc(5*n*sizeof(bld));
    at=(bld*)malloc(5*n*sizeof(bld));
    int n1,n2,na1,na2,nat,i,na=0;
    for(i=0,n1=0;i<n/2;i++,n1++) c1[n1]=c[i];
    for(n2=0;i<n;i++,n2++) c2[n2]=c[i];
    na1=magic(c1,n1,a1);
    na2=magic(c2,n2,a2);
    nat=merge(a1,na1,a2,na2,at);
    for(i=0;i<nat;i++) {
        if(at[i].l==a[na-1].l&&at[i].lh==a[na-1].lh) continue;
        a[na]=at[i];
        na++;
    }
    return(na);
}
int merge(bld *a1,int n1t,bld *a2,int n2t,bld *a) {
    int n1=0,n2=0,nt=0;
    float l1=0,pl1=0,m1=0,pm1=0,h1=0,ph1=0;
    float l2=0,pl2=0,m2=0,pm2=0,h2=0,ph2=0;
    while(n1<n1t||n2<n2t) {
        if(n1==n1t) { a[nt]=a2[n2]; nt++; n2++; continue; }
        if(n2==n2t) { a[nt]=a1[n1]; nt++; n1++; continue; }
        if((a1[n1].l==a2[n2].l&&a1[n1].lh>a2[n2].lh)||(a1[n1].l<a2[n2].l)) {
            l1=a1[n1].l; h1=a1[n1].lh;
            if(n1+1==n1t) m1=0;
            else if(a1[n1+1].l==l1) m1=-1;
            else m1=(a1[n1+1].lh-h1)/(a1[n1+1].l-l1);
            if(h1<h2+m2*(l1-l2)) { n1++; pl1=l1; pm1=m1; ph1=h1; continue; }
            if(pm1==m2) a[nt].l=pl1;
            else a[nt].l=(h2-ph1-m2*l2+pm1*pl1)/(pm1-m2);
            a[nt].lh=ph1+pm1*(a[nt].l-pl1);
            nt++;
            a[nt].l=a1[n1].l;
            a[nt].lh=a1[n1].lh;
            nt++; n1++;
            pl1=l1; pm1=m1; ph1=h1;
            if(a1[n1].l==l1) ph1=h1=a1[n1].lh;
        }
        else if((a2[n2].l==a1[n1].l&&a2[n2].lh>=a1[n1].lh)||(a2[n2].l<a1[n1].l)) {
            l2=a2[n2].l; h2=a2[n2].lh;
            if(n2+1==n2t) m2=0;
            else if(a2[n2+1].l==l2) m2=-1;
            else m2=(a2[n2+1].lh-h2)/(a2[n2+1].l-l2);
            if(h2<h1+m1*(l2-l1)) { n2++; pl2=l2; pm2=m2; ph2=h2; continue; }
            if(m1==-1)
            else if(pm2==m1) a[nt].l=pl2;
            else a[nt].l=(h1-ph2-m1*l1+pm2*pl2)/(pm2-m1);
            a[nt].lh=ph2+pm2*(a[nt].l-pl2);
                      nt++;
            a[nt].l=a2[n2].l;
            a[nt].lh=a2[n2].lh;
            nt++; n2++;
            pl2=l2; pm2=m2; ph2=h2;
            if(a2[n2].l==l2) ph2=h2=a2[n2].lh;
        }
    }
    return(nt);
}
int main() {
    int n,i,nan;
    float ml,mr,mh;
    bld *city,*ans;
    printf("Enter min value of  left : ");
    scanf("%f",&ml);
    printf("Enter max value of  right : ");
    scanf("%f",&mr);
    printf("Enter max value of  height : ");
    scanf("%f",&mh);
    printf("Enter value of  n : ");
    scanf("%d",&n);
    if(mr<ml||mh<1||n<1) { printf("Invalid Input!\n"); return(-1); }
    city=(bld*)malloc(n*sizeof(bld));
    ans=(bld*)malloc(5*n*sizeof(bld));
    time_t t;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++) {
        city[i].l=ml+rand()%((int)(mr-ml));
        if(mr-city[i].l!=1) city[i].r=1+city[i].l+rand()%((int)(mr-city[i].l-1));
        else city[i].r=city[i].l+1;
        city[i].lh=rand()%((int)mh);
        city[i].rh=rand()%((int)mh);
    }
    qsort(city,n,sizeof(bld),lsrt);
    printf("The input is (left,right,left height,right height)\n");
    for(i=0;i<n;i++) printf("(%f,%f,%f,%f)\n",city[i].l,city[i].r,city[i].lh,city[i].rh);
    nan=magic(city,n,ans);
    printf("The output is\n");
    for(i=0;i<nan;i++) printf("(%f,%f)\n",ans[i].l,ans[i].lh);
    return(1);
}
