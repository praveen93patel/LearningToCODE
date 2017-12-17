#include<iostream>
#include<cstdio>
using namespace std;

typedef long long int lli;

#define INF 202020

struct node
{
    lli presum, postsum, sum, maxsum;

    void init(lli val)
    {
        presum = postsum = sum = maxsum = val;
    }
    void identity()
    {
        presum = postsum = sum = maxsum = -INF;
    }
    void mergeC(node &l, node &r)
    {
        presum = max(l.presum, l.sum+r.presum);
        postsum = max(r.postsum, l.postsum+r.sum);
        sum = l.sum + r.sum;
        maxsum = max(l.postsum+r.presum, max(l.maxsum, r.maxsum));
    }
    void splitC(node &l, node &r)
    {
    }
    lli maxSum()
    {
        return maxsum;
    }
};

node Tree[200005];
lli A[50004];

void buildTree(lli si, lli ss, lli se)
{
    if(ss==se)
    {
        Tree[si].init(A[ss]);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    buildTree(lc, ss, sm);
    buildTree(rc, sm+1, se);
    Tree[si].mergeC(Tree[lc], Tree[rc]);
}

node range_query(lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>=qs && se<=qe)
    {
        return Tree[si];
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].splitC(Tree[lc], Tree[rc]);
    node l, r;
    l.identity();
    r.identity();
    if(qs<=sm) l = range_query(lc, ss, sm, qs, qe);
    if(qe>sm) r = range_query(rc, sm+1, se, qs, qe);
    Tree[si].mergeC(Tree[lc], Tree[rc]);
    node res;
    res.mergeC(l, r);
    return res;
}

void update_single_node(node &n, lli new_val)
{
    n.init(new_val);
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, lli val)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], val);
        return;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].splitC(Tree[lc], Tree[rc]);
    if(qs<=sm) range_update(lc, ss, sm, qs, qe, val);
    if(qe>sm) range_update(rc, sm+1, se, qs, qe, val);
    Tree[si].mergeC(Tree[lc], Tree[rc]);
}

void update(lli si, lli ss, lli se, lli qi, lli val)
{
    range_update(si, ss, se, qi, qi, val);
}

int main()
{
    lli N, Q, i;
    scanf("%lld\n", &N);
    for(i=1;i<=N;++i)
        scanf("%lld", &A[i]);
    buildTree(1, 1, N);
    scanf("%lld\n", &Q);
    while(Q--)
    {
        lli x, y, ch;
        scanf("%lld %lld %lld", &ch, &x, &y);
        if(ch==0)
        {
            update(1, 1, N, x, y);
        }
        else
        {
            node res;
            res = range_query(1, 1, N, x, y);
            printf("%lld\n", res.maxSum());
        }
    }
    return 0;
}
