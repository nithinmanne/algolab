#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node1 {
    int i;
    struct node1 *n;
}ll,*llp;

typedef struct nose12 {
    int l;
    int u;
    struct node12 *n;
}li,*lip;

typedef struct node2 {
    int l;
    int u;
    llp lst;
    struct node2 *lt;
    struct node2 *rt;
}tn,*tnp;

tnp mktree(lip ip) {
    if(ip==NULL) return(NULL);
    int n=0,i;
    lip tmp,tmp1;
    tnp nd;
    nd=(tnp)malloc(sizeof(tn));
    if(ip->n==NULL) {
        nd->l=ip->l; nd->u=ip->u; nd->lst=NULL;
        nd->lt=NULL; nd->rt=NULL;
        return(nd);
    }
    tmp=ip;
    while(tmp!=NULL) { n++; tmp=tmp->n; }
    tmp=ip;
    for(i=0;i<(n/2-1);i++) tmp=tmp->n;
    tmp1=tmp->n;
    tmp->n=NULL;
    nd->l=tmp1->l;
    nd->u=tmp1->u;
    nd->lst=NULL;
    tmp1=tmp1->n;
    nd->lt=mktree(ip);
    nd->rt=mktree(tmp1);
    return(nd);
}

tnp CREATE_INTERVAL_TREE(int l,int u,int n) {
    lip ip,tmp,tmp1;
    tnp nd;
    int s,r,i;
    s=(u-l+1)/n;
    r=(u-l+1)%n;
    ip=(lip)malloc(sizeof(li));
    ip->l=l;
    ip->u=l+s-1+((r>0)?1:0);
    r--;
    tmp=ip;
    for(i=1;i<n;i++) {
        tmp1=(lip)malloc(sizeof(li));
        tmp1->l=tmp->u+1;
        tmp1->u=tmp1->l+s-1+((r>0)?1:0);
        r--;
        tmp->n=tmp1;
        tmp=tmp1;
    }
    tmp->n=NULL;
    nd=mktree(ip);
    return(nd);
}

int hfinder(tnp nd) {
    if(nd==NULL) return 0;
    int lh,rh,h;
    lh=hfinder(nd->lt);
    rh=hfinder(nd->rt);
    h=lh>rh?lh:rh;
    h++;
    return(h);
}

void PRETTY_PRINT(tnp nd) {
    if(nd==NULL) return;
    int h=hfinder(nd);
    PRETTY_PRINT(nd->lt);
    int i;
    llp tl;
    for(i=h;i>1;i--) printf("   ");
    printf("[%d,%d] ",nd->l,nd->u);
    tl=nd->lst;
    if(tl==NULL) printf("........");
    else { while(tl!=NULL) { printf("%d, ",tl->i); tl=tl->n; } }
    printf("\b\b\n");
    PRETTY_PRINT(nd->rt);
}

void INSERT(tnp nd,int i) {
    if(nd==NULL) return;
    if(i>=nd->l&&i<=nd->u) {
        llp lp,tmp,tmp1;
        lp=(llp)malloc(sizeof(ll));
        lp->i=i;
        lp->n=NULL;
        if(nd->lst==NULL) { nd->lst=lp; return; }
        tmp=nd->lst;
        if(i<tmp->i) { tmp1=nd->lst; nd->lst=lp; lp->n=tmp1; return; }
        tmp1=tmp;
        while(tmp->n!=NULL) {
            tmp1=tmp->n;
            if(i<tmp1->i) break;
            tmp=tmp->n;
        }
        tmp1=tmp->n;
        tmp->n=lp;
        lp->n=tmp1;
        return;
    }
    if(i<nd->l) INSERT(nd->lt,i);
    else INSERT(nd->rt,i);
}

tnp mtnp(tnp nd,int l,int u) {
    if(nd==NULL) return(NULL);
    if(l<nd->l&&u>nd->u) return(nd);
    if((l>=nd->l&&l<=nd->u)||(u>=nd->l&&u<=nd->u)) return(nd);
    if(l<nd->l&&u<nd->l) return(mtnp(nd->lt,l,u));
    else return(mtnp(nd->rt,l,u));
}

