#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define pi 3.14159265

//Particle 1 : Red
//Particle 2 : Yellow
//Particle 3 : Green
//Particle 4 : Blue
//Particle 5 : Black

typedef struct {
    int c;
    float r;
    float x;
    float y;
    float vx;
    float vy;
    int i;
}prt,*pprt;

typedef struct {
    int a;
    int ai;
    int b;
    int bi;
    float t;
}hpd,*phpd;

typedef struct {
    int n;
    phpd hp;
}hap,*phap;

void fsave(prt st[5],hpd hp,float prep[5][2]) {
    FILE *f1;
    f1=fopen("collision.log","a");
    fprintf(f1,"\nCollision Time : %f\n",hp.t);
    int i,j;
    for(i=0;i<5;i++) {
        fprintf(f1,"Particle ");
        if(i==0) fprintf(f1,"red :\n");
        if(i==1) fprintf(f1,"yellow :\n");
        if(i==2) fprintf(f1,"green :\n");
        if(i==3) fprintf(f1,"blue :\n");
        if(i==4) fprintf(f1,"black :\n");
        fprintf(f1,"Location : (%f,%f)\n",st[i].x,st[i].y);
        fprintf(f1,"Velocity Vectors : (%f,%f)\n",st[i].vx,st[i].vy);
    }
    for(i=0;i<5;i++) {
        if(i==0) f1=fopen("red.dat","a");
        if(i==1) f1=fopen("yellow.dat","a");
        if(i==2) f1=fopen("green.dat","a");
        if(i==3) f1=fopen("blue.dat","a");
        if(i==4) f1=fopen("black.dat","a");fprintf(f1,"\n");
        for(j=0;j<=10;j++) fprintf(f1,"%f %f \n",(prep[i][0]+(j/10.0)*(st[i].x-prep[i][0])),(prep[i][1]+(j/10.0)*(st[i].y-prep[i][1])));
    }
}

void gmaker() {//Plot using gnuplot
    char * c1[] = {"set title \"BLUE\"", "plot 'blue.dat' with line lc rgb \"blue\""};
    char * c2[] = {"set title \"RED\"", "plot 'red.dat' with line lc rgb \"red\""};
    char * c3[] = {"set title \"GREEN\"", "plot 'green.dat' with line lc rgb \"green\""};
    char * c4[] = {"set title \"YELLOW\"", "plot 'yellow.dat' with line lc rgb \"yellow\""};
    char * c5[] = {"set title \"BLACK\"", "plot 'black.dat' with line lc rgb \"black\""};
    char * c0[] = {"set title \"BLACK\"", "plot 'blue.dat' with line lc rgb \"blue\", \'black.dat' with line lc rgb \"black\", \'red.dat' with line lc rgb \"red\", \'yellow.dat' with line lc rgb \"yellow\", \'green.dat' with line lc rgb \"green\""};
    FILE * g = popen ("gnuplot -persistent", "w");
    FILE * g1 = popen ("gnuplot -persistent", "w");
    FILE * g2 = popen ("gnuplot -persistent", "w");
    FILE * g3 = popen ("gnuplot -persistent", "w");
    FILE * g4 = popen ("gnuplot -persistent", "w");
    FILE * g5 = popen ("gnuplot -persistent", "w");
    int i;
    for(i=0;i<2;i++) fprintf(g,"%s \n",c0[i]);
    for(i=0;i<2;i++) fprintf(g1,"%s \n",c1[i]);
    for(i=0;i<2;i++) fprintf(g2,"%s \n",c2[i]);
    for(i=0;i<2;i++) fprintf(g3,"%s \n",c3[i]);
    for(i=0;i<2;i++) fprintf(g4,"%s \n",c4[i]);
    for(i=0;i<2;i++) fprintf(g5,"%s \n",c5[i]);
}

float tcol(prt pa,prt pb) {
    prt bwa;
    bwa.x=pb.x-pa.x;
    bwa.y=pb.y-pa.y;
    bwa.vx=pb.vx-pa.vx;
    bwa.vy=pb.vy-pa.vy;
    float a,b,c;
    a=bwa.vx*bwa.vx+bwa.vy*bwa.vy;
    b=bwa.x*bwa.vx+bwa.y*bwa.vy;
    c=bwa.x*bwa.x+bwa.y*bwa.y-(pa.r+pb.r)*(pa.r+pb.r);
    float det=b*b-a*c;
    if(det<=0) return(-1);
    if(c<0) return(0);
    det=sqrt(det);
    float tim=-(b/a)-(det/a);
    return(tim);
}

