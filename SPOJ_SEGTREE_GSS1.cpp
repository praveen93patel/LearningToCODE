#include<iostream>
#include<cstdio>
using namespace std;

#define INF 202020
typedef long long int lli;

struct node
{
    lli presum;
    lli postsum;
    lli sum;
    lli maxsum;
    void init(lli val)
    {
        presum = val;
        postsum = val;
        sum = val;
        maxsum = val;
    }
    void infinity()
    {
        presum = -INF;
        postsum = -INF;
        sum = -INF;
        maxsum = -INF;
    }
    void mergeChildren(node l, node r)
    {
        presum = max(l.presum, l.sum + r.presum);
        postsum = max(r.postsum, r.sum + l.postsum);
        sum = l.sum + r.sum;
        maxsum = max(l.postsum + r.presum, max(l.maxsum, r.maxsum));
    }
    lli maxRes()
    {
        return maxsum;
    }
};

node Tree[200005];
lli A[50005];

void buildTree(lli si, lli ss, lli se)
{
    if(ss>se)
    {
        Tree[si].infinity();
        return;
    }
    if(ss == se)
    {
        Tree[si].init(A[ss]);
        return;
    }
    lli sm = ss + (se-ss)/2;
    buildTree(2*si, ss, sm);
    buildTree(2*si+1, sm+1, se);
    Tree[si].mergeChildren(Tree[2*si], Tree[2*si+1]);
}

node query(lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>se || ss>qe || se<qs)
    {
        node a;
        a.infinity();
        return a;
    }
    if(ss>=qs && se<=qe)
        return Tree[si];
    lli sm = ss + (se-ss)/2;
    node l = query(2*si, ss, sm, qs, qe);
    node r = query(2*si+1, sm+1, se, qs, qe);
    node res;
    res.mergeChildren(l, r);
    return res;
}

int main()
{
    lli N, Q;
    scanf("%lld", &N);
    for(lli i=1; i<=N; ++i)
        scanf("%lld", &A[i]);
    buildTree(1, 1, N);
    scanf("%lld", &Q);
    lli x, y;
    while(Q--)
    {
        scanf("%lld %lld", &x, &y);
        node res = query(1, 1, N, x, y);
        printf("%lld\n", res.maxRes());
    }
    return 0;
}
