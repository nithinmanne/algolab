#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
int l;
int r;
int h;
}bld;
void msort(bld *a,int n) {
    if(n==1) return;
    bld *b,*c,*d;
    b=(bld*)malloc(n*sizeof(bld));
    c=(bld*)malloc(n*sizeof(bld));
    d=(bld*)malloc(n*sizeof(bld));
    int n1,n2,i;
    for(i=0,n1=0;i<n/2;i++,n1++) b[n1]=a[i];
    for(n2=0;i<n;i++,n2++) c[n2]=a[i];
    msort(b,n1);
    msort(c,n2);
    int n1t=0,n2t=0,nt=0;
    while(n1t<n1||n2t<n2) {
        if(n1t==n1) { d[nt]=c[n2t];n2t++;nt++;continue; }
        if(n2t==n2) { d[nt]=b[n1t];n1t++;nt++;continue; }
        if(b[n1t].l<c[n2t].l) { d[nt]=b[n1t];n1t++;nt++; }
        else { d[nt]=c[n2t];n2t++;nt++; }
    }
}
int magic(bld*,int,bld*);
int main() {
    int n,ml,mr,mh,i,nan;
    bld *city,*ans;
    printf("Enter min value of  left : ");
    scanf("%d",&ml);
    printf("Enter max value of  right : ");
    scanf("%d",&mr);
    printf("Enter max value of  height : ");
    scanf("%d",&mh);
    printf("Enter value of  n : ");
    scanf("%d",&n);
    if(mr<ml||mh<1||n<1) { printf("Invalid Input!\n"); return(-1); }
    city=(bld*)malloc(n*sizeof(bld));
    ans=(bld*)malloc(2*n*sizeof(bld));
    time_t t;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++) {
        city[i].l=ml+rand()%(mr-ml);
        if(mr-city[i].l!=1) city[i].r=1+city[i].l+rand()%(mr-city[i].l-1);
        else city[i].r=city[i].l+1;
        city[i].h=1+rand()%(mh-1);
    }
    msort(city,n);
    printf("The input is\n");
    for(i=0;i<n;i++) printf("(%d,%d,%d)\n",city[i].l,city[i].r,city[i].h);
    nan=magic(city,n,ans);
    printf("The output is\n");
    for(i=0;i<nan;i++) printf("(%d,%d)\n",ans[i].l,ans[i].h);
    return(1);
}
int magic(bld *c,int n,bld *a) {
    if(n==1) {
        a[0].l=c[0].l;
        a[0].h=c[0].h;
        a[1].l=c[0].r;
        a[1].h=0;
        return(2);
    }
    bld *c1,*c2,*a1,*a2,*at;
    c1=(bld*)malloc(n*sizeof(bld));
    c2=(bld*)malloc(n*sizeof(bld));
    a1=(bld*)malloc(2*n*sizeof(bld));
    a2=(bld*)malloc(2*n*sizeof(bld));
    at=(bld*)malloc(2*n*sizeof(bld));
    int n1,n2,na1,na2,i,t=0,t1=0,t2=0,na=1,na1t=0,na2t=0,nat=0;
    for(i=0,n1=0;i<n/2;i++,n1++) c1[n1]=c[i];
    for(n2=0;i<n;i++,n2++) c2[n2]=c[i];
    na1=magic(c1,n1,a1);
    na2=magic(c2,n2,a2);
    for(i=0;i<na1+na2;i++) {
        if(na1t==na1) { at[nat]=a2[na2t]; na2t++; nat++; continue; }
        if(na2t==na2) { at[nat]=a1[na1t]; na1t++; nat++; continue; }
        if(a1[na1t].l==a2[na2t].l) {
            if(a1[na1t].h<a2[na2t].h) {
                t1=a1[na1t].h;
                if(a1[na1t].h<t2) a1[na1t].h=t2;
                at[nat]=a1[na1t];
                na1t++;
                nat++;
            }
            else {
                t2=a1[na2t].h;
                if(a2[na2t].h<t1) a2[na2t].h=t1;
                at[nat]=a2[na2t];
                na2t++;
                nat++;
            }
        }
        else if(a1[na1t].l<a2[na2t].l) {
            t1=a1[na1t].h;
            if(a1[na1t].h<t2) a1[na1t].h=t2;
            at[nat]=a1[na1t];
            na1t++;
            nat++;
        }
        else {
            t2=a1[na2t].h;
            if(a2[na2t].h<t1) a2[na2t].h=t1;
            at[nat]=a2[na2t];
            na2t++;
            nat++;
        }
    }
    a[0]=at[0];
    for(i=1;i<nat;i++) {
        if(at[i].h==a[na-1].h) continue;
        if(at[i].l==a[na-1].l) na--;
        a[na]=at[i];
        na++;
    }
    return(na);
}
