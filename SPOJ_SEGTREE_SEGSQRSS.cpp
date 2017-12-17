#include<iostream>
#include<cstdio>

using namespace std;

typedef long long int lli;

struct node
{
    lli sum, sqrSum, add, numLeaves;
    bool isSetAll;
    void init(lli val)
    {
        sum = val;
        sqrSum = val*val;
        add = 0;
        numLeaves = 1;
        isSetAll = false;
    }
    void identity()
    {
        sum = 0;
        sqrSum = 0;
        add = 0;
        numLeaves = 0;
        isSetAll = false;
    }
    void merge(node &l, node &r)
    {
        sum = l.sum + r.sum;
        sqrSum = l.sqrSum + r.sqrSum;
        add = 0;
        numLeaves = l.numLeaves + r.numLeaves;
        isSetAll = false;
    }
    void split(node &l, node &r)
    {
        if(isSetAll)
        {
            l.sum = l.numLeaves*add;
            l.sqrSum = l.sum*add;
            l.add = add;
            l.isSetAll = true;
            r.sum = r.numLeaves*add;
            r.sqrSum = r.sum*add;
            r.add = add;
            r.isSetAll = true;
        }
        else
        {
            l.sqrSum += 2*add*l.sum + l.numLeaves*add*add;
            l.sum += l.numLeaves*add;
            l.add += add;
            //l.isSetAll
            r.sqrSum += 2*add*r.sum + r.numLeaves*add*add;
            r.sum += r.numLeaves*add;
            r.add += add;
            //r.isSetAll
        }
    }
};

node Tree[1000006];
lli A[100005];

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

void update_single_node(node &n, lli add, bool isSetAll)
{
    if(isSetAll)
    {
        n.sum = n.numLeaves*add;
        n.sqrSum = n.sum*add;
        n.add = add;
        n.isSetAll = true;
    }
    else
    {
        n.sqrSum += 2*add*n.sum + n.numLeaves*add*add;
        n.sum += n.numLeaves*add;
        n.add += add;
        //n.isSetAll
    }
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, lli add, bool isSetAll)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], add, isSetAll);
        return;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) range_update(lc, ss, sm, qs, qe, add, isSetAll);
    if(qe>sm) range_update(rc, sm+1, se, qs, qe, add, isSetAll);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

int main()
{
    lli T, N, Q;
    scanf("%lld", &T);
    for(lli t = 1; t<=T; ++t)
    {
        printf("Case %d:\n", t);
        scanf("%lld%lld", &N, &Q);
        lli i, ch, x, y, val;
        for(i=1; i<=N; ++i)
        {
            scanf("%lld", &A[i]);
        }
        buildTree(1, 1, N);
        while(Q--)
        {
            scanf("%lld%lld%lld", &ch, &x, &y);
            switch(ch)
            {
            case 0:
                scanf("%lld", &val);
                range_update(1, 1, N, x, y, val, true);
                break;
            case 1:
                scanf("%lld", &val);
                range_update(1, 1, N, x, y, val, false);
                break;
            case 2:
                node res;
                res = range_query(1, 1, N, x, y);
                printf("%lld\n", res.sqrSum);
                break;
            default:
                ;
            }
        }
    }
}
