#include<iostream>
#include<cstdio>
using namespace std;

typedef long long int lli;

struct node
{
    lli sum, numLeaves, add;
    void init(lli val)
    {
        sum = val;
        numLeaves = 1;
        add = 0;
    }
    void identity()
    {
        sum = numLeaves = add = 0;
    }
    void merge(node &l, node &r)
    {
        sum = l.sum + r.sum;
        numLeaves = l.numLeaves + r.numLeaves;
        add = 0;
    }
    void split(node &l, node &r)
    {
        l.sum += l.numLeaves*add;
        r.sum += r.numLeaves*add;
        l.add += add;
        r.add += add;
        add = 0;
    }
};

node Tree[1000006];

void buildTree(lli si, lli ss, lli se)
{
    if(ss==se)
    {
        Tree[si].init(0);
        return ;
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
    if(qe>sm) r = range_query(rc, sm+1, se, qs, qe);
    Tree[si].merge(Tree[lc], Tree[rc]);
    node res;
    res.merge(l, r);
    return res;
}

void update_single_node(node &n, lli val)
{
    n.sum += n.numLeaves*val;
    n.add += val;
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

void Clear()
{
    for(lli i=0; i<1000006; ++i)
        Tree[i].identity();
}

void Main()
{
    lli N, Q, ch, x, y, v;
    scanf("%lld%lld", &N, &Q);
    buildTree(1, 1, N);
    while(Q--)
    {
        scanf("%lld%lld%lld", &ch, &x, &y);
        if(ch==1)
        {
            node res;
            res = range_query(1, 1, N, x, y);
            printf("%lld\n", res.sum);
        }
        else
        {
            scanf("%lld", &v);
            range_update(1, 1, N, x, y, v);
        }
    }
}

int main()
{
    lli T;
    scanf("%lld", &T);
    while(T--)
    {
        Clear();
        Main();
    }
    return 0;
}
