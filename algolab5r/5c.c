#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct tree{
int key;
struct tree *lchild,*rchild;
}bintree,*bintreeptr;
typedef struct node{
int key;
struct node *x;}_Node;

typedef struct node2{
int key;
struct node2 *next,*prev;}_Node2;
void validate(bintreeptr T,int *A,int k);
void generate (bintreeptr T,int n,int *A, int k){
    int m;
    float p;
    T->lchild=(bintreeptr)malloc(sizeof(bintree));
    T->rchild=(bintreeptr)malloc(sizeof(bintree));
    p=(400.0+rand()%201)/1000.0;
    m=p*n;
    if(n==0){T=NULL;return;}
    if(n==1){validate(T,A,k);
    k++;
    T->lchild=NULL;
    T->rchild=NULL;
    return;
    }
    else if(n==2){
            validate(T,A,k);
            k++;
    generate(T->lchild,1,A,k);
    T->rchild=NULL;
    return;
    }
    validate(T,A,k);
    k++;
    generate(T->lchild,m,A,k);
    generate(T->rchild,n-m-1,A,k+m);
    return;
}

void validate(bintreeptr T,int *A,int k){
    int i,p;
    p=-10+rand()%20;

    T->key=p;
    if(k==0){A[k]=T->key;return;}
    for(i=0;i<k;i++){
        if(T->key==A[i]){
            T->key=-10+rand()%20;
            validate(T,A,k);return;
        }
    }
    A[k]=T->key;
    return;
}
void inorder (bintreeptr T)
{if(T==NULL){printf("Error");return;}
if(T->lchild!=NULL)inorder(T->lchild);
printf("%d ",T->key);
if(T->rchild!=NULL)inorder(T->rchild);
return;
}
void preorder (bintreeptr T)
{if(T==NULL){printf("Error");return;}
    printf("%d ",T->key);
if(T->lchild!=NULL)preorder(T->lchild);
if(T->rchild!=NULL)preorder(T->rchild);
return;
}
void postorder (bintreeptr T)
{if(T==NULL){printf("Error");return;}
if(T->lchild!=NULL)postorder(T->lchild);
if(T->rchild!=NULL)postorder(T->rchild);
printf("%d ",T->key);
return;
}
int maxsum(bintreeptr T,_Node *h){
    _Node *h1,*h2;
    h1=(_Node *)malloc(sizeof(_Node));
    h2=(_Node *)malloc(sizeof(_Node));
    if(T==NULL){return 0;h=NULL;}
    else if(T->rchild==NULL && T->lchild==NULL){h->key=T->key;h->x=NULL;return T->key;}
    else if(T->rchild==NULL ){h->key=T->key;
    h->x=h1;
    return(T->key+maxsum(T->lchild,h1));}
    else if(T->lchild==NULL ){ h->key=T->key;h->x=h2;return(T->key+maxsum(T->rchild,h2));}

    if(maxsum(T->lchild,h1)>=maxsum(T->rchild,h2)){
            h->key=T->key;h->x=h1;
        return (T->key+maxsum(T->lchild,h1));
    }
    else if(maxsum(T->lchild,h1)<maxsum(T->rchild,h2)){
        h->key=T->key;h->x=h2;
        return (T->key+maxsum(T->rchild,h2));
    }
}
int maxpath(bintreeptr T,_Node2 **Y,int *big,int *A,int *n){
    if(T==NULL){*Y=NULL;return 0;}
int p,q;printf("loooop %d  %d\n",*big,T->key);
_Node2 **Y1t,**Y2t,*Y1,*Y2,*M,*Temp;
if(T==NULL){*Y=NULL;return 0;}
Y=(_Node2**)malloc(sizeof(_Node2*));
M=(_Node2*)malloc(sizeof(_Node2));
p=maxpath(T->lchild,Y1t,big,A,n);
q=maxpath(T->rchild,Y2t,big,A,n);
Y1=*Y1t; Y2=*Y2t;
M->key=T->key;
if(p+q+T->key>*big && p>0 && q>0){
    *big=p+q+T->key;*n=0;Temp=Y1;
    while(Y1->next!=NULL)Y1=Y1->next;
    while(Y1!=NULL){
        A[*n]=Y1->key;(*n)++;
        Y1=Y1->prev;
    }
    Y1=Temp;
    A[*n]=T->key;(*n)++;
    Temp=Y2;
    while(Y2!=NULL){
        A[*n]=Y2->key;(*n)++;
        Y2=Y2->next;
    }
    Y2=Temp;}
    else if (p+T->key>*big && p>0)
    {
        *big=p+T->key;*n=0;Temp=Y1;
        while(Y1->next!=NULL)Y1=Y1->next;
    while(Y1!=NULL){
        A[*n]=Y1->key;(*n)++;
        Y1=Y1->prev;
    }
    Y1=Temp;
    A[*n]=T->key;(*n)++;}
    else if(q +T->key >*big && q>0){

        *big=q+T->key;*n=0;
         A[*n]=M->key;(*n)++;
             Temp=Y2;
    while(Y2!=NULL){
        A[*n]=Y2->key;(*n)++;
        Y2=Y2->next;
    }
    Y2=Temp;

    }
    else if(T->key>*big){
            *big=T->key;*n=0;
        A[*n]=M->key;(*n)++;
    }

    if(p>q && p>0)
    {
        M->prev=NULL;
        M->next=Y1;
        if(Y1!=NULL)Y1->prev=M;
        *Y=M;
        return p+T->key;
    }
    else if(q>p && q>0)
    {
        M->prev=NULL;
        M->next=Y2;
        if(Y2!=NULL)Y2->prev=M;
        *Y=M;
        return q+T->key;
    }
    else{
        M->next=NULL;M->prev=NULL;*Y=M;
        return T->key;
    }
}

int main(){
    int n,i,k,*A,*B,*big,temp,*size;
    bintreeptr T;
    _Node *h,*p,**y,*j,*k1;
    _Node2 *p0,*q0;
    printf("Enter the number of nodes in the Binary Tree:");
    scanf("%d",&n);
    A=(int*)malloc(n*sizeof(int));
    size=(int*)malloc(sizeof(int));
    B=(int*)malloc(100*sizeof(int));
    h=(_Node *)malloc(sizeof(_Node));
    p=(_Node *)malloc(sizeof(_Node));
    T=(bintreeptr)malloc(sizeof(bintree));
    big=(int *)malloc(sizeof(int));
    k=0;
    generate(T,n,A,k);
        printf("\ninorder\n");
        inorder(T);
                printf("\npreorder\n");
                preorder(T);
                printf("\npostorder\n");
                postorder(T);
                printf("\n------\n");
 printf("The maxSum of the binary tree is :%d\n",maxsum(T,h));
 printf("The path of maxsum from root to leaf is:\n");
 p=h;
 while(p!=NULL){
        printf("%d,",p->key);
        p=p->x;
 }
  *big=-1001;
  printf("\n-----------------------------------------------------------------\n");
   temp=maxpath(T,y,big,B,size);
  printf("The total maximum sum in the complete binary tree is :%d_%d",*big,*size);

  for(i=0;i<*size;i++){
    printf("%d ",B[i]);
  }


return 0;
}



