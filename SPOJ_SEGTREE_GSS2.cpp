#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long int lli;
lli MINF = -100000000000ll;
#define P5 100000
struct node
{
    lli best, curr, lazy, best_lazy;
    void identity()
    {
        best = best_lazy = MINF;
        curr = lazy = 0;
    }
    void merge(node& l, node& r)
    {
        best = max(l.best, r.best);
        curr = max(l.curr, r.curr);
        lazy = best_lazy = 0;
    }
    void split(node& l, node& r)
    {
        l.best_lazy = max(l.best_lazy, l.lazy + best_lazy);
        l.lazy += lazy;
        l.best = max(l.best, l.curr + best_lazy);
        l.curr += lazy;
        r.best_lazy = max(r.best_lazy, r.lazy + best_lazy);
        r.lazy += lazy;
        r.best = max(r.best, r.curr + best_lazy);
        r.curr += lazy;
        lazy = best_lazy = 0;
    }
};

node Tree[1000006];
lli A[100005];
struct query
{
    lli l, r, idx;
} Queries[100005];
lli ans[100005];
lli lastOcc[200005];

void buildTree(lli si, lli ss, lli se)
{
    if(ss == se)
    {
        Tree[si].identity();
        return;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    buildTree(lc, ss, sm);
    buildTree(rc, sm+1, se);
    Tree[si].merge(Tree[lc], Tree[rc]);
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
    node l, r;
    l.identity();
    r.identity();
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) l = range_query(lc, ss, sm, qs, qe);
    if(qe> sm) r = range_query(rc, sm+1, se, qs, qe);
    Tree[si].merge(Tree[lc], Tree[rc]);
    node res ;
    res.merge(l, r);
    return res;
}

void update_single_node(node& n, lli val)
{
    n.best_lazy = max(n.best_lazy, n.lazy + val);
    n.lazy += val;
    n.best = max(n.best, n.curr + val);
    n.curr += val;
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, lli val)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], val);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) range_update(lc, ss, sm, qs, qe, val);
    if(qe>sm)  range_update(rc, sm+1, se, qs, qe, val);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

bool myCompare(query p, query q)
{
    return (p.r<q.r || (p.r==q.r && p.l<q.l));
}

int main()
{
    lli N, Q, i;
    scanf("%lld", &N);
    for(i=1; i<=N; ++i)
        scanf("%lld", &A[i]);
    scanf("%lld", &Q);
    for(i=1; i<=Q; ++i)
    {
        scanf("%lld%lld", &Queries[i].l, &Queries[i].r);
        Queries[i].idx = i;
    }
    sort(Queries+1, Queries+Q+1, myCompare);
    lli j, q;
    q = 1;
    buildTree(1, 1, N);
    for(i=1; i<=N; ++i)
    {
        j = lastOcc[A[i]+P5];
        range_update(1, 1, N, j+1, i, A[i]);
        lastOcc[A[i]+P5] = i;
        while(q<=Q && Queries[q].r==i)
        {
            node res;
            res = range_query(1, 1, N, Queries[q].l, Queries[q].r);
            ans[Queries[q].idx] = res.best;
            ++q;
        }
    }
    for(i=1; i<=Q; ++i)
    {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
