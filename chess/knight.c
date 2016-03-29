#include<stdio.h>
#include<stdlib.h>
int brd[10][10];
int move(int *ar,int i,int j,int ad) {
    if(i>4||j>4||i<0||j<0) return(0);
    int ij,ji;
    if(brd[i][j]==1) {
        for(ij=0;ij<5;ij++)
            for(ji=0;ji<5;ji++)
                if(brd[ij][ji]==0) return(0);
        return(1);
    }
    int t;
    brd[i+1][j+2]=1;
    t=move(ar,i+1,j+2,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i+1][j+2]=0;
    brd[i+1][j-2]=1;
    t=move(ar,i+1,j-2,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i+1][j-2]=0;
    brd[i-1][j+2]=1;
    t=move(ar,i-1,j+2,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i-1][j+2]=0;
    brd[i-1][j+2]=1;
    t=move(ar,i-1,j+2,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i-1][j+2]=0;
    brd[i+2][j+1]=1;
    t=move(ar,i+2,j+1,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i+2][j+1]=0;
    brd[i+2][j-1]=1;
    t=move(ar,i+2,j-1,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i+2][j-1]=0;
    brd[i-2][j+1]=1;
    t=move(ar,i-2,j+1,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i-2][j+1]=0;
    brd[i-2][j-1]=1;
    t=move(ar,i-2,j-1,ad+1);
    if(t) { ar[ad]=5*i+j; return(1); }
    else brd[i-2][j-1]=0;
    return(0);
}
int main() {
    int i,j,ar[100];
    for(i=0;i<5;i++)
        for(j=0;j<5;j++) brd[i][j]=0;
    brd[0][0]=1;
    move(ar,0,0,0);
    for(i=0;i<25;i++) printf("%d, ",ar[i]);
}