void vcol(prt st[5],int a,int b) {
    if(b==-1||b==-3) {
        st[a].vy=-st[a].vy;
        return;
    }
    if(b==-2||b==-4) {
        st[a].vx=-st[a].vx;
        return;
    }
    float mx,my,tht;
    mx=st[b].x-st[a].x;
    my=st[b].y-st[a].y;
    if(mx==0) tht=pi/2;
    else tht=atan(my/mx);
    float avc,avn,bvc,bvn,tmp;;
    avc=st[a].vx*cos(tht)+st[a].vy*sin(tht);
    avn=-st[a].vx*sin(tht)+st[a].vy*cos(tht);
    bvc=st[b].vx*cos(tht)+st[b].vy*sin(tht);
    bvn=-st[b].vx*sin(tht)+st[b].vy*cos(tht);
    tmp=avc;
    avc=bvc;
    bvc=tmp;
    st[a].vx=avc*cos(tht)-avn*sin(tht);
    st[a].vy=avc*sin(tht)+avn*cos(tht);
    st[b].vx=bvc*cos(tht)-bvn*sin(tht);
    st[b].vy=bvc*sin(tht)+bvn*cos(tht);
}

hap hin(hap heap,hpd num) {
    if(heap.n==0) {
        heap.hp[1]=num;
        heap.n++;
        return(heap);
    }
    heap.n++;
    int n=heap.n;
    while(n>1) {
        if(num.t>=heap.hp[n/2].t) {
            heap.hp[n]=num;
            return(heap);
        }
        heap.hp[n]=heap.hp[n/2];
        n=n/2;
    }
    heap.hp[1]=num;
    return(heap);
}

hap hdm(hap heap) {
    if(heap.n==1) {
        heap.n=0;
        return(heap);
    }
    heap.n--;
    int i=1,n=heap.n;
    hpd tmp;
    heap.hp[1]=heap.hp[n+1];
    while(i<=n) {
        if(2*i>n) return(heap);
        else if(2*i==n) {
            if(heap.hp[n].t<heap.hp[i].t) {
                tmp=heap.hp[n];
                heap.hp[n]=heap.hp[i];
                heap.hp[i]=tmp;
            }
            return(heap);
        }
        if(heap.hp[2*i].t<heap.hp[i].t&&heap.hp[2*i].t<heap.hp[2*i+1].t) {
            tmp=heap.hp[2*i];
            heap.hp[2*i]=heap.hp[i];
            heap.hp[i]=tmp;
            i=2*i;
        }
        else if(heap.hp[2*i+1].t<heap.hp[i].t) {
            tmp=heap.hp[2*i+1];
            heap.hp[2*i+1]=heap.hp[i];
            heap.hp[i]=tmp;
            i=2*i+1;
        }
        else return(heap);
    }
    return(heap);
}

