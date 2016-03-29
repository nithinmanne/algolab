#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct hn {
    int v;
    int d;
    int m;
    int t;
    struct hn *p;
    struct hn *c;
    struct hn *l;
    struct hn *r;
}hn,*hnp;

typedef struct hep {
    hnp l;
    hnp r;
    int m;
}hep,*hpp;

typedef struct {
    int *v;
}bl,*blp;

typedef struct {
    int mx;
    int mn;
}mxmn,*mxmnp;

hnp hnnp[10001];

hpp makeHeap() {
    hpp heap;
    heap=(hpp)malloc(sizeof(hep));
    heap->l=heap->r=NULL;
    return(heap);
}

void insertHeap(hpp hp,int x) {
    if(hnnp[x]!=NULL) return;
    hnp nhn;
    nhn=(hnp)malloc(sizeof(hn));
    nhn->v=x;
    nhn->d=nhn->m=0;
    nhn->t=1;
    nhn->p=nhn->c=nhn->l=nhn->r=NULL;
    hnnp[x]=nhn;
    if(hp->l==NULL) {
        hp->l=hp->r=nhn;
        hp->m=x;
        return;
    }
    hnp tmp;
    tmp=hp->l;
    hp->l=nhn;
    nhn->r=tmp;
    tmp->l=nhn;
    if(hp->m>x) hp->m=x;
}

hpp unionHeap(hpp hp1,hpp hp2) {
    if(hp1->l==NULL) return(hp2);
    if(hp2->r==NULL) return(hp1);
    hpp heap;
    heap=(hpp)malloc(sizeof(hep));
    heap->l=hp1->l;
    hp1->r->r=hp2->l;
    heap->r=hp2->r;
    heap->m=hp1->m<hp2->m?hp1->m:hp2->m;
    return(heap);
}

void decreaseKeyHeap(hpp hp,int x,int k) {
    if(k==-1) return;
    if(hnnp[x]==NULL) return;
    if(hnnp[k]!=NULL) return;
    hnp tmp,tmp1;
    tmp=hnnp[x];
    hnnp[x]=NULL;
    hnnp[k]=tmp;
    tmp->v=k;
    if(hp->m>k) hp->m=k;
    if(tmp->p==NULL) return;
    if(tmp->p!=NULL) if(tmp->p->v<k) return;
    tmp->t=tmp->t+3;
    while(tmp->p!=NULL) {
        tmp->t=tmp->t-2;
        tmp1->t++;
        tmp1=tmp->p;
        if(tmp->l==NULL) tmp1->c=tmp->r;
        else tmp->l->r=tmp->r;
        tmp->r=hp->l;
        hp->l=tmp;
        tmp1->m++;
        if(tmp1->m==1) return;
        tmp1->m=0;
        tmp=tmp1;
    }
    tmp->t--;
}

