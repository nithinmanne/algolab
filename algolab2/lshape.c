#include<stdio.h>
#include<stdlib.h>

void lfill(long int,long int,long int,long int,long int);
int main() {
    printf("Location and Shape Definitions :-\n\n");
    printf("Location gives the co-ordinates of the center element of the shape\n");
    printf("The co-ordinates go from (0,0) on BOTTOM LEFT to (n-1,n-1) on TOP RIGHT\n\n");
    printf("Shape gives the orientation of the L shaped tile\n");
    printf("Shape 1 means proper L shape\n");
    printf("Shape 2 means upside down L shape\n");
    printf("Shape 3 means mirrored L shape\n");
    printf("Shape 4 means mirrored upside down L shape\n\n\n");
    long int n,x,y;
    printf("Enter the value of 'n' (must be a power of 2) : ");
    scanf("%ld",&n);
    printf("Enter the co-ordinates of the missing cell :-\n");
    printf("x : ");
    scanf("%ld",&x);
    printf("y : ");
    scanf("%ld",&y);
    lfill(n,0,0,x,y);
    return 1;
}
void lfill(long int n,long int x,long int y,long int xf,long int yf) {
    if(n==1) return;
    if(xf>=n/2&&yf>=n/2) {
        printf("Location : (%d,%d) and Shape : 1\n",x+n/2-1,y+n/2-1);
        lfill(n/2,x,y,n/2-1,n/2-1);
        lfill(n/2,x,y+n/2,n/2-1,0);
        lfill(n/2,x+n/2,y,0,n/2-1);
        lfill(n/2,x+n/2,y+n/2,xf-n/2,yf-n/2);
    }
    else if(xf>=n/2&&yf<n/2) {
        printf("Location : (%d,%d) and Shape : 2\n",x+n/2-1,y+n/2);
        lfill(n/2,x,y,n/2-1,n/2-1);
        lfill(n/2,x,y+n/2,n/2-1,0);
        lfill(n/2,x+n/2,y,xf-n/2,yf);
        lfill(n/2,x+n/2,y+n/2,0,0);
    }
    else if(yf>=n/2) {
        printf("Location : (%d,%d) and Shape : 3\n",x+n/2,y+n/2-1);
        lfill(n/2,x,y,n/2-1,n/2-1);
        lfill(n/2,x,y+n/2,xf,yf-n/2);
        lfill(n/2,x+n/2,y,0,n/2-1);
        lfill(n/2,x+n/2,y+n/2,0,0);
    }
    else {
        printf("Location : (%d,%d) and Shape : 4\n",x+n/2,y+n/2);
        lfill(n/2,x,y,xf,yf);
        lfill(n/2,x,y+n/2,n/2-1,0);
        lfill(n/2,x+n/2,y,0,n/2-1);
        lfill(n/2,x+n/2,y+n/2,0,0);
    }
}