int main() {
    int l=100,b=100;
    int lb=(l>b)?b:l;
    time_t t;
    srand((unsigned)time(&t));
    float th,tp=0,tt;
    float prep[5][2];
    FILE *f1;
    f1=fopen("collision.log","w");
    f1=fopen("red.dat","w");
    f1=fopen("yellow.dat","w");
    f1=fopen("blue.dat","w");
    f1=fopen("green.dat","w");
    f1=fopen("black.dat","w");
    fclose(f1);
    printf("Enter the time horizon : ");
    scanf("%f",&th);
    prt STATE[5];
    int i,j,ch=1;
    while(ch) {
        ch=0;
        for(i=0;i<5;i++) {
            STATE[i].c=i;
            STATE[i].i=0;
            STATE[i].r=1+rand()%(10-1);
            STATE[i].x=STATE[i].r+rand()%(l-(int)(2*STATE[i].r));
            STATE[i].y=STATE[i].r+rand()%(b-(int)(2*STATE[i].r));
            STATE[i].vx=-5+rand()%11;
            STATE[i].vy=-5+rand()%11;
        }
        for(i=0;i<4;i++)
            for(j=i+1;j<5;j++)
                if(tcol(STATE[i],STATE[j])==0) { ch=1; break; }
    }
    for(i=0;i<5;i++) {
        prep[i][0]=STATE[i].x;
        prep[i][1]=STATE[i].y;
    }
    hap heap;
    hpd thp,tthp;
    heap.hp=(phpd)malloc(100000*sizeof(hpd));
    heap.n=0;
    for(i=0;i<4;i++) {
        for(j=i+1;j<5;j++) {
            tt=tcol(STATE[i],STATE[j]);
            if(tt<0) continue;
            thp.a=i; thp.ai=STATE[i].i;
            thp.b=j; thp.bi=STATE[j].i;
            thp.t=tt;
            heap=hin(heap,thp);
        }
    }
    float tx,ty;
    for(i=0;i<5;i++) {
        if(STATE[i].vx==0) tx=-1;
        else if(STATE[i].vx>0) tx=(l-STATE[i].r-STATE[i].x)/STATE[i].vx;
        else tx=(STATE[i].r-STATE[i].x)/STATE[i].vx;
        if(STATE[i].vy==0) ty=-1;
        else if(STATE[i].vy>0) ty=(b-STATE[i].r-STATE[i].y)/STATE[i].vy;
        else ty=(STATE[i].r-STATE[i].y)/STATE[i].vy;
        thp.a=i;
        thp.ai=STATE[i].i;
        thp.bi=-1;
        if(ty==-1&&tx==-1) continue;
        else if(tx==-1) {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty;
        }
        else if(ty==-1) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx;
        }
        else if(tx<ty) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx;
        }
        else {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty;
        }
        heap=hin(heap,thp);
    }
    while(tp<th) {
        tthp=heap.hp[1];
        if(tthp.t>th) break;
        heap=hdm(heap);
        if(tthp.ai<STATE[tthp.a].i) continue;
        if(tthp.b>=0) if(tthp.bi<STATE[tthp.b].i) continue;
        STATE[tthp.a].i++;
        if(tthp.b>=0) STATE[tthp.b].i++;
        for(i=0;i<5;i++) {
            STATE[i].x=STATE[i].x+STATE[i].vx*(tthp.t-tp);
            STATE[i].y=STATE[i].y+STATE[i].vy*(tthp.t-tp);
        }
        fsave(STATE,tthp,prep);
        for(i=0;i<5;i++) {
            prep[i][0]=STATE[i].x;
            prep[i][1]=STATE[i].y;
        }
        vcol(STATE,tthp.a,tthp.b);
        tp=tthp.t;
        for(i=0;i<5;i++) {
            if(i==tthp.a||i==tthp.b) continue;
            tt=tcol(STATE[i],STATE[tthp.a]);
            if(tt<0) continue;
            thp.a=i; thp.ai=STATE[tthp.a].i;
            thp.b=tthp.a; thp.bi=STATE[tthp.a].i;
            thp.t=tt+tp;
            heap=hin(heap,thp);
        }
        i=tthp.a;
        if(STATE[i].vx==0) tx=-1;
        else if(STATE[i].vx>0) tx=(l-STATE[i].r-STATE[i].x)/STATE[i].vx;
        else tx=(STATE[i].r-STATE[i].x)/STATE[i].vx;
        if(STATE[i].vy==0) ty=-1;
        else if(STATE[i].vy>0) ty=(b-STATE[i].r-STATE[i].y)/STATE[i].vy;
        else ty=(STATE[i].r-STATE[i].y)/STATE[i].vy;
        thp.a=i;
        thp.ai=STATE[i].i;
        thp.bi=-1;
        if(ty==-1&&tx==-1) continue;
        else if(tx==-1) {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty+tp;
        }
        else if(ty==-1) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx+tp;
        }
        else if(tx<ty) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx+tp;
        }
        else {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty+tp;
        }
        heap=hin(heap,thp);
        if(tthp.b<0) continue;
        for(i=0;i<5;i++) {
            if(i==tthp.a||i==tthp.b) continue;
            tt=tcol(STATE[i],STATE[tthp.b]);
            if(tt<0) continue;
            thp.a=i; thp.ai=STATE[i].i;
            thp.b=tthp.b; thp.bi=STATE[tthp.b].i;
            thp.t=tt+tp;
            heap=hin(heap,thp);
        }
        i=tthp.b;
        if(STATE[i].vx==0) tx=-1;
        else if(STATE[i].vx>0) tx=(l-STATE[i].r-STATE[i].x)/STATE[i].vx;
        else tx=(STATE[i].r-STATE[i].x)/STATE[i].vx;
        if(STATE[i].vy==0) ty=-1;
        else if(STATE[i].vy>0) ty=(b-STATE[i].r-STATE[i].y)/STATE[i].vy;
        else ty=(STATE[i].r-STATE[i].y)/STATE[i].vy;
        thp.a=i;
        thp.ai=STATE[i].i;
        thp.bi=-1;
        if(ty==-1&&tx==-1) continue;
        else if(tx==-1) {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty+tp;
        }
        else if(ty==-1) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx+tp;
        }
        else if(tx<ty) {
            if(STATE[i].vx>0) thp.b=-2;
            else thp.b=-4;
            thp.t=tx+tp;
        }
        else {
            if(STATE[i].vy>0) thp.b=-3;
            else thp.b=-1;
            thp.t=ty+tp;
        }
        heap=hin(heap,thp);
    }
    for(i=0;i<5;i++) {
        STATE[i].x=STATE[i].x+STATE[i].vx*(th-tp);
        STATE[i].y=STATE[i].y+STATE[i].vy*(th-tp);
    }
    fsave(STATE,tthp,prep);
    gmaker();

    return(0);

}
