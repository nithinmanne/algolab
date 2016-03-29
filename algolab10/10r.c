#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main(){
    float A[30][30];
    float E[30][30];
    float V[30];
    int i,j,n,k,flag=0;n=3;
    printf("Enter the Table :\n");

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf(" A[%d][%d] :\n",i+1,j+1);
            scanf("%f",&A[i][j]);
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            E[i][j]=log(100.0/A[i][j]);
        }
        V[i]=50000;
    }
    V[0]=0;

    for(k=0;k<n-1;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i!=j){
                    if(V[i]>V[j]+E[i][j]) V[i]=V[j]+E[i][j];}
            }
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){

            if(i!=j){
                if(V[i]>V[j]+E[i][j]){flag=1;printf("There is a negative cycle in the graph.\nHence One can get profit by doing this process."); break;}}
        }
        if(flag==1)break;
    }
    if(flag==0){printf("There is no negative cycle in the graph.\nHence We can't get profit by doing this process.");}

    return 0;
}
