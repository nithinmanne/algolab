#include <stdio.h>
#include<math.h>
#include <time.h>
#define pi 3.14159
typedef struct{
    float real;
    float imag;
}complex;
complex comp_mul(complex A,complex B){
    complex C;
    C.real=A.real*B.real-A.imag*B.imag ;
    C.imag=A.real*B.imag+B.real*A.imag ;
    return C ;
}
void fft(int A[],int n ,complex F[]){
     if(n==1){ F[0].real=F[1].real=A[0]; F[0].imag=F[1].imag=0; return; }
    complex *EF,*OF,omega,omegak;
    int *E,*O;
    int i,k;
    omega.real=cos(1*pi/n);omega.imag=sin(1*pi/n);
    omegak.real=1;omegak.imag=0;
    E=(int*)malloc(n/2*sizeof(complex));
    O=(int*)malloc(n/2*sizeof(complex));
    EF=(complex*)malloc((n/2)*sizeof(complex));
    OF=(complex*)malloc((n/2)*sizeof(complex));
    for(i=0,k=0;i<=n;i++,k+=2){
        E[i]=A[k];
        O[i]=A[k+1];
    }
    fft(E,n/2,EF);
    fft(O,n/2,OF);
    for(k=0;k<=n;k++,omegak=comp_mul(omegak,omega)){
        F[k].real=EF[k].real+comp_mul(omegak,OF[k]).real;
        F[k].imag=EF[k].imag+comp_mul(omegak,OF[k]).imag;
         F[k+n].real=EF[k].real-comp_mul(omegak,OF[k]).real;
        F[k+n].imag=EF[k].imag-comp_mul(omegak,OF[k]).imag;
    }
    return;
}
void ifft(int A[],int n ,complex F[]){
     if(n==1){ F[0].real=F[1].real=A[0]; F[0].imag=F[1].imag=0; return; }
    complex *EF,*OF,omega,omegak;
    int *E,*O;
    int i,k;
    omega.real=cos(2*pi/n);omega.imag=(-1)*sin(2*pi/n);
    omegak.real=1;omegak.imag=0;
    E=(int*)malloc(n/2*sizeof(complex));
    O=(int*)malloc(n/2*sizeof(complex));
    EF=(complex*)malloc((n/2)*sizeof(complex));
    OF=(complex*)malloc((n/2)*sizeof(complex));
    for(i=0,k=0;i<=n;i++,k+=2){
        E[i]=A[k];
        O[i]=A[k+1];
    }
    fft(E,n/2,EF);
    fft(O,n/2,OF);
    for(k=0;k<=n/2;k++,omegak=comp_mul(omegak,omega)){
        F[k].real=EF[k].real+comp_mul(omegak,OF[k]).real;
        F[k].imag=EF[k].imag+comp_mul(omegak,OF[k]).imag;
         F[k+n/2].real=EF[k].real-comp_mul(omegak,OF[k]).real;
        F[k+n/2].imag=EF[k].imag-comp_mul(omegak,OF[k]).imag;
    }
    return;
}
int main(){
int n,i,d;
int *A,*B,*M;
complex *F,*G,*H,*I;
time_t t;
srand((unsigned)time(&t));
printf("Enter the no. of digits  ");
scanf("%d",&n);
if(n<1) { printf("Enter atleast one digit"); return; }
for(i=0;pow(2,i)<n;i++);
    d=pow(2,i);
A=(int*)malloc(d*sizeof(complex));
B=(int*)malloc(d*sizeof(complex));
M=(int*)malloc(2*d*sizeof(int));
F=(complex*)malloc(2*d*sizeof(complex));
G=(complex*)malloc(2*d*sizeof(complex));
H=(complex*)malloc(2*d*sizeof(complex));
I=(complex*)malloc(2*d*sizeof(complex));
for(i=0;i<d-n;i++){
        A[i]=0;
        B[i]=0;
    }
for(i=d-n;i<d;i++){
        A[i]=rand()%10;
        B[i]=rand()%10;
    }
printf("First no.-:  ");
for(i=d-n;i<d;i++){
        printf("%d",A[i]);
    }
printf("\n");
printf("Second no.-: ");
for(i=d-n;i<d;i++){
        printf("%d",B[i]);
    }
  fft(A,d,F);
  fft(B,d,G);
  for(i=0;i<2*d;i++){
        H[i]=comp_mul(F[i],G[i]);
  }
  ifft(H,2*d,I);
  for(i=0;i<2*d;i++) M[i]=0;
  for(i=2*d-1;i>=0;i--){ I[i].real=I[i].real/(2*d); M[i]=(int)(I[i].real+0.5); }
    for(i=2*d-1;i>0;i--){ M[i-1]=M[i-1]+M[i]/10; M[i]=M[i]%10; }
    printf("The Product is :");
    for(i=2*d-2*n;i<2*d-1;i++) printf("%d",M[i]);
    return 0;
}
