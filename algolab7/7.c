#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct pr {
    int pid;
    int et;
    int pr;
    struct pr *n;
}pr,*prp;

typedef struct rbtn {
    prp val;
    int nul;
    struct rbtn *l;
    struct rbtn *r;
    struct rbtn *p;
    int c;//1 for black and 0 for red
}rbtn,*rbtp;

rbtp lrot(rbtp nd) {
    rbtp tmp,tmp1;
    tmp=nd->r;
    tmp1=tmp->l;
    tmp->l=nd;
    nd->r=tmp1;
    tmp->p=nd->p;
    if(tmp1->nul!=1) tmp1->p=nd;
    nd->p=tmp;
    return(tmp);
}

rbtp rrot(rbtp nd) {
    rbtp tmp,tmp1;
    tmp=nd->l;
    tmp1=tmp->r;
    tmp->r=nd;
    nd->l=tmp1;
    tmp->p=nd->p;
    if(tmp1->nul!=1) tmp1->p=nd;
    nd->p=tmp;
    return(tmp);
}

rbtp find(rbtp nd,prp p) {
    if(nd->nul==1) return(nd);
    rbtp lloc=find(nd->l,p);
    if(p->et==nd->val->et) return(nd);
    else if(p->et<nd->val->et) return(find(nd->l,p));
    else return(find(nd->r,p));
}

void rin(rbtp nd,rbtp nnd) {
    if(nnd->val->et<nd->val->et) {
        if(nd->l->nul==1) {
            nd->l=nnd;
            nnd->p=nd;
            return;
        }
        rin(nd->l,nnd);
    }
    else {
        if(nd->r->nul==1) {
            nd->r=nnd;
            nnd->p=nd;
            return;
        }
        rin(nd->r,nnd);
    }
}

rbtp unc(rbtp nd) {
    rbtp tmp,tmp1;
    tmp=nd->p;
    if(tmp->nul==1) return(tmp);
    tmp1=tmp->p;
    if(tmp1->nul==1) return(tmp1);
    if(tmp1->l==tmp) return(tmp1->r);
    else return(tmp1->l);
}

rbtp insert(rbtp nd,prp p) {
    rbtp loc=find(nd,p);
    if(loc->nul!=1) {
        prp tmp=loc->val;
        while(tmp->n!=NULL) tmp=tmp->n;
        tmp->n=p;
        return(nd);
    }
    rbtp nnd,tmp,tmp1,tmp2;
    nnd=(rbtp)malloc(sizeof(rbtn));
    tmp=(rbtp)malloc(sizeof(rbtn));
    tmp->nul=1;
    tmp->c=1;
    nnd->l=tmp;
    tmp=(rbtp)malloc(sizeof(rbtn));
    tmp->nul=1;
    tmp->c=1;
    nnd->r=tmp;
    tmp=(rbtp)malloc(sizeof(rbtn));
    tmp->nul=1;
    tmp->c=1;
    nnd->p=tmp;
    nnd->nul=0;
    nnd->c=1;
    nnd->val=p;
    if(nd->nul==1) return(nnd);
    nnd->c=0;
    rin(nd,nnd);
    if(nnd->p==nd) return(nd);
    while(nnd->p->nul!=1&&nnd->p->p->nul!=1) {
    if(nnd->p->c==1) return(nd);
    tmp=unc(nnd);
    tmp1=nnd->p->p;
    int uncl,ct;
    if(tmp->nul==1) uncl=1;
    else uncl=tmp->c;
    if(uncl==0) {
        tmp->c=1;
        nnd->p->c=1;
        nnd->p->p->c=0;
        nnd=nnd->p->p;
        continue;
    }
    if(nnd->p->r==nnd&&nnd->p->p->l==nnd->p) {
        tmp1->l=lrot(nnd->p);
        nnd=nnd->l;
    }
    if(nnd->p->l==nnd&&nnd->p->p->l==nnd->p) {
        tmp2=tmp1->p;
        ct=tmp1->c;
        tmp1->c=nnd->p->c;
        nnd->p->c=ct;
        if(tmp2->nul!=1) {
            if(tmp2->l==tmp1) tmp2->l=rrot(tmp1);
            else tmp2->r=rrot(tmp1);
        }
        else return(rrot(tmp1));
        nd->c=1;
        return(nd);

    }
    if(nnd->p->l==nnd&&nnd->p->p->r==nnd->p) {
        tmp1->r=rrot(nnd->p);
        nnd=nnd->r;
    }
    if(nnd->p->r==nnd&&nnd->p->p->r==nnd->p) {
        tmp2=tmp1->p;
        ct=tmp1->c;
        tmp1->c=nnd->p->c;
        nnd->p->c=ct;
        if(tmp2->nul!=1) {
            if(tmp2->l==tmp1) tmp2->l=lrot(tmp1);
            else tmp2->r=lrot(tmp1);
        }
        else return(lrot(tmp1));
        nd->c=1;
        return(nd);
    }
    }
    if(nnd->p->nul==1) nnd->c=1;
    return(nd);
}

rbtp delete(rbtp nd) {
    if(nd->l->nul==1) {
        if(nd->val!=NULL) return(nd);
        nd=nd->r;
        if(nd->nul!=1) { nd->p->nul=1; nd->c=1; }
        return(nd);
    }
    rbtp tmp=nd,tmp1,tmp2;
    while(tmp->l->l->nul!=1) tmp=tmp->l;
    if(tmp->l->val!=NULL) return(nd);
    if(tmp->l->c==0||tmp->c==0) {
        tmp->c=1;
        tmp->l=tmp->l->r;
        return(nd);
    }
    if(tmp->l->r->nul!=1) {
        tmp->l=tmp->l->r;
        tmp->l->c=1;
        return(nd);
    }
    tmp1=tmp->l;
    tmp->l->c=2;
    while(tmp1->c==2||tmp1!=nd) {
        tmp2=tmp->r;
        if(tmp2->c==1&&(tmp2->l->c==0||tmp2->r->c==0)) {
            if(tmp2->r->c==0) {
                tmp1->c=1;

            }
        }
    }
}

int dpt(rbtp nd) {
    if(nd->nul==1) return(0);
    int dl,dr,d;
    dl=dpt(nd->l);
    dr=dpt(nd->r);
    d=dl>dr?dl:dr;
    return(d+1);
}

void inor(rbtp nd) {
    if(nd->nul==1) return;
    inor(nd->l);
    printf("%d  %d  %d\n",dpt(nd),nd->val->et,nd->c);
    inor(nd->r);
}

int main(){
    time_t t;
    srand((unsigned)time(&t));
    int i;
    rbtp tree=NULL,tmp;
    tree=(rbtp)malloc(sizeof(rbtn));
    tree->nul=1;
    tree->c=1;
    prp p;
    for(i=0;i<10;i++) {
        p=(prp)malloc(sizeof(pr));p->n=NULL;
        p->et=rand()%100;
        tree=insert(tree,p);
        inor(tree);printf("\n");
    }printf("Deleting\n");
    /*for(i=0;i<10;i++) {
        tmp=tree;
        while(tmp->l!=NULL) tmp=tmp->l;
        tmp->val=NULL;
        tree=delete(tree);
        inor(tree);printf("\n");
    }*/
}
