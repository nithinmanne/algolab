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
int magic(bld*,int,bld*);
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
int magic(bld *c,int n,bld *a) {
    if(n==1) {
        a[0].l=c[0].l;
        a[0].lh=0;
        a[0].rh=c[0].lh;
        a[1].l=c[0].l;
        a[1].lh=c[0].lh;
        a[1].rh=c[0].rh;
        a[2].l=c[0].r;
        a[2].lh=c[0].rh;
        a[2].rh=0;
        a[3].l=c[0].r;
        a[3].lh=a[3].rh=0;
        return(4);
    }
    bld *c1,*c2,*a1,*a2,*at;
    c1=(bld*)malloc(n*sizeof(bld));
    c2=(bld*)malloc(n*sizeof(bld));
    a1=(bld*)malloc(5*n*sizeof(bld));
    a2=(bld*)malloc(5*n*sizeof(bld));
    at=(bld*)malloc(5*n*sizeof(bld));
    int n1,n2,na1,na2,i,na=1,na1t=0,na2t=0,nat=0;
    float t1l=0,t1r=0,t1=0,t1m=0,t2l=0,t2r=0,t2m=0,t2=0;
    for(i=0,n1=0;i<n/2;i++,n1++) c1[n1]=c[i];
    for(n2=0;i<n;i++,n2++) c2[n2]=c[i];
    na1=magic(c1,n1,a1);
    na2=magic(c2,n2,a2);
    for(i=0;na1t<na1||na2t<na2;i++) {
        if(na1t==na1) { at[nat]=a2[na2t]; na2t++; nat++; continue; }
        if(na2t==na2) { at[nat]=a1[na1t]; na1t++; nat++; continue; }
        if(a1[na1t].l==a2[na2t].l) {
            if(a1[na1t].lh<a2[na2t].lh) {
                if(na1t==0&&t2!=0) {na1t++;continue;}
                else if(na1t==0) {
                    at[nat].l=0;
                    at[nat].lh=0;
                    nat++;
                }
                if(a2[na1t].lh<t2+t2m*(a1[na1t].l-t2l)) {na1t++;continue;}
                at[nat].l=(t2-t1-t2m*t2l+t1m*t1l)/(t1m-t2m);
                at[nat].lh=t1+t1m*(at[nat].l-t1l);
                nat++;
                t1=a1[na1t].lh;
                t1l=a1[na1t].l;
                if(na1t==na1-1) { t1=0; t1m=0; }
                else if(a1[na1t].l==a1[na1t+1].l) { t1=a1[na1t+1].lh; t1m=0; }
                else t1m=(a1[na1t].lh-a1[na1t+1].lh)/(a1[na1t].l-a1[na1t+1].l);
                at[nat]=a1[na1t];
                na1t++;
                nat++;
                t2=a2[na2t].lh;
                t2l=a2[na2t].l;
                if(na2t==na2-1) { t1m=0; }
                else if(a2[na2t].l==a2[na2t+1].l) { t2=a2[na2t+1].lh; t2m=0; }
                else t2m=(a2[na2t].lh-a2[na2t+1].lh)/(a2[na2t].l-a2[na2t+1].l);
                na2t++;
            }
            else {
                if(na2t==0&&t1!=0) {na2t++;continue;}
                else if(na1t==0) {
                    at[nat].l=0;
                    at[nat].lh=0;
                    nat++;
                }
                if(a1[na2t].lh<t1+t1m*(a2[na2t].l-t1l)) {na2t++;continue;}
                at[nat].l=(t1-t2-t1m*t1l+t2m*t2l)/(t2m-t1m);
                at[nat].lh=t2+t2m*(at[nat].l-t2l);
                nat++;
                t2=a2[na2t].lh;
                t2l=a2[na2t].l;
                if(na2t==na2-1) { t2=0; t2m=0; }
                else if(a2[na2t].l==a2[na2t+1].l) { t2=a2[na2t+1].lh; t2m=0; }
                else t2m=(a2[na2t].lh-a2[na2t+1].lh)/(a2[na2t].l-a2[na2t+1].l);
                at[nat]=a2[na2t];
                na2t++;
                nat++;
                t1=a1[na1t].lh;
                t1l=a1[na1t].l;
                if(na1t==na1-1) { t1m=0; }
                else if(a1[na1t].l==a1[na1t+1].l) { t1=a1[na1t+1].lh; t2m=0; }
                else t1m=(a1[na1t].lh-a1[na1t+1].lh)/(a1[na1t].l-a1[na1t+1].l);
                na1t++;
            }
        }
        else if(a1[na1t].l<a2[na2t].l) {
            if(na1t==0&&t2!=0) {na1t++;continue;}
            else if(na1t==0) {
                at[nat].l=0;
                at[nat].lh=0;
                nat++;
            }
            if(a2[na1t].lh<t2+t2m*(a1[na1t].l-t2l)) {na1t++;continue;}
            at[nat].l=(t2-t1-t2m*t2l+t1m*t1l)/(t1m-t2m);
            at[nat].lh=t1+t1m*(at[nat].l-t1l);
            nat++;
            t1=a1[na1t].lh;
            t1l=a1[na1t].l;
            if(na1t==na1-1) { t1=0; t1m=0; }
            else if(a1[na1t].l==a1[na1t+1].l) { t1=a1[na1t+1].lh; t1m=0; }
            else t1m=(a1[na1t].lh-a1[na1t+1].lh)/(a1[na1t].l-a1[na1t+1].l);
            at[nat]=a1[na1t];
            na1t++;
            nat++;
        }
        else {
            if(na2t==0&&t1!=0) {na2t++;continue;}
            else if(na1t==0) {
                at[nat].l=0;
                at[nat].lh=0;
                nat++;
            }
            if(a1[na2t].lh<t1+t1m*(a2[na2t].l-t1l)) {na2t++;continue;}
            at[nat].l=(t1-t2-t1m*t1l+t2m*t2l)/(t2m-t1m);
            at[nat].lh=t2+t2m*(at[nat].l-t2l);
            nat++;
            t2=a2[na2t].lh;
            t2l=a2[na2t].l;
            if(na2t==na2-1) { t2=0; t2m=0; }
            else if(a2[na2t].l==a2[na2t+1].l) { t2=a2[na2t+1].lh; t2m=0; }
            else t2m=(a2[na2t].lh-a2[na2t+1].lh)/(a2[na2t].l-a2[na2t+1].l);
            at[nat]=a2[na2t];
            na2t++;
            nat++;
        }
    }
    a[0]=at[0];
    for(i=1;i<nat;i++) {
        //if(at[i].lh==a[na-1].lh) continue;
        a[na]=at[i];
        na++;
    }
    return(na);
}
