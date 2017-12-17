#include<cstdio>
#include<iostream>
using namespace std;

#define MAXN 100005

struct node
{
    int distinct;
    node *left, *right;
    node() :
        distinct(0), left(NULL), right(NULL) {}
} all[20000000];
int tot;

typedef node * pnode;

pnode root[MAXN];
int A[MAXN], prevOcc[MAXN];
int N, i, k;

pnode update(pnode t, int idx, int val, int l, int r)
{
    if(l>r)
        return NULL;
    pnode res = &all[tot++];
    res->distinct = t->distinct+val;
    res->left = t->left;
    res->right = t->right;
    if(l<r)
    {
        int m = l+(r-l)/2;
        if(idx<=m)
            res->left = update(t->left, idx, val, l, m);
        else
            res->right = update(t->right, idx, val, m+1, r);
    }
    return res;
}

int kDistinct(pnode t, int k, int l, int r)
{
    if(l>=r)
        return r;
    int m = l+(r-l)/2;
    int c = t->left->distinct;
  //  printf("%d : %d : %d : %d : %d\n", l, m, r, c, k);
    if(c>=k)
        return kDistinct(t->left, k, l, m);
    else
        return kDistinct(t->right, k-c, m+1, r);
}

int ans(int k)
{
    int _ans=0;
    int l, r;
    l=1;
    while(l<=N)
    {
        _ans++;
        r = kDistinct(root[l], k+1, 1, N+1);
        l = r;
       // printf("%d %d %d\n", k, _ans, l);
    }
    return _ans;
}

void printTree(pnode t, int l, int r)
{
    if(l==r)
    {
        printf("%d ", t->distinct);
        return;
    }
    printTree(t->left, l, (l+r)/2);
    printTree(t->right, 1+(l+r)/2, r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    scanf("%d", &N);
    for(i=1;i<=N;++i)
        scanf("%d", &A[i]);

    root[N+1] = &all[tot++];
    root[N+1]->left = root[N+1]->right = root[N+1];

    for(i=N; i>0; --i)
    {
        root[i] = update(root[i+1], i, 1, 1, N+1);
        if(prevOcc[A[i]])
            root[i] = update(root[i], prevOcc[A[i]], -1, 1, N+1);
        prevOcc[A[i]] = i;
    }
    int test = 1;

   // printTree(root[1], 1, N+1);

    for(k=1; k<=N; ++k)
    {
       // printf("Test%d: ", test++);
        printf("%d ", ans(k));
       // printf("\n");
    }
    printf("\n");
    return 0;
}
