#include<cstdio>
using namespace std;

#define MAXN 1000006

struct node
{
    int distinct;
    node *left, *right;
    node() : distinct(0), left(NULL), right(NULL) {}
} all[20000000];
int tot;

typedef node * pnode;

pnode root[MAXN];
int A[MAXN], prevOcc[MAXN], n, i, q, l, r, ans;

pnode update(pnode t, int idx, int val, int l, int r)
{
    if(l>r)
        return NULL;
    pnode ret = &all[tot++];
    ret->left = t->left;
    ret->right = t->right;
    ret->distinct = t->distinct + val;
    if(l<r)
    {
        int m = (l+r)>>1;
        if(idx<=m)
            ret->left = update(t->left, idx, val, l, m);
        else
            ret->right = update(t->right, idx, val, m+1, r);
    }
    return ret;
}

int query(pnode s, int x, int y, int l, int r)
{
    if(x>r || y<l || l>r)
        return 0;
    if(x<=l && y>=r)
        return s->distinct;
    int m = (l+r)>>1;
    return query(s->left, x, y, l, m) + query(s->right, x, y, m+1, r);
}

int main()
{
    scanf("%d", &n);
    for(i=1;i<=n;++i)
        scanf("%d", &A[i]);
    root[0] = &all[tot++];
    root[0]->left = root[0]->right = root[0];
    for(i=1;i<=n;++i)
    {
        root[i] = update(root[i-1], i, 1, 1, n);
        if(prevOcc[A[i]])
            root[i] = update(root[i], prevOcc[A[i]], -1, 1, n);
        prevOcc[A[i]] = i;
    }
    scanf("%d", &q);
    for(i=1; i<=q; ++i)
    {
        scanf("%d%d", &l, &r);
        ans = query(root[r], l, r, 1, n);
        printf("%d\n", ans);
    }
    return 0;
}