tnp ltnp(tnp nd,int l) {
    if(nd==NULL) return(NULL);
    if(l>nd->u) return(ltnp(nd->rt,l));
    if(l<nd->l) return(ltnp(nd->lt,l));
    return(nd);
}

tnp rtnp(tnp nd,int u) {
    if(nd==NULL) return(NULL);
    if(u>nd->u) return(ltnp(nd->rt,u));
    if(u<nd->l) return(ltnp(nd->lt,u));
    return(nd);
}

llp llip(tnp nd,int l) {
    if(nd==NULL) return(NULL);
    if(l>nd->u) return(llip(nd->rt,l));
    llp ltip,ctip,cttip,lttip;
    if(l<nd->l) ltip=llip(nd->l,l);
    ctip=nd->lst;
    if(ctip==NULL) cttip=NULL;
    else if(ctip->i>l) {
        ctip=nd->lst;
        nd->lst=NULL;
    }
    else {
        while(l<ctip->n->i) ctip=ctip->n;
        cttip=ctip->n;
        ctip->n=NULL;
    }
    if(ltip!=NULL) {
        while(lttip->n!=NULL) lttip=lttip->n;
        lttip->n=ctip;
    }
    ctip=cttip;
    while(cttip->n!=NULL) cttip=cttip->n;
    cttip->n=llip(nd->rt,l);
    if(ltip!=NULL) return(ltip);
    else return(ctip);
}

llp rlip(tnp nd,int l) {
    if(nd==NULL) return(NULL);
    if(l<nd->u) return(llip(nd->lt,l));
    llp ltip,ctip,cttip,lttip;
    if(l>nd->l) ltip=llip(nd->l,l);
    ctip=nd->lst;
    if(ctip==NULL) cttip=NULL;
    else if(ctip->i<l) {
        ctip=nd->lst;
        nd->lst=NULL;
    }
    else {
        cttip=ctip;
        while(l>ctip->n->i) { ctip=ctip->n; if(ctip->n==NULL) break; }
        nd->lst=ctip->n;
        ctip->n=NULL;
    }
    lttip=ltip;
    if(ltip!=NULL) {
        while(lttip->n!=NULL) lttip=lttip->n;
        lttip->n=ctip;
    }
    ctip=cttip;
    while(cttip->n!=NULL) cttip=cttip->n;
    cttip->n=llip(nd->rt,l);
    if(ltip!=NULL) return(ltip);
    else return(ctip);
}

int fnode(tnp nd,tnp nod,tnp *tnd) {
    if(nd->rt==nod) { *tnd=nd; return 1; }
    if(nd->lt==nod) { *tnd=nd; return -1; }
    if(nod->l>nd->u) return(fnode(nd,nod,tnd));
    else return(fnode(nd,nod,tnd));
}

void MERGE(tnp nd,int l,int u) {
    tnp tmp,tmpc,tmpl,tmpr,tmplt,tmprt;
    tmp=(tnp)malloc(sizeof(tn));
    tmp->l=l;
    tmp->u=u;
    tmpc=mtnp(tmp,l,u);
    tmpl=tmpc;
    while(l>tmpl->l) tmpl=tmpl->lt;
    tmpr=tmpc;
    while(u<tmp->u) tmpr=tmpr->rt;
    tmplt=tmplt->lt;
    tmprt=tmprt->rt;
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int l,u,n;
    tnp tree=NULL;
    printf("Enter l, u and n : ");
    scanf("%d %d %d",&l,&u,&n);
    tree=CREATE_INTERVAL_TREE(l,u,n);
    PRETTY_PRINT(tree);
    int i,j,k;
    printf("Enter value of i : ");
    scanf("%d",&i);
    for(j=0;j<i;j++) {
        k=l+rand()%(u-l+1);
        INSERT(tree,k);
    }
    PRETTY_PRINT(tree);
    tnp tnpl,tnpr;
    llp *lipl,*ripl;
    lipl=(llp*)malloc(sizeof(llp));
    ripl=(llp*)malloc(sizeof(llp));
    lipl=llip(tree,8);while(lipl!=NULL) { printf("\n%d\n",lipl->i);lipl=lipl->n; }
    //rlip
    return;
    int m;
    printf("Enter value of m(<n) : ");
    scanf("%d",&m);
    //mergething(tree,m);
    PRETTY_PRINT(tree);
}
