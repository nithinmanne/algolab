#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
    float l;
    float r;
    float lh;
    float rh;
}bld;
typedef struct {
    float lx;
    float ly;
    float rx;
    float ry;
}lin;
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
lin intr(lin a,lin b) {
    lin pt;
    float x,y,m1,m2;
    if(a.lx==a.rx&&b.lx==b.rx) {
        if(a.lx==b.lx) { pt.lx=a.lx; pt.ly=a.ly>b.ly?b.ly:a.ly; return(pt); }
        pt.lx=-1;pt.ly=0;return(pt);
    }
    if(a.lx==a.rx) {
        y=b.ly+((b.ry-b.ly)/(b.rx-b.lx))*(a.lx-b.lx);
        if(y>a.ry) { pt.lx=-1;pt.ly=0;return(pt); }
        pt.lx=a.lx;pt.ly=y;return(pt);
    }
    if(b.lx==b.rx) {
        y=a.ly+((a.ry-a.ly)/(a.rx-a.lx))*(b.rx-a.lx);
        if(y>b.ry) { pt.lx=-1;pt.ly=0;return(pt);}
        pt.lx=b.lx;pt.ly=y;return(pt);
    }
    m1=(a.ry-a.ly)/(a.rx-a.lx);
    m2=(b.ry-b.ly)/(b.rx-b.lx);
    x=(m2*b.lx-m1*a.lx+a.ly-b.ly)/(m2-m1);
    y=(m1*m2*(b.lx-a.lx)+a.ly*m2-b.ly*m1)/(m2-m1);
    if(x>a.rx||x<a.lx||x>b.rx||x<b.lx) { pt.lx=-1;pt.ly=0;return(pt); }
    pt.lx=x;pt.ly=y;return(pt);
}
float eqy(lin a,float x) {
    if(a.lx==a.rx) return(a.ry);
    float y;
    y=a.ly+((a.ry-a.ly)/(a.rx-a.lx))*(x-a.lx);
    return(y);
}
int merge(bld *a1,int n1t,bld *a2,int n2t,bld *a) {
    int n1=0,n2=0,nt=0;
    lin la,lb,lc;
    la.lx=la.ly=la.rx=la.ry=0;
    lb.lx=lb.ly=lb.rx=lb.ry=0;
    while(n1<n1t||n2<n2t) {
        if(n1==n1t) { a[nt]=a2[n2]; nt++; n2++; continue; }
        if(n2==n2t) { a[nt]=a1[n1]; nt++; n1++; continue; }
        if((a1[n1].l==a2[n2].l&&a1[n1].lh>a2[n2].lh)||(a1[n1].l<a2[n2].l)) {
            la.lx=a1[n1].l;la.ly=a1[n1].lh;
            if(n1==n1t-1) la.rx=la.ry=0;
            else la.rx=a1[n1+1].l;la.ry=a1[n1+1].lh;
            lc=intr(la,lb);
            if(la.ly>=eqy(lb,la.lx)) { a[nt]=a1[n1];nt++; }
            if(lc.lx!=-1) { a[nt].l=lc.lx;a[nt].lh=lc.ly;nt++; }
            n1++;
        }
        else if((a2[n2].l==a1[n1].l&&a2[n2].lh>=a1[n1].lh)||(a2[n2].l<a1[n1].l)) {
            lb.lx=a2[n2].l;lb.ly=a2[n2].lh;
            if(n2==n2t-1) lb.rx=lb.ry=0;
            else lb.rx=a2[n2+1].l;lb.ry=a2[n2+1].lh;
            lc=intr(la,lb);
            if(lb.ly>=eqy(la,lb.lx)) { a[nt]=a2[n2];nt++; }
            if(lc.lx!=-1) { a[nt].l=lc.lx;a[nt].lh=lc.ly;nt++; }
            n2++;
        }
    }
    return(nt);
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
    a1=(bld*)malloc(500*n*sizeof(bld));
    a2=(bld*)malloc(500*n*sizeof(bld));
    at=(bld*)malloc(500*n*sizeof(bld));
    int n1,n2,na1,na2,nat,i,na=0;
    for(i=0,n1=0;i<n/2;i++,n1++) c1[n1]=c[i];
    for(n2=0;i<n;i++,n2++) c2[n2]=c[i];
    na1=magic(c1,n1,a1);
    na2=magic(c2,n2,a2);
    nat=merge(a1,na1,a2,na2,at);
    for(i=0;i<nat;i++) {
        if(at[i].l==a[na-1].l&&at[i].lh==a[na-1].lh) continue;
        if((at[i].l<=0&&at[i].lh<=0)&&i) continue;
        a[na]=at[i];
        na++;
    }
    return(na);
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
    if(mr<ml||mh<1||n<1||ml<0) { printf("Invalid Input!\n"); return(-1); }
    city=(bld*)malloc(n*sizeof(bld));
    ans=(bld*)malloc(500*n*sizeof(bld));
    time_t t;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++) {
        city[i].l=ml+rand()%((int)(mr-ml));
        if(mr-city[i].l!=1) city[i].r=1+city[i].l+rand()%((int)(mr-city[i].l-1));
        else city[i].r=city[i].l+1;
        city[i].lh=rand()%((int)mh);
        city[i].rh=rand()%((int)mh);
    }
    msort(city,n);
    printf("The input is (left,right,left height,right height)\n");
    for(i=0;i<n;i++) printf("(%f,%f,%f,%f)\n",city[i].l,city[i].r,city[i].lh,city[i].rh);
    nan=magic(city,n,ans);
    printf("The output is\n");
    for(i=0;i<nan;i++) printf("(%f,%f)\n",ans[i].l,ans[i].lh);
    return(1);
}
