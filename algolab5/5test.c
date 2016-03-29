#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node {
    int v;
    struct node *l;
    struct node *r;
}tn,*tnp;

typedef struct lnode{
    struct lnode *pre;
    int v;
    struct lnode *nex;
}ln,*lnp;

tnp maxleaf=NULL;
int maxleafl=-100000000;
int maxnodea[1000];
int maxnodeas=0;
lnp maxnode=NULL;
int maxnodel=-100000000;

int search(int ar[],int va,int si[]) {
    if(si[0]==0) return 0;
    int i;
    for(i=0;i<si[0];i++) {
        if(va==ar[i]) return 1;
    }
    return 0;
}

tnp magicalbinarytreemaker(int n,int ar[],int si[]) {
    if(n==0) return(NULL);
    float p;
    int nl,nr,ch=1;
    tnp nd;
    nd=(tnp)malloc(sizeof(tn));
    while(ch) {
        nd->v=-49+rand()%100;
        ch=search(ar,nd->v,si);
    }
    ar[si[0]]=nd->v;
    si[0]++;
    n--;
    p=0.4+((rand()%21)/100.0);
    nl=(int)(n*p+0.5);
    nr=n-nl;
    nd->l=magicalbinarytreemaker(nl,ar,si);
    nd->r=magicalbinarytreemaker(nr,ar,si);
    return(nd);
}

void inorder(tnp tr) {
    if(tr==NULL) return;
    inorder(tr->l);
    printf("%d ",tr->v);
    inorder(tr->r);
}

void preorder(tnp tr) {
    if(tr==NULL) return;
    printf("%d ",tr->v);
    preorder(tr->l);
    preorder(tr->r);
}

void postorder(tnp tr) {
    if(tr==NULL) return;
    postorder(tr->l);
    postorder(tr->r);
    printf("%d ",tr->v);
}

void maxl(tnp tr,int n) {
    int nn=n+tr->v;
    if((tr->l==NULL&&tr->r==NULL)&&(nn>maxleafl)) { maxleafl=nn; maxleaf=tr; return(n+tr->v); }
    if(tr->l!=NULL) { maxl(tr->l,nn); }
    if(tr->r!=NULL) { maxl(tr->r,nn); }
}

int pleaf(tnp tr,int ch) {
    if(tr==NULL) return 0;
    if(ch==1) {
        if(tr->l==NULL&&tr->r==NULL) {
            if(tr->v==maxleaf->v) return 1;
            else return 0;
        }
        if(pleaf(tr->l,1)==1) return 1;
        else if(pleaf(tr->r,1)==1) return 1;
        else return 0;
    }
    else {
        printf("%d ",tr->v);
        if(tr->v==maxleaf->v) return 1;
        if(pleaf(tr->l,1)==1) pleaf(tr->l,0);
        else if(pleaf(tr->r,1)==1) pleaf(tr->r,0);
    }
}

int maxn(tnp tr,lnp lnnl[]) {
    if(tr==NULL) { lnnl[0]=NULL; return 0; }
    int lnl,rnl,cnl=tr->v;
    lnp lnllt[1],lnlrt[1],lnll,lnlle,lnlr,lnlc,temp;
    lnlc=(lnp)malloc(sizeof(ln));
    lnlc->v=cnl;
    lnl=maxn(tr->l,lnllt);
    lnll=lnllt[0];
    rnl=maxn(tr->r,lnlrt);
    lnlr=lnlrt[0];
    if(lnl+cnl+rnl>maxnodel&&lnl>0&&rnl>0) {
        maxnodel=lnl+cnl+rnl;
        maxnodeas=0;
        temp=lnll;
        while(lnll->nex!=NULL) lnll=lnll->nex;
        while(lnll!=NULL) {
            maxnodea[maxnodeas]=lnll->v;
            maxnodeas++;
            lnll=lnll->pre;
        }
        lnll=temp;
        maxnodea[maxnodeas]=cnl;
        maxnodeas++;
        temp=lnlr;
        while(lnlr!=NULL) {
            maxnodea[maxnodeas]=lnlr->v;
            maxnodeas++;
            lnlr=lnlr->nex;
        }
        lnlr=temp;
    }
    if(lnl+cnl>maxnodel&&lnl>0) {
        maxnodel=lnl+cnl;
        maxnodeas=0;
        temp=lnll;
        while(lnll->nex!=NULL) lnll=lnll->nex;
        while(lnll!=NULL) {
            maxnodea[maxnodeas]=lnll->v;
            maxnodeas++;
            lnll=lnll->pre;
        }
        lnll=temp;
        maxnodea[maxnodeas]=cnl;
        maxnodeas++;
    }
    if(cnl+rnl>maxnodel&&rnl>0) {
        maxnodel=cnl+rnl;
        maxnodeas=0;
        maxnodea[maxnodeas]=cnl;
        maxnodeas++;
        temp=lnlr;
        while(lnlr!=NULL) {
            maxnodea[maxnodeas]=lnlr->v;
            maxnodeas++;
            lnlr=lnlr->nex;
        }
        lnlr=temp;
    }
    if(cnl>maxnodel) {
        maxnodel=cnl;
        maxnodeas=0;
        maxnodea[maxnodeas]=cnl;
        maxnodeas++;
    }
    if(lnl>rnl&&lnl>0) {
        lnlc->pre=NULL;
        lnlc->nex=lnll;
        if(lnll!=NULL) lnll->pre=lnlc;
        lnnl[0]=lnlc;
        return(lnl+cnl);
    }
    else if(lnl<rnl&&rnl>0) {
        lnlc->pre=NULL;
        lnlc->nex=lnlr;
        if(lnlr!=NULL) lnlr->pre=lnlc;
        lnnl[0]=lnlc;
        return(rnl+cnl);
    }
    else {
        lnlc->pre=NULL;
        lnlc->nex=NULL;
        lnnl[0]=lnlc;
        return(cnl);
    }
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int i=0,ar[1000],si[1];
    si[0]=0;
    tnp tree=NULL;
    lnp maxnodeu[0];
    tree=magicalbinarytreemaker(100,ar,si);
    inorder(tree); printf("\n\n");
    preorder(tree); printf("\n\n");
    postorder(tree); printf("\n\n");
    maxl(tree,0);
    //printf("The maximum sum from path to leaf is %d and way :\n",maxleafl);
    pleaf(tree,0); printf("\n\n");
    maxn(tree,maxnodeu);
    //printf("The maximum sum from node to node is %d and way :\n",maxnodel);
    for(i=0;i<maxnodeas;i++) {
        printf("%d ",maxnodea[i]);
    }
}
