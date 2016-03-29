#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct pr {
    int pid;
    int ct;
    int et;
    int pr;
    struct pr *n;
}pr,*prp;

typedef struct rbtn {
    prp val;
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
    if(tmp1!=NULL) tmp1->p=nd;
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
    if(tmp1!=NULL) tmp1->p=nd;
    nd->p=tmp;
    return(tmp);
}

rbtp find(rbtp nd,prp p) {
    if(nd==NULL) return(NULL);
    rbtp lloc=find(nd->l,p);
    if(p->et==nd->val->et) return(nd);
    else if(p->et<nd->val->et) return(find(nd->l,p));
    else return(find(nd->r,p));
}

void rin(rbtp nd,rbtp nnd) {
    if(nnd->val->et<nd->val->et) {
        if(nd->l==NULL) {
            nd->l=nnd;
            nnd->p=nd;
            return;
        }
        rin(nd->l,nnd);
    }
    else {
        if(nd->r==NULL) {
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
    if(tmp==NULL) return(NULL);
    tmp1=tmp->p;
    if(tmp1==NULL) return(NULL);
    if(tmp1->l==tmp) return(tmp1->r);
    else return(tmp1->l);
}

rbtp insert(rbtp nd,prp p) {
    rbtp loc=find(nd,p);
    if(loc!=NULL) {
        prp tmp=loc->val;
        while(tmp->n!=NULL) tmp=tmp->n;
        tmp->n=p;
        return(nd);
    }
    rbtp nnd,tmp,tmp1,tmp2;
    nnd=(rbtp)malloc(sizeof(rbtn));
    nnd->l=nnd->r=nnd->p=NULL;
    nnd->c=1;
    nnd->val=p;
    if(nd==NULL) return(nnd);
    nnd->c=0;
    rin(nd,nnd);
    if(nnd->p==nd) return(nd);
    while(nnd->p!=NULL&&nnd->p->p!=NULL) {
    if(nnd->p->c==1) return(nd);
    tmp=unc(nnd);
    tmp1=nnd->p->p;
    int uncl,ct;
    if(tmp==NULL) uncl=1;
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
        if(tmp2!=NULL) {
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
        if(tmp2!=NULL) {
            if(tmp2->l==tmp1) tmp2->l=lrot(tmp1);
            else tmp2->r=lrot(tmp1);
        }
        else return(lrot(tmp1));
        nd->c=1;
        return(nd);
    }
    }
    if(nnd->p==NULL) nnd->c=1;
    return(nd);
}

int dpt(rbtp nd) {
    if(nd==NULL) return(0);
    int dl,dr,d;
    dl=dpt(nd->l);
    dr=dpt(nd->r);
    d=dl>dr?dl:dr;
    return(d+1);
}

prp flush(rbtp nd) {
    if(nd==NULL) return(NULL);
    prp pl,pr,pc,temp;
    pl=flush(nd->l);
    temp=pl;
    if(temp!=NULL) while(temp->n!=NULL) temp=temp->n;
    pc=nd->val;
    if(temp!=NULL) temp->n=pc;
    while(pc->n!=NULL) pc=pc->n;
    pr=flush(nd->r);
    pc->n=pr;
    if(pl==NULL) return(pc);
    return(pl);
}

int main(){
  FILE *fil;
  fil=fopen("scheduler.txt","w");
    time_t t;
    srand((unsigned)time(&t));
    int N,M;
    fprintf(fil,"Process ID\tCreation Time\tPriority\tScheduled\tPre-empted\tExecuted Completely\n");
    printf("Enter value of N : ");
    scanf("%d",&N);
    printf("Enter value of M : ");
    scanf("%d",&M);
    int i,tim=0,pid=0,m=0,n=0;
    rbtp tree=NULL,tmp;
    prp p,l,s;
    while(m<M) {
        if(n<N) {
            p=(prp)malloc(sizeof(pr));
            p->pid=pid;
            pid++;
            p->ct=tim;
            p->et=1+rand()%1000;
            p->pr=1+rand()%4;
            p->n=NULL;
            tree=insert(tree,p);
            n++;
        }
        l=flush(tree);
        tree=NULL;
        s=l;
        l=l->n;
        s->n=NULL;
        fprintf(fil,"%d\t\t%d\t\t%d\t\t%d\t\t",s->pid,s->ct,s->pr,tim);
        if(s->pr*50>s->et) {
            tim=tim+s->et;
            s=NULL;
            fprintf(fil,"N/A\t\t%d\n",tim);
            m++;
            n--;
        }
        else {
            tim=tim+s->pr*50;
            s->et=s->et-s->pr*50;
            fprintf(fil,"%d\t\tN/A\n",tim);
        }
        tree=NULL;
        if(s!=NULL) tree=insert(tree,s);
        while(l!=NULL) { s=l->n; l->n=NULL; tree=insert(tree,l); l=s; }
    }
}