void extractMinHeap(hpp hp) {
    if(hp->l==hp->r&&hp->l->c==NULL) {
        hp->l=hp->r=NULL;
        hnnp[hp->m]=NULL;
        hp->m=10001;
        return;
    }
    hnp tmp,tmp1,tmp2,ttmp;
    tmp=hnnp[hp->m];
    hnnp[hp->m]=NULL;
    hp->m=10001;
    if(tmp->c==NULL) {
        if(tmp->l==NULL) hp->l=tmp->r;
        else tmp->l->r=tmp->r;
        if(tmp->r==NULL) hp->r=NULL;
        else tmp->r->l=tmp->l;
    }
    else {
        if(tmp->l==NULL) hp->l=tmp->c;
        else tmp->l->r=tmp->c;
        tmp1=tmp->c;
        tmp1->l=tmp->l;
        while(tmp1->r!=NULL) tmp1=tmp1->r;
        tmp1->r=tmp->r;
        if(tmp->r==NULL) hp->r=NULL;
        else tmp->r->l=tmp1;
    }
    hnp s[20];
    int i;
    for(i=0;i<20;i++) s[i]=NULL;
    tmp=hp->l;
    hp->l=hp->r=NULL;
    while(tmp!=NULL) {
        tmp1=tmp;
        tmp=tmp->r;
        tmp1->l=tmp1->r=NULL;
        if(s[tmp1->d]==NULL) {
            s[tmp1->d]=tmp1;
            continue;
        }
        tmp2=s[tmp1->d];
        if(tmp1->v<tmp2->v) {
            ttmp=tmp1;
            tmp1=tmp2;
            tmp2=ttmp;
        }
        tmp2->d++;
        tmp1->t--;
        tmp1->p=tmp2;
        tmp1->r=tmp2->c;
        tmp2->c=tmp1;
        tmp2->r=tmp;
        tmp=tmp2;
        s[tmp1->d]=NULL;
    }
    for(i=0;i<20;i++) {
        if(s[i]==NULL) continue;
        if(hp->l==NULL) { hp->l=s[i]; s[i]->l=NULL; }
        else { tmp->r=s[i]; s[i]->l=tmp; }
        tmp=s[i];
    }
    hp->r=tmp;
    tmp->r=NULL;
    tmp=hp->l;
    while(tmp!=NULL) {
        if(tmp->v<hp->m) hp->m=tmp->v;
        tmp=tmp->r;
    }
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int l,b,m;
    printf("Enter number of lists (k) : ");
    scanf("%d",&l);
    printf("Enter number of blocks per list : ");
    scanf("%d",&b);
    printf("Enter number of items per block (m) : ");
    scanf("%d",&m);
    int i,j,n;
    hpp *heap,fheap;
    blp *blk,fblk;
    heap=(hpp*)malloc(l*sizeof(hpp));
    fheap=makeHeap();
    blk=(blp*)malloc(l*sizeof(blk));
    fblk=(blp)malloc(l*b*sizeof(bl));
    for(i=0;i<10000;i++) hnnp[i]=NULL;
    for(i=0;i<l;i++) {
        blk[i]=(blp)malloc(b*sizeof(bl));
        for(j=0;j<b;j++) blk[i][j].v=(int*)malloc(m*sizeof(int));
    }
    for(i=0;i<l*b;i++) fblk[i].v=(int*)malloc(m*sizeof(int));
    for(i=0;i<l;i++) {
        heap[i]=makeHeap();
        for(j=0;j<b*m;j++) {
            n=rand()%10000;
            if(hnnp[n]!=NULL) {
                j--;
                continue;
            }
            insertHeap(heap[i],n);
        }
    }
    for(i=0;i<l;i++) {
        printf("List %d :\n",i+1);
        for(j=0;j<b;j++) {
            for(n=0;n<m;n++) {
                blk[i][j].v[n]=heap[i]->m;
                printf("%d ",blk[i][j].v[n]);
                extractMinHeap(heap[i]);
            }
            printf("\n");
        }
        printf("\n");
    }
    mxmnp deck;
    deck=(mxmnp)malloc(l*b*sizeof(mxmn));
    for(i=0;i<l*b;i++) deck[i].mn=deck[i].mx=-1;
    for(i=0;i<l;i++)
        for(j=0;j<b;j++) {
            for(n=0;n<m;n++) insertHeap(heap[i],blk[i][j].v[n]);
            if(blk[i][j].v[0]>0)
            //decreaseKeyHeap(heap[i],blk[i][j].v[m-1],blk[i][j].v[0]-1);
            deck[i*b+j].mn=blk[i][j].v[0];
            deck[i*b+j].mx=blk[i][j].v[m-1];
        }
    for(i=0;i<l;i++) {
        fheap=unionHeap(fheap,heap[i]);
    }
    for(i=0;i<l*b;i++) decreaseKeyHeap(fheap,deck[i].mx,deck[i].mn-1);
    printf("\nThe Resultant List is :\n");
    for(i=0;i<l*b;i++) {
        for(j=0;j<m;j++) {
            printf("%d ",fheap->m);
            extractMinHeap(fheap);
        }
        printf("\n");
    }
    return(0);
}
