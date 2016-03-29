#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define pi 3.14159
typedef struct {
    float re;
    float im;
}cmplx;
void mul(int*,int*,int*,int);
void fft(cmplx*,int,cmplx*);
cmplx cmul(cmplx,cmplx);
int main() {
    printf("Enter the number of Digits : ");
    int n;
    scanf("%d",&n);
    if(n<1) { printf("Well, that makes no sense!"); return n; }
    int *a,*b,*c;
    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(2*n*sizeof(int));
    int i;
    time_t t;
    srand((unsigned)time(&t));
    for(i=0;i<n;i++) {
            a[i]=rand()%10;
            b[i]=rand()%10;
    }
    printf("The first number is : ");
    for(i=n-1;i>=0;i--) {
        printf("%d",a[i]);
    }
    printf("\nThe second number is : ");
    for(i=n-1;i>=0;i--) {
        printf("%d",b[i]);
    }
    mul(a,b,c,n);
}
cmplx cmul(cmplx a,cmplx b) {
    cmplx c;
    c.re=a.re*b.re-a.im*b.im;
    c.im=a.re*b.im+a.im*b.re;
    return c;
}
void mul(int a[],int b[],int c[],int n) {
    cmplx *aco,*bco,*af,*bf,*cf,*cco,cmu;
    aco=(cmplx*)malloc(n*sizeof(cmplx));
    bco=(cmplx*)malloc(n*sizeof(cmplx));
    af=(cmplx*)malloc(2*n*sizeof(cmplx));
    bf=(cmplx*)malloc(2*n*sizeof(cmplx));
    cf=(cmplx*)malloc(2*n*sizeof(cmplx));
    cco=(cmplx*)malloc(2*n*sizeof(cmplx));
    int i;
    for(i=0;i<n;i++) {
        aco[i].re=a[i];
        aco[i].im=0;
        bco[i].re=b[i];
        bco[i].im=0;
    }
    fft(aco,n,af);
    fft(bco,n,bf);
    for(i=0;i<2*n;i++) {
        cmu=cmul(af[i],bf[i]);
        cf[i].re=cmu.re;
        cf[i].im=cmu.im;
    }
    ifft(cf,2*n,cco);
    for(i=0;i<n;i++) {
        cco[i].re/=n;
        cco[i].im/=n;
    }
    for(i=0;i<n;i++) {
        printf("\n%f    %f",cco[i].re,cco[i].im);
    }
}
void fft(cmplx a[],int n,cmplx f[]) {
    if(n==1) {
        f[0].re=f[1].re=a[0].re;
        f[0].im=f[1].im=a[0].im;
        return;
    }
    cmplx *o,*e,*ef,*of,omega,omegak,cmu;
    o=(cmplx*)malloc((n/2)*sizeof(cmplx));
    e=(cmplx*)malloc((n/2+n%2)*sizeof(cmplx));
    of=(cmplx*)malloc(n*sizeof(cmplx));
    ef=(cmplx*)malloc(n*sizeof(cmplx));
    int i,j;
    for(i=0,j=0;j<n;i++,j+=2) {
        e[i].re=a[j].re;
        o[i].re=a[j+1].re;
    }
    fft(o,n/2,of);
    fft(e,n/2+n%2,ef);
    omega.re=cos(pi/n);
    omega.im=sin(pi/n);
    omegak.re=1;omegak.im=0;
    for(i=0;i<n;i++) {
        cmu=cmul(omegak,of[i]);
        f[i].re=ef[i].re+cmu.re;
        f[i].im=ef[i].im+cmu.im;
        f[i+n].re=ef[i].re-cmu.re;
        f[i+n].im=ef[i].im-cmu.im;
        omegak=cmul(omega,omegak);
    }
}
void ifft(cmplx a[],int n,cmplx f[]) {
    if(n==1) {
        f[0].re=a[0].re;
        f[0].im=a[0].im;
        return;
    }
    cmplx *o,*e,*ef,*of,omega,omegak,cmu;
    o=(cmplx*)malloc((n/2)*sizeof(cmplx));
    e=(cmplx*)malloc((n/2+n%2)*sizeof(cmplx));
    of=(cmplx*)malloc((n/2)*sizeof(cmplx));
    ef=(cmplx*)malloc((n/2+n%2)*sizeof(cmplx));
    int i,j;
    for(i=0,j=0;j<n;i++,j+=2) {
        e[i]=a[j];
        if(j==n-1) continue;
        o[i]=a[j+1];
    }
    fft(o,n/2,of);
    fft(e,n/2+n%2,ef);
    omega.re=cos(2*pi/n);
    omega.im=-sin(2*pi/n);
    omegak.re=1;omegak.im=0;
    for(i=0;i<n/2;i++) {
        cmu=cmul(omegak,of[i]);
        f[i].re=ef[i].re+cmu.re;
        f[i].im=ef[i].im+cmu.im;
        f[i+n/2].re=ef[i].re-cmu.re;
        f[i+n/2].im=ef[i].im-cmu.im;
        omegak=cmul(omega,omegak);
    }
    if(n%2) {
        f[n]=ef[n/2+1];
    }
}
