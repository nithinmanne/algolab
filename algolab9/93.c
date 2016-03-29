#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct node{
int key,degree,mark;
struct node *child,*sibr,*sibl,*parent;
}fbtree,*fbtreeptr;

typedef struct lnode{
    fbtreeptr min;
fbtreeptr x,last;
}list;

typedef struct Y{
int key;
struct Y *next;
}list1;
list* makeheap(){
    list *H;
    H=(list*)malloc(sizeof(list));
H->x=NULL;H->min=NULL;H->last=NULL;
return H;
}

list* insertheap( list *H, fbtreeptr T){
    if(H->x==NULL){H->x=T;H->min=T;T->sibr=NULL;T->sibl=NULL;H->last=T;return H;}
T->sibr=H->x;H->x->sibl=T;
H->x=T;T->sibl=NULL;
if(H->min->key>T->key)H->min=T;
return H;
}
void decheapkey(list *H,fbtreeptr x,int k){
    fbtreeptr temp;
    temp=x;
    x->key=k;
    if(x->parent==NULL){if(H->min->key>x->key)H->min=x;
    return;
    }
    if( x->key<x->parent->key){
                if(H->min->key>x->key)H->min=x;
        H=insertheap(H,temp);temp->mark=0;
    while(temp->parent!=NULL){
            temp->parent->mark+=1;

            if(temp->sibl==NULL){
                temp->parent->child=temp->sibr;
            }
            else{
                temp->sibl->sibr=temp->sibr;
                temp->sibr->sibl=temp->sibl;
            }

            if(temp->parent->mark>=2){temp=temp->parent;temp->degree--;if(temp->parent==NULL)temp->mark=0;}
            else break;
    }
    }
    return ;
}


fbtreeptr check(fbtreeptr T,list* H){
    fbtreeptr X,extra,temp;
    X=T;
while(X->sibr!=NULL){
    if(X->degree==X->sibr->degree){
        if(X->key<X->sibr->key){
          extra=(fbtreeptr)malloc(sizeof(fbtree));
          extra->key=X->sibr->key;extra->degree=X->sibr->degree;extra->parent=NULL;
          extra->sibl=NULL;extra->sibr=NULL;
          temp=X->sibr;
    if(temp->sibr!=NULL) {    X->sibr=temp->sibr;
          temp->sibr->sibl=X;}else X->sibr=NULL;
          extra->sibr=X->child;X->child=extra;
          X->degree++;

        }
        else {printf("cccc\n");
         extra=(fbtreeptr)malloc(sizeof(fbtree));
         extra->key=X->key;extra->degree=X->degree;extra->parent=NULL;
         extra->sibl=NULL;extra->sibr=NULL;
         temp=X;
    if(temp->sibl!=NULL) {    X->sibr->sibl=temp->sibl;
          temp->sibl->sibr=X->sibr;}else {X->sibr->sibl=NULL;}
          extra->sibr=X->sibr->child;X->sibr->child=extra;
          X->sibr->degree++;
            X=X->sibr;
            if(X->sibl==NULL)H->x=X;
        }
    }
    else break;
}
H->last=X;
return T;
}


list* collapse (list* H){
    int flag;
list* p;
fbtreeptr temp,extra,add;
if(H->x==NULL)return H;
p=(list*)malloc(sizeof(list));
p->x=NULL;p->min=NULL;
    p->x=H->x;H->x=H->x->sibr;H->x->sibl=NULL;
    p->x->sibr=NULL;p->x->sibl=NULL;p->last=p->x;p->min=p->x;
    printf("@@@@@@@@@@@@%d@@@\n",p->x->key);

while(H->x!=NULL){
        printf("@@@@@@@@@@@@%d@@@---%d\n",p->x->key,H->x->key);

        flag=0;
        add=(fbtreeptr)malloc(sizeof(fbtree));
        add->key=H->x->key;add->sibr=NULL;add->sibl=NULL;add->degree=H->x->degree;add->parent=NULL;
        H->x=H->x->sibr;if(H->x!=NULL){H->x->sibl=NULL;}
        temp=p->x;
        if(add->degree<temp->degree){
                if(p->min->key>add->key)p->min=add;
                flag=1;
                add->sibr=p->x;p->x->sibl=add;
            p->x=add;add->sibl=NULL;
        }
        else if(add->degree==temp->degree){printf("AAAA\n");
            flag=1;
               extra=(fbtreeptr)malloc(sizeof(fbtree));
            if(temp->key<add->key){
                extra=add;
     if(temp->child!=NULL)extra->sibr=temp->child;else extra->sibr=NULL;temp->child=extra;
        temp->degree++;
        temp=check(temp,p);
            }
            else{ printf("BBBB\n");
                    if(p->min->key>add->key)p->min=add;
extra->key=temp->key;printf("QQQQQQQ%d\n",extra->key);
extra->degree=temp->degree;extra->parent=NULL;extra->sibr=NULL;extra->sibl=NULL;
add->sibr=temp->sibr;add->sibl=temp->sibl;
add->sibr->sibl=add;if(add->sibl!=NULL)add->sibl->sibr=add;else p->x=add;
if(add->child!=NULL)extra->sibr=add->child;else extra->sibr=NULL;add->child=extra;
add->degree++;
if(p->last==temp){p->last=add;}
     add=check(add,p);
            }
        }

   temp=p->x;
   while(temp->sibr!=NULL  && flag!=1 ) {
    if(add->degree<temp->sibr->degree){
            flag=1;
            if(p->min->key>add->key)p->min=add;
            add->sibr=temp->sibr;temp->sibr->sibl=add;
            temp->sibr=add;add->sibl=temp;
    }
    else if(add->degree==temp->sibr->degree){
        flag=1;
            extra=(fbtreeptr)malloc(sizeof(fbtree));
                if(temp->sibr->key<H->x->key){
                extra=add;if(temp->sibr->child!=NULL)extra->sibr=temp->sibr->child;else extra->sibr=NULL;temp->sibr->child=extra;
        temp->sibr->degree++;
    temp->sibr=check(temp->sibr,p);
            }
                        else{
                                if(p->min->key>add->key)p->min=add;
extra->key=temp->sibr->key;extra->degree=temp->sibr->degree;extra->parent=NULL;
extra->sibr=NULL;extra->sibl=NULL;

if(temp->sibr->sibr!=NULL)add->sibr=temp->sibr->sibr;else add->sibr=NULL;add->sibl=temp;
add->sibr->sibl=add;if(add->sibl!=NULL)add->sibl->sibr=add;
extra->sibr=add->child;add->child=extra;
add->degree++;
if(p->last==temp){p->last=add;}
         add=check(add,p);

            }
    }
   }
   if(flag==0){
    temp->sibr=add;add->sibl=temp;add->sibr=NULL;
if(p->last==temp){p->last=add;}
   }

}
return  p;
}






