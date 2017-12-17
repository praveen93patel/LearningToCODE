#include<iostream>
#include<cstdio>
using namespace std;

typedef long long ll;

#define MAXN 100005

ll an = 1e9 + 9;

struct node
{
    ll sum;
    node *left, *right;
    node() : sum(0), left(NULL), right(NULL) {}
} all[20000000];
ll tot;

typedef node * pnode;

pnode root[MAXN];
ll N, M, A, L, R;

//pnode null = &all[tot++];

pnode update(pnode t, ll val, ll l, ll r)
{
    if(l>r)
        return NULL;
    pnode ret = &all[tot++];
    ret->sum = t->sum + val;
    ret->left = t->left;
    ret->right = t->right;
    if(l==r)
        return ret;
    ll m = l+(r-l)/2;
    if(val<=m)
        ret->left = update(t->left, val, l, m);
    else
        ret->right = update(t->right, val, m+1, r);
    return ret;
}

ll SumLessThan(pnode low, pnode high, ll val, ll l, ll r)
{
    if(l>=r)
        return 0;
    ll m = l+(r-l)/2;
    ll sum = high->left->sum - low->left->sum;
//    if(l==r)
//        return sum;
    if(val<m)
        return SumLessThan(low->left, high->left, val, l, m);
    else
        return sum + SumLessThan(low->right, high->right, val, m+1, r);
}

ll ForbiddenSum(ll L, ll R)
{
    ll S = 0;
    ll newS;
    while(true)
    {
        newS = SumLessThan(root[L-1], root[R], S+1, 1, an);
        if(newS==S)
            break;
        S = newS;
    }
    return S+1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    scanf("%lld", &N);

    root[0] = &all[tot++];
    root[0]->left = root[0]->right = root[0];
   // null->left = null->right = null;

    for(int i=1; i<=N; ++i)
    {
        scanf("%lld", &A);
        root[i] = update(root[i-1], A, 1, an);
    }

    scanf("%lld", &M);
    for(int i=1; i<=M; ++i)
    {
        scanf("%lld%lld", &L, &R);
        printf("%lld\n", ForbiddenSum(L, R));
    }
    return 0;
}
