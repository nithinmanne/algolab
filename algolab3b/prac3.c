#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct {
float l,r,y1,y2;}bld;

typedef struct {
float x,y,slopef,slopeb;}point;


void merge(bld *A,bld *B,bld *C,int m,int n){
int i=0,j=0,k=0;
while(i<m&&j<n){
    if(A[i].l<B[j].l || (A[i].l==B[j].l && A[i].y1<B[j].y1) ||(A[i].l==B[j].l && A[i].y1==B[j].y1 &&A[i].r<B[j].r))
        C[k++]=A[i++];
    else C[k++]=B[j++];
}
while(i<m)C[k++]=A[i++];
while(j<n)C[k++]=B[j++];
}
void mergesort(bld *A,int n){
int i,j;
bld *B;
if(n<=1)return;
B=(bld*)malloc(n*sizeof(bld));
i=n/2;
mergesort(A,i);
mergesort(A+i,n-i);
merge(A,A+i,B,i,n-i);
for(j=0;j<n;j++)A[j]=B[j];
free(B);
return ;
}


void skyline (bld *b,int n,point *A,int *count){
int i,j,x=0,count1,count2,count_a,temp;
point *A1,*A2;
if(n<1) return;
printf("^^^^^%d^^^^^^^\n",n);
if(n==1){
A[0].x=b[0].l;A[0].y=0;A[0].slopeb=0;A[0].slopef=-1;
A[1].x=b[0].l;A[1].y=b[0].y1;A[1].slopeb=-1;A[1].slopef=(b[0].y2-b[0].y1)/(b[0].r-b[0].l);
A[2].x=b[0].r;A[2].y=b[0].y2;A[2].slopeb=(b[0].y2-b[0].y1)/(b[0].r-b[0].l);A[2].slopef=-1;
A[3].x=b[0].r;A[3].y=0;A[3].slopeb=-1;A[3].slopef=0;
*count=4;
//for(i=0;i<*count;i++){
 //printf("_________________%f,%f,forward--%f,backward%f\n",A[i].x,A[i].y,A[i].slopef,A[i].slopeb);
//}
printf("ABC--%d\n",*count);
return ;
}
temp=n/2;
A1=(point*)malloc(5*temp*sizeof(point));
temp=n-n/2;
A2=(point*)malloc(5*temp*sizeof(point));
skyline(b,n/2,A1,&count1);skyline(&b[n/2],n-n/2,A2,&count2);
for(i=0;i<count1;i++){
 printf("_________________%f,%f,%f,%f\n",A1[i].x,A1[i].y,A1[i].slopef,A1[i].slopeb);
}
printf("\n\n\n\n");
for(i=0;i<count2;i++){
 printf("_________________%f,%f,%f,%f\n",A2[i].x,A2[i].y,A2[i].slopef,A2[i].slopeb);
}
skymerge(A,A1,A2,count1,count2,&count_a);
for(i=0;i<count_a;i++){
 printf("+++++++++++++++++++%f,%f\n",A[i].x,A[i].y);
}
*count=count_a;
free(A1);free(A2);
return ;
}
float calx(point A1,point A2){
    float x,m1,m2,l,r,y1,y2;
    m1=A1.slopeb;l=A1.x;y1=A1.y;
    m2=A2.slopeb;r=A2.x;y2=A2.y;
    if(m1!=-1 && m2!=-1){
            x=(y2-y1+m1*l-m2*r)/(m1-m2);
        return x;
    }
    if(m1==-1)return l;
    if(m2==-1)return r;
}
float caly(point A1,point A2){
    float y,m1,m2,l,r,y1,y2;
    m1=A1.slopeb;l=A1.x;y1=A1.y;
    m2=A2.slopeb;r=A2.x;y2=A2.y;
    if(m1!=-1 && m2!=-1){
            y=(m1*y2-m2*y1+m1*m2*(l-r))/(m1-m2);
        return y;
    }
    if(m1==-1)return (y2+m2*(l-r));
    if(m2==-1)return (y1+m1*(r-l));
}