list* extractmin(list *H){
    fbtreeptr temp,temp2;int loop=5;
    if(H->min==NULL)return H;

    if(H->min->child!=NULL){temp2=H->min->child->sibr;
       H= insertheap(H,H->min->child);
       }
while(temp2!=NULL){ temp=temp2;       printf("PQRS----%d\n",temp->key);
printf("ZZZZZ\n");
if(temp2->sibr!=NULL)temp2=temp2->sibr;else break;
printf("AAAAAA\n");
   H= insertheap(H,temp);
   printf("BBBBBB\n");
}
H->min->child=NULL;
    }


    if(H->x->key==H->min->key){
    H->x=H->x->sibr;
    H->x->sibl=NULL;
}
else {
    temp=H->min->sibl;
    temp->sibr=H->min->sibr;
    H->min->sibr->sibl=temp;
}
printf("XXXX%dXXXX\n",H->min->key);
H=collapse(H);
printf("XXXX%dXXXX\n",H->min->key);

return H;
}

list *merge (list *H1,list* H2){
if(H1->x!=NULL)H1->last->sibr=H2->x;
if(H2->x!=NULL)H2->x->sibl=H1->last;
if(H2->min->key<H1->min->key)H1->min=H2->min;
H1->last=H2->last;
return H1;
}
int generate(int **A,int x,int y,int k,int m,int *p){
int rdm,i,j;
rdm=rand()%10000;
for(i=0;i<=x;i++){
    for(j=0;j<=p[i]*m;j++){
        if(i==x && j==y)break;
        else {
            if(rdm==A[i][j])rdm=generate(A,x,y,k,m,p);
        }
    }
}
return rdm;
}
int main(){
    int **A,k,m,i,j,*p;
    list **H,*main,*duplist;
    list1 *out,*local;
    fbtreeptr temp,newnode;
    printf("Enter The no:of lists and no:of elements in each block:");
    scanf("%d %d",&k,&m);
    A=(int **)malloc(k*sizeof(int *));
    p=(int *)malloc(k*sizeof(int ));
    H=(list **)malloc(k*sizeof(list*));
    out=(list1 *)malloc(sizeof(list1));
    for(i=0;i<k;i++){
            p[i]=rand()%2+2;
    A[i]=(int *)malloc(p[i]*m*sizeof(int));
    H[i]=makeheap();
        for(j=0;j<p[i]*m;j++){
                    newnode=(fbtreeptr)malloc(m*sizeof(fbtree));
           A[i][j]=generate(A,i,j,k,m,p);
           newnode->key=A[i][j];newnode->degree=0;newnode->mark=0;
           newnode->child=NULL;newnode->sibr=NULL;newnode->sibl=NULL;newnode->parent=NULL;
          H[i]= insertheap(H[i],newnode);

        }
    }
    for(i=0;i<k;i++){
        temp=H[i]->x;
        while(temp!=NULL){printf("%d\t",temp->key);temp=temp->sibr;}
        printf("\n\n\n");
    }
main=(list *)malloc(k*sizeof(list));
printf("\n\n\n\n");
main=H[0];
for(i=1;i<k;i++){
    main=merge(main,H[i]);
}
    printf("\n\n\n\n");
        temp=main->x;
        while(temp!=NULL){printf("%d\t",temp->key);temp=temp->sibr;}

local=out;duplist=main;temp=duplist->min;
while(temp!=NULL){
    local->key=temp->key;
    local->next=(list1*)malloc(sizeof(list1));
    local=local->next;
    printf("\nABCD\n");duplist=extractmin(duplist);printf("\nABCD1\n");
    temp=duplist->min;
    if(duplist->min!=NULL){printf("--%d---%d",duplist->x->key,duplist->min->key);}
}
local->next=NULL;
return 0;
}
