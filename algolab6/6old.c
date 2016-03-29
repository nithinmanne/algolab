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
};

typedef struct node2 {
    int l;
    int u;
    llp lst;
    struct node2 *lt;
    struct node2 *rt;
}tn,*tnp;

tnp CREATE_INTERVAL_TREE(int l,int u,int n) {
    if(n==0) return(NULL);
    tnp nd;
    nd=(tnp)malloc(sizeof(tn));
    int s,r,l1,u1,ls,rs;
    float ch;
    s=(u-l+1)/n;
    r=(u-l+1)%n;
    l1=l+s*(n/2);
    u1=l1+s-1+((r>0)?1:0);
    ls=n/2;
    rs=n-ls-1;
    nd->l=l1;
    nd->u=u1;
    nd->lst=NULL;
    nd->lt=CREATE_INTERVAL_TREE(l,l1-1,ls);
    nd->rt=CREATE_INTERVAL_TREE(u1+1,u,rs);
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
    printf("\n");
    PRETTY_PRINT(nd->rt);
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int l,u,n;
    tnp tree=NULL;
    printf("Enter l, u and n : ");
    scanf("%d %d %d",&l,&u,&n);
    tree=CREATE_INTERVAL_TREE(l,u,n);
    PRETTY_PRINT(tree);return;
    int i,j,k;
    printf("Enter value of i : ");
    scanf("%d",&i);
    for(j=0;j<i;j++) {
        k=l+rand()%(u-l+1);
        //INSERT(tree,k);
    }
    PRETTY_PRINT(tree);
    int m;
    printf("Enter value of m(<n) : ");
    scanf("%d",&m);
    //mergething(tree,m);
    PRETTY_PRINT(tree);
}
