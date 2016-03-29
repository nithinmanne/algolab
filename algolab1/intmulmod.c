#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define pi 3.14159
typedef struct {
    float re;
    float im;
}cmplx;
void mul(int*,int*,int*,int,int);
void fft(int*,int,cmplx*);
cmplx cmul(cmplx,cmplx);
int main() {
    printf("Enter the number of Digits : ");
    int n,d,i;
    scanf("%d",&n);
    if(n<1) { printf("Well, that makes no sense!"); return n; }
    for(i=0;pow(2,i)<n;i++) {}
    d=pow(2,i);
    int *a,*b,*c;
    a=(int*)malloc(d*sizeof(int));
    b=(int*)malloc(d*sizeof(int));
    c=(int*)malloc(2*d*sizeof(int));
    for(i=0;i<d-n;i++) { a[i]=0; b[i]=0; }
    time_t t;
    srand((unsigned)time(&t));
    for(i=d-n;i<d;i++) {
            a[i]=rand()%10;
            b[i]=rand()%10;
    }
    printf("The first number is : ");
    for(i=d-n;i<d;i++) {
        printf("%d",a[i]);
    }
    printf("\nThe second number is : ");
    for(i=d-n;i<d;i++) {
        printf("%d",b[i]);
    }
    mul(a,b,c,d,n);
    printf("\n%d   %d",n,d);
    printf("\nThe product is : ");
    for(i=2*d-2*n-1;i<2*d-1;i++) { printf("%d",c[i]); }
}
cmplx cmul(cmplx a,cmplx b) {
    cmplx c;
    c.re=a.re*b.re-a.im*b.im;
    c.im=a.re*b.im+a.im*b.re;
    return c;
}
void mul(int a[],int b[],int c[],int d,int n) {
    cmplx *af,*bf,*cf,*cco,cmu;
    af=(cmplx*)malloc(2*d*sizeof(cmplx));
    bf=(cmplx*)malloc(2*d*sizeof(cmplx));
    cf=(cmplx*)malloc(2*d*sizeof(cmplx));
    cco=(cmplx*)malloc(2*d*sizeof(cmplx));
    int i;
    fft(a,d,af);
    fft(b,d,bf);
    for(i=0;i<2*d;i++) {
        cmu=cmul(af[i],bf[i]);
        cf[i].re=cmu.re;
        cf[i].im=cmu.im;
    }
    ifft(cf,2*d,cco);
    for(i=0;i<2*d;i++) c[i]=0;
    for(i=2*d-1;i>=0;i--) {
        cco[i].re/=(2*d);
        cco[i].im/=(2*d);
        c[i]=(int)(cco[i].re+0.5);
    }
    for(i=2*d;i>0;i--){c[i-1]=c[i-1]+c[i]/10;c[i]=c[i]%10;}
}
void fft(int a[],int n,cmplx f[]) {
    if(n==1) {
        f[0].re=f[1].re=a[0];
        f[0].im=f[1].im=0;
        return;
    }
    cmplx *ef,*of,omega,omegak,cmu;
    int *o,*e;
    o=(int*)malloc((n/2)*sizeof(int));
    e=(int*)malloc((n/2+n%2)*sizeof(int));
    of=(cmplx*)malloc(n*sizeof(cmplx));
    ef=(cmplx*)malloc(n*sizeof(cmplx));
    int i,j;
    for(i=0,j=0;j<n;i++,j+=2) {
        e[i]=a[j];
        o[i]=a[j+1];
    }
    fft(o,n/2,of);
    fft(e,n/2,ef);
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
    e=(cmplx*)malloc((n/2)*sizeof(cmplx));
    of=(cmplx*)malloc((n/2)*sizeof(cmplx));
    ef=(cmplx*)malloc((n/2)*sizeof(cmplx));
    int i,j;
    for(i=0,j=0;j<n;i++,j+=2) {
        e[i]=a[j];
        o[i]=a[j+1];
    }
    ifft(o,n/2,of);
    ifft(e,n/2+n%2,ef);
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
}
