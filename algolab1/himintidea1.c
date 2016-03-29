#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define pi 3.14159265
typedef struct {
    double real;
    double imag;
}complex;
complex comp_mul(complex A,complex B) {
    complex C;
    C.real=A.real*B.real-A.imag*B.imag;
    C.imag=A.real*B.imag+A.imag*B.real;
    return C;
}
void fft(int A[],int n,complex F[]) {
    int i,k;
    int *E,*O;
    complex *EF,*OF,omegak,omega,cmul;
    EF=(complex*)malloc(n*sizeof(complex));
    OF=(complex*)malloc(n*sizeof(complex));
    if(n==1){ F[0].real=F[1].real=A[0]; F[0].imag=F[1].imag=0; return; }
    E=(int*)malloc(n*sizeof(int));
    O=(int*)malloc(n*sizeof(int));
    omega.real=cos(1.0*pi/n);omega.imag=sin(1.0*pi/n);
    omegak.real=1;omegak.imag=0;
    for(i=k=0;k<n;i++,k+=2){ E[i]=A[k]; O[i]=A[k+1]; }
    fft(E,n/2,EF);
    fft(O,n/2,OF);
        for(k=0;k<n;k++) {
            cmul=comp_mul(omegak,OF[k]);
            F[k].real=EF[k].real+cmul.real;
            F[k].imag=EF[k].imag+cmul.imag;
            F[k+n].real=EF[k].real-cmul.real;
            F[k+n].imag=EF[k].imag-cmul.imag;
            omegak=comp_mul(omegak,omega);
        }
        return;
}
void ifft (complex A[],int n,complex F[]) {
    int i,k;
    complex omegak,omega,*EF,*OF,*E,*O,cmul;
    EF=(complex*)malloc(n/2*sizeof(complex));
    OF=(complex*)malloc(n/2*sizeof(complex));
    E=(complex*)malloc(n/2*sizeof(complex));
    O=(complex*)malloc(n/2*sizeof(complex));
    if(n==1){ F[0].real=A[0].real; F[0].imag=A[0].imag; return; }
    for(i=k=0;i<n;i++,i+=2){ E[i].real=A[k].real; E[i].imag=A[k].imag; O[i].real=A[k+1].real; O[i].imag=A[k+1].imag; }
    omega.real=cos(2*pi/n); omega.imag=-1*sin(2*pi/n);
    omegak.real=1; omegak.imag=0;
    ifft(E,n/2,EF);
    ifft(O,n/2,OF);
    for(k=0;k<n/2;k++) {
        cmul=comp_mul(omegak,OF[k]);
        F[k].real=EF[k].real+cmul.real;
        F[k].imag=EF[k].imag+cmul.imag;
        F[k+n/2].real=EF[k].real-cmul.real;
        F[k+n/2].imag=EF[k].imag-cmul.imag;
        omegak=comp_mul(omegak,omega);
    }
    return;
}


int main() {
    int i,d,temp=0,n;
    int *a,*b,*c;
    complex *af,*bf,*cf,*cif;
    printf("Enter the number of digits : ");
    scanf("%d",&n);
    if(n<1) { printf("Well, that makes no sense!"); return; }
    for(i=0;pow(2,i)<n;i++) {}
    d=pow(2,i);
    a=(int*)malloc(d*sizeof(int));
    b=(int*)malloc(d*sizeof(int));
    c=(int*)malloc(2*d*sizeof(int));
    af=(complex*)malloc(2*d*sizeof(complex));
    bf=(complex*)malloc(2*d*sizeof(complex));
    cf=(complex*)malloc(2*d*sizeof(complex));
    cif=(complex*)malloc(2*d*sizeof(complex));
    for(i=0;i<d-n;i++){
        a[i]=0;
        b[i]=0;
    }
    time_t t;
    srand((unsigned)time(&t));
    for(i=d-n;i<d;i++){
        a[i]=rand()%10;
        b[i]=rand()%10;
    }
    printf("The first number is : ");
        for(i=d-n;i<d;i++){
        printf("%d",a[i]);
    }
    printf("\nThe second number is : ");
    for(i=d-n;i<d;i++){
        printf("%d",b[i]);
    }
    printf("\n");
    fft(a,d,af);
    fft(b,d,bf);
    for(i=0;i<2*d;i++){ cf[i]=comp_mul(af[i],bf[i]); }
    ifft(cf,2*d,cif);
    for(i=0;i<2*d;i++) c[i]=0;
    for(i=2*d-1;i>=0;i--){ cif[i].real=cif[i].real/(2*d); c[i]=(int)(cif[i].real+0.5); }
    for(i=2*d-1;i>0;i--){ c[i-1]=c[i-1]+c[i]/10; c[i]=c[i]%10; }
    printf("The multiplication is :  ");
    for(i=2*d-2*n;i<2*d-1;i++) printf("%d",c[i]);
    return 0;
}