void skymerge(point *B,point *A1,point *A2,int count1,int count2,int *count){
       int i=0,j=0;
   float h1,h2;
   point *A;
   A=(point*)malloc(5*(count1+count2)*sizeof(point));
   A[0]=A1[0];A[1]=A1[1];*count=2;
   h1=A1[1].y;h2=0;i=2;j=0;
// printf("-----%f------%f-------\n",h1,h2);
   while(i<count1 &&j<count2){
    if(A1[i].x<A2[j].x){h1=A1[i].y;printf("-------%d-------%d\n",i,j);printf("-----%f------%f-------\n",h1,h2);
        if( h1>=h2+(A2[j].slopeb*(A1[i].x-A2[j-1].x)) && A1[i-1].y<A[*count-1].y){A[*count].x=calx(A2[j],A1[i]);A[*count].y=caly(A1[i],A2[j]);
        A[*count].slopef=A1[i].slopeb;A[*count].slopeb=A2[j-1].slopef;
         printf("---------%fa----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
         A[*count]=A1[i++];
          printf("---------%fb----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;}
         else if (h1>=h2+A2[j].slopeb*(A1[i].x-A2[j-1].x)&& A1[i-1].y>=A[*count-1].y){
            A[*count]=A1[i++];
             printf("---------%fc----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
         }
         else if(h1<h2+A2[j].slopeb*(A1[i].x-A2[j-1].x) && A1[i-1].y<A[*count-1].y){
          A[*count].x=A1[i].x;A[*count].y=h2+A2[j-1].slopef*(A1[i].x-A2[j-1].x);A[*count].slopef=A2[j].slopeb;A[*count].slopeb=A2[j-1].slopef;
           printf("---------%fd----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;i++;
         }
         else if(h1<h2+A2[j].slopeb*(A1[i].x-A2[j-1].x) && A1[i-1].y>=A[*count-1].y){A[*count].x=calx(A1[i],A2[j]);A[*count].y=caly(A1[i],A2[j]);A[*count].slopef=A2[j].slopeb;
         A[*count].slopeb=A1[i-1].slopef;
          printf("---------%fe----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
             A[*count].x=A1[i].x;A[*count].y=h2+A2[j-1].slopef*(A1[i].x-A2[j-1].x);A[*count].slopef=A2[j].slopeb;A[*count].slopeb=A2[j-1].slopef;
              printf("---------%ff----%f-------%f--------%f ---------%d ####%f####%f##%f###%f\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1,h1,A2[j-1].slopef,A1[i].x,A2[j-1].x);*count+=1;i++;
         }
    }
    else{ h2=A2[j].y;
    //printf("-----%f------%f-------\n",h1,h2);
        if(h2>=h1+A1[i].slopeb*(A2[j].x-A1[i-1].x) && A2[j-1].y<A[*count-1].y){A[*count].x=calx(A1[i],A2[j]);A[*count].y=caly(A1[i],A2[j]);A[*count].slopef=A2[j].slopeb;
        A[*count].slopeb=A1[i-1].slopef;
         printf("---------%fg----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
            A[*count]=A2[j]; printf("---------%fh----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A[*count].slopeb,*count+1);*count+=1;j++;
            }
            else if (h2>=h1+A1[i].slopeb*(A2[j].x-A1[i-1].x)  && A2[j-1].y>=A[*count-1].y){
               A[*count]=A2[j++]; printf("---------%fi----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
            }
            else if (h2<h1+A1[i].slopeb*(A2[j].x-A1[i-1].x) && (A2[j-1].y<A[*count-1].y || j==0)){
                A[*count].x=A2[j].x;A[*count].y=h1+A1[i-1].slopef*(A2[j].x-A1[i-1].x);A[*count].slopef=A1[i].slopeb;A[*count].slopeb=A1[i-1].slopef;
                printf("---------%fj----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);
                *count+=1;j++;

            }
            else if(h2<h1+A1[i].slopeb*(A2[j].x-A1[i-1].x) && A2[j-1].y>=A[*count-1].y){A[*count].x=calx(A1[i],A2[j]);A[*count].y=caly(A1[i],A2[j]);
            A[*count].slopef=A1[i].slopeb;A[*count].slopeb=A2[j-1].slopef;
             printf("---------%fk----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;
              A[*count].x=A2[j].x;A[*count].y=h1+A1[i-1].slopef*(A2[j].x-A1[i-1].x);A[*count].slopef=A1[i].slopeb;A[*count].slopeb=A1[i-1].slopef;
               printf("---------%fl----%f-------%f--------%f ---------%d\n",A[*count].x,A[*count].y,A[*count].slopef,A1[*count].slopeb,*count+1);*count+=1;j++;
            }
    }
   // printf("####%d######\n",*count);
    //printf("-------%d-------%d\n",i,j);
   }
     while (i<count1){
        A[*count]=A1[i++];*count+=1;
    }
       while (j<count2){
        A[*count]=A2[j++];*count+=1;
    }
       B[0]=A[0];
    for(i=1,j=1;i<*count-1;i++){
     if(!( (A[i].slopef==A[i-1].slopef) )) {
        B[j++]=A[i];
     }
    }
    B[j]=A[*count-1];
    for(i=0;i<j+1;i++)printf("%f---+++++++--%f_____%f____%f \n",B[i].x,B[i].y,B[i].slopef,B[i].slopeb);
    *count=j+1;
    return;

}
int main(){
int i,n,temp,count;
time_t t;
srand((unsigned)time(&t));
bld *b;
point *p;
printf("Enter the no:of bldings to be considered ");
scanf("%d",&n);
printf("NOTE THAT THE bldINGS ARE IN A SPAN OF 0 TO 1000m ALONG X-Axis\n");
b= (bld*)malloc(n*sizeof(bld));
p= (point*)malloc(5*n*sizeof(point));
for(i=0;i<n;i++){
b[i].l=(rand()%100000)/100.0;
b[i].r=(rand()%100000)/100.0;
if(b[i].l>b[i].r){
temp=b[i].l;b[i].l=b[i].r;b[i].r=temp;}
b[i].y1=(rand()%5000)/100.0;
b[i].y2=(rand()%5000)/100.0;}
printf("the sizes of bldings are:\n");
for(i=0;i<n;i++){
printf("The position of blding%d is : left edge %f right edge %f Y1 %f  Y2 %f\n",i+1,b[i].l,b[i].r,b[i].y1,b[i].y2);
}
mergesort(b,n);
printf("-------------------------------------------------------------------------------\n");
for(i=0;i<n;i++){
printf("The position of blding%d is : left edge %f right edge %f Y1 %f  Y2 %f\n",i+1,b[i].l,b[i].r,b[i].y1,b[i].y2);
}
skyline(b,n,p,&count);
printf("-------------------------------------------------------------------------------\n");
printf("the skyline points are:\n");
for(i=0;i<count;i++){
 printf("%f,%f\n",p[i].x,p[i].y);
}
return 0;}
