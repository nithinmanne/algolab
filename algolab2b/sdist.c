#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
    float x;
    float y;
}pt;
int xcomp(const void *p,const void *q)
{
    float l = ((pt*)p)[0].x;
    float r = ((pt*)q)[0].x;
    return (l - r);
}
int ycomp(const void *p,const void *q)
{
    float l = ((pt*)p)[0].y;
    float r = ((pt*)q)[0].y;
    return (l - r);
}
float shdist(pt*,int,pt*);
float dis(pt p1,pt p2) {
    float dist=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    return(dist);
}
int main() {
    int n,i;
    float dist;
    pt *p,*pr;
    printf("Enter number of points : ");
    scanf("%d",&n);
    p=(pt*)malloc(n*sizeof(pt));
    pr=(pt*)malloc(2*sizeof(pt));
    printf("Enter the co-ordinates of the %d points :\n",n);
    for(i=0;i<n;i++) {
        printf("%d : x : ",i+1);
        scanf("%f",&p[i].x);
        printf("%d : y : ",i+1);
        scanf("%f",&p[i].y);
    }
    qsort(p,n,sizeof(pt),xcomp);
    dist=shdist(p,n,pr);
    printf("The closest pair is (%f,%f) and (%f,%f) with distance of %f",pr[0].x,pr[0].y,pr[1].x,pr[1].y,dist);
}
float shdist(pt *p,int n,pt *pr) {
    if(n==2) { pr[0]=p[0]; pr[1]=p[1]; return(dis(pr[0],pr[1])); }
    if(n==3) {
        if(dis(p[0],p[1])<dis(p[0],p[2])&&dis(p[0],p[1])<dis(p[1],p[2])) { pr[0]=p[0]; pr[1]=p[1]; return(dis(pr[0],pr[1])); }
        else if(dis(p[0],p[1])<dis(p[0],p[2])) { pr[0]=p[1]; pr[1]=p[2]; return(dis(pr[0],pr[1])); }
        else { pr[0]=p[0]; pr[1]=p[2]; return(dis(pr[0],pr[1])); }
    }
    pt *p1,*p2,*pr1,*pr2,*ps1,*ps2;
    p1=(pt*)malloc(n/2*sizeof(pt));
    p2=(pt*)malloc((n/2+n%2)*sizeof(pt));
    ps1=(pt*)malloc(n/2*sizeof(pt));
    ps2=(pt*)malloc((n/2+n%2)*sizeof(pt));
    pr1=(pt*)malloc(2*sizeof(pt));
    pr2=(pt*)malloc(2*sizeof(pt));
    float d1,d2,d,mid,tdis;
    int i,j,p1n=0,p2n=0;
    for(i=0;i<n/2;i++) p1[i]=p[i];
    for(j=0;i<n;i++,j++) p2[j]=p[i];
    d1=shdist(p1,n/2,pr1);
    d2=shdist(p2,n/2+n%2,pr2);
    d=d1>d2?d2:d1;
    pr[0]=pr1[0];pr[1]=pr1[1];
    if(d==d2) { pr[0]=pr2[0]; pr[1]=pr2[1]; }
    mid=p2[0].x;
    for(i=n/2-1;i>=0;i--,p1n++) {
            if(mid-p1[i].x>d) break;
            ps1[p1n]=p[i];
    }
    for(i=n/2;i<n;i++,p2n++) {
            if(p2[i].x-mid>d) break;
            ps2[p2n]=p[i];
    }
    qsort(ps2,p2n,sizeof(pt),ycomp);
    for(i=0;i<p1n;i++) {
        for(j=0;j<p2n;j++) {
            if(ps2[j].y>ps1[i].y-d&&ps2[j].y<ps1[i].y+d) {
                tdis=dis(ps1[i],ps2[j]);
                if(tdis<d) {
                    d=tdis;
                    pr[0]=ps1[i];
                    pr[1]=ps2[j];
                }
            }
        }
    }
return(d);




}
