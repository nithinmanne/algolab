#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct{
    float x;
    float y;
}pnt;
float dist(pnt A,pnt B){
    float c;
   c=sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
   return c;
}
int xcomp(const void *p,const void *q)
{
    float l = ((pnt*)p)->x;
    float r = ((pnt*)q)->x;
    return (l - r);
}
int ycomp(const void *p, const void *q)
{
    float l = ((pnt*)p)->y;
    float r = ((pnt*)q)->y;
    return (l - r);
}
float shdist(pnt A[],int n,int l,int m){

    pnt C[n];
    float d1,d2,d=1000;
     int i,k,j,h=(l+m)/2;
    if(n<=3){
       for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        if(dist(A[i],A[j])<d)
        d=dist(A[i],A[j]);
  return d ;
}

       qsort(A,n,sizeof(pnt),xcomp);

         d1=shdist(C,n/2,l,h);
          d2=shdist(C,n-h,m-h,m);
          if(d1<d2)
            d=d1;
           else
            d=d2;
         for (i=h,k=0;(A[h].x-A[i].x)<=d;i--,k++){
            C[k].x= A[i].x;C[k].y= A[i].y;
            }
        for(i=h+1;(A[i].x-A[h].x)<=d;i++,k++){
            C[k]=A[i];C[k].y= A[i].y;
        }
       qsort(C,k,sizeof(pnt),ycomp);
       for(i=0;i<k;i++){
       for(j=i+1;(j<i+8)&&(j<k);j++){
          if(dist(C[i],C[j])<d)
            d=dist(C[i],C[j]);
       }
    }
    return d;
}
int main() {
    int i,n;
    float c;
    pnt *a;
    printf("Enter value of n\n");
    scanf("%d",&n);
    a=(pnt*)malloc(n*sizeof(pnt));
    for(i=0;i<n;i++){
        printf("Enter x-pntinate %d-: ",i+1);
        scanf("%f",&a[i].x);
         printf("Enter y-pntinate %d-: ",i+1);
        scanf("%f",&a[i].y);
    }

    c=shdist(a,n,0,n);
     printf("min distance -:   %f",c);
   return 0;
}
