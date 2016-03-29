#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//Taking both sides as tight bounds
typedef struct node1 {
    int i;
    struct node1 *n;
}ll,*llp,*llpp;

typedef struct nose12 {
    int l;
    int u;
    llp lst;
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
    prtprint(nd,hfinder(nd));
}

void prtprint(tnp nd,int h) {
    if(nd==NULL) return;
    prtprint(nd->lt,h-1);
    int i;
    llp tl;
    for(i=h;i>1;i--) printf("   ");
    printf("[%d,%d] ",nd->l,nd->u);
    tl=nd->lst;
    if(tl==NULL) printf("........  ");
    else { while(tl!=NULL) { printf("%d, ",tl->i); tl=tl->n; } }
    printf("\b\b \n");
    prtprint(nd->rt,h-1);
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

tnp fnode(tnp nd,tnp nod) {
    if(nd==nod) return(NULL);
    if(nd->rt->l==nod->l||nd->lt->l==nod->l) return nd;
    if(nod->l>nd->u) return(fnode(nd->rt,nod));
    else return(fnode(nd->lt,nod));
}

lip lmaker(tnp nd) {
    if(nd==NULL) return(NULL);
    lip llip,rlip,clip,tmp;
    clip=(lip)malloc(sizeof(li));
    clip->l=nd->l;
    clip->lst=nd->lst;
    clip->u=nd->u;
    llip=lmaker(nd->lt);
    tmp=llip;
    if(llip!=NULL) {
        while(llip->n!=NULL) llip=llip->n;
        llip->n=clip;
    }
    rlip=lmaker(nd->rt);
    clip->n=rlip;
    if(tmp==NULL) return(clip);
    return(tmp);
}

llp getlist(lip lis) {
    if(lis==NULL) return(NULL);
    llp vlist,tmp;
    vlist=lis->lst;
    if(vlist==NULL) return(getlist(lis->n));
    tmp=vlist;
    while(vlist->n!=NULL) vlist=vlist->n;
    vlist->n=getlist(lis->n);
    return(tmp);
}

tnp MERGE(tnp nd,int l,int u) {
    tnp ntmp,tmpc,tmpl,tmpr,tmplt,tmprt;
    ntmp=(tnp)malloc(sizeof(tn));
    ntmp->l=l;
    ntmp->u=u;
    tmpc=mtnp(nd,l,u);
    lip list=lmaker(tmpc);
    llp vlist=getlist(list);
    llp nlist,olist,tmp;
    /*if(vlist==NULL) { nlist=NULL; olist=NULL; }
    else {
        if(vlist->i>l) nlist=vlist;
        else {
            olist=vlist;
            if(vlist->n==NULL) nlist=NULL;
            else {
                while(vlist->n->i<l) {
                    vlist=vlist->n;
                    if(vlist->n==NULL) break;
                }
                nlist=vlist->n;
                vlist->n=NULL;
                vlist=nlist;
            }
        }
        if(vlist!=NULL) {
            if(vlist->n!=NULL) {
                while(vlist->n->i<=u) {
                    vlist=vlist->n;
                    if(vlist->n==NULL) break;
                }
                if(olist!=NULL) {
                    tmp=olist;
                    while(tmp->n!=NULL) tmp=tmp->n;
                    tmp->n=vlist->n;
                    vlist->n=NULL;
                }
                else {
                    olist=vlist;
                }
            }
        }
    }
    ntmp->lst=nlist;*/
    ntmp->lst=NULL;
    lip llist=list,rlist,tmplist=list;
    while(tmplist->u<l) tmplist=tmplist->n;
    tmplist->u=l-1;
    list=tmplist->n;
    tmplist->n=NULL;
    tmplist=list;
    if(tmplist!=NULL) {
    while(tmplist->u<u) { tmplist=tmplist->n; if(tmplist==NULL) break; }
    rlist=tmplist;
    if(tmplist!=NULL) tmplist->l=u+1;}
    else rlist=NULL;
    ntmp->lt=mktree(llist);
    ntmp->rt=mktree(rlist);
    int i=0;
    /*llp temmp=olist;
    if(olist!=NULL) for(i=0;i<10010;i++) {temmp=temmp->n;if(temmp==NULL) break;}
    if(temmp!=NULL) temmp->n=NULL;
    while(olist!=NULL) { INSERT(ntmp,olist->i); olist=olist->n; }*/
    tnp prev=fnode(nd,tmpc);
    if(prev==NULL) return(ntmp);
    if(prev->lt==tmpc) prev->lt=ntmp;
    else prev->rt=ntmp;
    return(nd);
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
    int m;
    printf("Enter value of m(<n) : ");
    scanf("%d",&m);
    int sz,re;
    sz=(u-l+1)/m;
    re=(u-l+1)/m;
    lip ip,tmp,tmp1;
    ip=(lip)malloc(sizeof(li));
    ip->l=l;
    ip->u=l+sz-1+((re>0)?1:0);
    re--;
    tmp=ip;
    for(i=1;i<m;i++) {
        tmp1=(lip)malloc(sizeof(li));
        tmp1->l=tmp->u+1;
        tmp1->u=tmp1->l+sz-1+((re>0)?1:0);
        re--;
        tmp->n=tmp1;
        tmp=tmp1;
    }
    tmp->n=NULL;
    while(ip!=NULL) {
        tree=MERGE(tree,ip->l,ip->u);
        ip=ip->n;
    }
    PRETTY_PRINT(tree);
}
