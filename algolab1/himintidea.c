#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define pi 3.14159265
typedef struct {
    double re;
    double im;
}complex;
complex comp_mul(complex A,complex B) {
    complex C;
    C.re=A.re*B.re-A.im*B.im;
    C.im=A.re*B.im+A.im*B.re;
    return C;
}
void fft(int a[],int n,complex f[]) {
    int j,k;
    int *e,*o;
    complex *ef,*of,omegak,omega,cmu;
    ef=(complex*)malloc(n*sizeof(complex));
    of=(complex*)malloc(n*sizeof(complex));
    if(n==1){ f[0].re=f[1].re=a[0]; f[0].im=f[1].im=0; return; }
    e=(int*)malloc(n*sizeof(int));
    o=(int*)malloc(n*sizeof(int));
    omega.re=cos(1.0*pi/n);omega.im=sin(1.0*pi/n);
    omegak.re=1;omegak.im=0;
    for(j=k=0;k<n;j++,k+=2){ e[j]=a[k]; o[j]=a[k+1]; }
    fft(e,n/2,ef);
    fft(o,n/2,of);
        for(k=0;k<n;k++) {
            cmu=comp_mul(omegak,of[k]);
            f[k].re=ef[k].re+cmu.re;
            f[k].im=ef[k].im+cmu.im;
            f[k+n].re=ef[k].re-cmu.re;
            f[k+n].im=ef[k].im-cmu.im;
            omegak=comp_mul(omegak,omega);
        }
        return;
}
void ifft (complex a[],int n,complex f[]) {
    int j,k;
    complex omegak,omega,*ef,*of,*e,*o,cmu;
    ef=(complex*)malloc(n/2*sizeof(complex));
    of=(complex*)malloc(n/2*sizeof(complex));
    e=(complex*)malloc(n/2*sizeof(complex));
    o=(complex*)malloc(n/2*sizeof(complex));
    if(n==1){ f[0].re=a[0].re; f[0].im=a[0].im; return; }
    for(j=k=0;k<n;j++,k+=2){ e[j].re=a[k].re; e[j].im=a[k].im; o[j].re=a[k+1].re; o[j].im=a[k+1].im; }
    omega.re=cos(2*pi/n); omega.im=-1*sin(2*pi/n);
    omegak.re=1; omegak.im=0;
    ifft(e,n/2,ef);
    ifft(o,n/2,of);
    for(k=0;k<n/2;k++) {
        cmu=comp_mul(omegak,of[k]);
        f[k].re=ef[k].re+cmu.re;
        f[k].im=ef[k].im+cmu.im;
        f[k+n/2].re=ef[k].re-cmu.re;
        f[k+n/2].im=ef[k].im-cmu.im;
        omegak=comp_mul(omegak,omega);
    }
    return;
}


int main() {
    int i,d,temp=0,n;
    int *A,*B,*c;
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
        A[i]=0;
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
    for(i=2*d-1;i>=0;i--){ cif[i].re=cif[i].re/(2*d); c[i]=(int)(cif[i].re+0.5); }
    for(i=2*d-1;i>0;i--){ c[i-1]=c[i-1]+c[i]/10; c[i]=c[i]%10; }
    printf("The Product is :");
    for(i=2*d-2*n;i<2*d-1;i++) printf("%d",c[i]);
    return 0;
}
