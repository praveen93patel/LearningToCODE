#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long int lli;

struct node
{
    lli distinct;
    void init()
    {
        distinct = 0;
    }
    void identity()
    {
        distinct = 0;
    }
    void merge(node &l, node &r)
    {
        distinct = l.distinct + r.distinct;
    }
    void split(node &l, node &r)
    {
    }
};

node Tree[1000006];
lli A[1000006];
lli prevOcc[1000006];
lli ans[200005];
struct query
{
    lli l, r, idx;
    //query(lli x, lli y, lli i) : l(x), r(y), idx(i) {}
} Queries[200005];

bool MyCompare(query a, query b)
{
    return (a.r<b.r || (a.r==b.r && a.l<b.l));
}

void buildTree(lli si, lli ss, lli se)
{
    if(ss==se)
    {
        Tree[si].init();
        return;
    }
    lli sm = ss + (se-ss)/2;
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
    Tree[si].split(Tree[lc], Tree[rc]);
    node l, r;
    l.identity();
    r.identity();
    if(qs<=sm) l = range_query(lc, ss, sm, qs, qe);
    if(qe>sm) r = range_query(rc, sm+1, se, qs, qe);
    Tree[si].merge(Tree[lc], Tree[rc]);
    node res;
    res.merge(l, r);
    return res;
}

void update_single_node(node &n, lli val)
{
    n.distinct += val;
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
    if(qe>sm) range_update(rc, sm+1, se, qs, qe, val);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

void update(lli si, lli ss, lli se, lli qi, lli val)
{
    range_update(si, ss, se, qi, qi, val);
}

int main()
{
    lli N, Q, x, y;
    scanf("%lld", &N);
    lli i, j;
    for(i=1;i<=N;++i)
        scanf("%lld", &A[i]);
    scanf("%lld", &Q);
    for(i=1;i<=Q;++i)
    {
        scanf("%lld%lld", &x, &y);
        //Queries[i] = query(x, y, i);
        Queries[i].l = x;
        Queries[i].r = y;
        Queries[i].idx = i;
    }
    sort(Queries+1, Queries+Q+1, MyCompare);
    for(i=0;i<1000006;++i)
        prevOcc[i] = 0;

    for(i=1, j=1; i<=N && j<=Q; ++i)
    {
        if(prevOcc[A[i]])
        {
            update(1, 1, N, prevOcc[A[i]], -1);
        }
        prevOcc[A[i]] = i;
        update(1, 1, N, i, 1);
        while(j<=Q && Queries[j].r==i)
        {
            node res = range_query(1, 1, N, Queries[j].l, Queries[j].r);
            ans[Queries[j].idx] = res.distinct;
            ++j;
        }
    }
    for(i=1; i<=Q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
