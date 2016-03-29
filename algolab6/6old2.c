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
    llp lst[1];
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
    int h=hfinder(nd);
    prtprint(nd,h);
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

tnp fnode(tnp nd,tnp nod) {
    if(nd->rt==nod||nd->lt==nod) return nd;
    if(nod->l>nd->u) return(fnode(nd,nod));
    else return(fnode(nd,nod));
}

lip lmaker(tnp nd) {
    if(nd==NULL) return(NULL);
    lip llip,rlip,clip,tmp;
    clip=(lip)malloc(sizeof(li));
    clip->l=nd->l;
    clip->lst[0]=nd->lst;
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

llp modlist(lip lis,int l,int u) {
    if(lis==NULL) return(NULL);
    llp cllp,tmp,tmp1;
    if(lis->lst[0]==NULL) cllp=NULL;
    else if(l>lis->u||u<lis->l) cllp=NULL;
    else {printf("%d,%d\n",lis->l,lis->u);
        if(lis->lst[0]->i>=l&&lis->lst[0]->i<=u) {
            cllp=lis->lst[0];
            tmp=cllp;
            if(tmp->n==NULL) lis->lst[0]=NULL;
            else {
                while(tmp->n->i<=u) {
                    tmp=tmp->n;
                    if(tmp->n==NULL) break;
                }
                if(tmp->n=NULL) lis->lst[0]=NULL;
                else {
                    lis->lst[0]=tmp->n;
                    tmp->n=NULL;
                }
            }
        }
        else {
            tmp=lis->lst[0];
            if(tmp->n!=NULL)
            while(tmp->n->i>=l&&tmp->n->i<=u) {
                tmp=tmp->n;
                if(tmp->n=NULL) break;
            }
            if(tmp->n=NULL) cllp=NULL;
            else {
                cllp=tmp->n;
                tmp->n=NULL;
            }
            tmp1=cllp;
            if(tmp1!=NULL) {
                if(tmp1->n==NULL) tmp->n=NULL;
                else {
                    while(tmp1->n->i<=u) {
                        tmp1=tmp1->n;
                        if(tmp1==NULL) break;
                    }
                    if(tmp1==NULL) tmp->n=NULL;
                    else {
                        tmp->n=tmp1->n;
                        tmp1->n=NULL;
                    }
                }
            }
        }
    }
    if(cllp!=NULL) {
        tmp=cllp;
        while(tmp->n!=NULL) tmp=tmp->n;
        tmp->n=modlist(lis->n,l,u);
        return(cllp);
    }
    return(modlist(lis->n,l,u));
}

void MERGE(tnp nd,int l,int u) {
    tnp tmp,tmpc,tmpl,tmpr,tmplt,tmprt;
    tmp=(tnp)malloc(sizeof(tn));
    tmp->l=l;
    tmp->u=u;
    tmpc=mtnp(tmp,l,u);
    lip list=lmaker(tmpc);
    modlist(list,l,u);

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
    lip list=lmaker(tree);llp lst;
    llp mlist=modlist(list,35,65);
    while(mlist!=NULL) {printf("\n%d\n",mlist->i);mlist=mlist->n;}
    PRETTY_PRINT(tree);
    return;
    int m;
    printf("Enter value of m(<n) : ");
    scanf("%d",&m);
    //mergething(tree,m);
    PRETTY_PRINT(tree);
}
