#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int yes() {
    printf("Yes, It is Possible to make a Profit!\n");
    return 1;
}

int no() {
    printf("No, It is not Possible to make a Profit!\n");
    return 0;
}

int main() {
    int n=30;
    int i,j,k;
    float **ex,*er;
    ex=(float**)malloc(n*sizeof(float*));
    er=(float*)malloc(n*sizeof(float));
    for(i=0;i<n;i++) ex[i]=(float*)malloc(n*sizeof(float));
    printf("Enter the exchange rates for 100 units each\n");
    for(i=0;i<n;i++) {
        printf("Enter number of units that can be bought with 100 units of currency %d\n",(i+1));
        for(j=0;j<n;j++) {
            printf("Currency %d ( Entry [%d][%d] ) : ",(j+1),(i+1),(j+1));
            scanf("%f",&ex[i][j]);
            ex[i][j]=-log10(ex[i][j]/100);
        }
        printf("\n");
    }
    for(i=0;i<n;i++)
        if(ex[i][i]!=0) {
            printf("Input Error!\n");
            return 0;
        }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(ex[i][j]+ex[j][i]<0) return(yes());
    for(i=0;i<n;i++) er[i]=100000;
    er[0]=0;
    for(i=0;i<n-1;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
                if(j!=k&&er[j]>er[k]+ex[j][k])
                    er[j]=er[k]+ex[j][k];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i!=j&&er[i]>er[j]+ex[i][j]) return(yes());
    return(no());
}
