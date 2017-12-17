#include<iostream>
#include<cstdio>
using namespace std;

typedef long long int lli;

void swap(lli &a, lli &b)
{
    lli tmp = a;
    a=b;
    b=tmp;
}

struct node
{
    lli red, green;
    bool add;
    void init()
    {
        red=0;
        green=1;
        add=false;
    }
    void identity()
    {
        red=green=0;
        add=false;
    }
    void mergeC(node &l, node &r)
    {
        red = l.red+r.red;
        green = l.green+r.green;
        add = false;
    }
    void splitC(node &l, node &r)
    {
        if(add)
        {
            swap(l.green, l.red);
            l.add = !l.add;
            swap(r.green, r.red);
            r.add = !r.add;
        }
        add = false;
    }
};

node Tree[3][1000006];
//node TreeY[1000006];
//node TreeZ[1000006];

void buildTree(lli t, lli si, lli ss, lli se)
{
    if(ss==se)
    {
        Tree[t][si].init();
        return ;
    }
    lli lc = 2*si;
    lli rc = lc+1;
    lli sm = ss+(se-ss)/2;
    buildTree(t, lc, ss, sm);
    buildTree(t, rc, sm+1, se);
    Tree[t][si].mergeC(Tree[t][lc], Tree[t][rc]);
}

node range_query(lli t, lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>=qs && se<=qe)
    {
        return Tree[t][si];
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[t][si].splitC(Tree[t][lc], Tree[t][rc]);
    node l, r;
    l.identity();
    r.identity();
    if(qs<=sm) l = range_query(t, lc, ss, sm, qs, qe);
    if(qe>sm) r = range_query(t, rc, sm+1, se, qs, qe);
    Tree[t][si].mergeC(Tree[t][lc], Tree[t][rc]);
    node res;
    res.mergeC(l, r);
    return res;
}

void update_single_node(node &n)
{
    swap(n.red, n.green);
    n.add = !n.add;
}

void range_update(lli t, lli si, lli ss, lli se, lli qs, lli qe) //val=true
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[t][si]);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[t][si].splitC(Tree[t][lc], Tree[t][rc]);
    if(qs<=sm) range_update(t, lc, ss, sm, qs, qe);
    if(qe>sm) range_update(t, rc, sm+1, se, qs, qe);
    Tree[t][si].mergeC(Tree[t][lc], Tree[t][rc]);
}

int main()
{
    lli T, Q;
    lli N[3];
    scanf("%lld", &T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld", &N[0], &N[1], &N[2], &Q);
        for(lli k=0; k<3; ++k)
        {
            buildTree(k, 1, 1, N[k]);
        }
        while(Q--)
        {
            lli ch, i, j;
            lli x1, x2, y1, y2, z1, z2;
            scanf("%lld", &ch);
            switch(ch)
            {
            case 0:
            case 1:
            case 2:
                scanf("%lld%lld", &i, &j);
                range_update(ch, 1, 1, N[ch], i+1, j+1);
                break;
            case 3:
                scanf("%lld%lld%lld%lld%lld%lld", &x1, &y1, &z1, &x2, &y2, &z2);
                node X, Y, Z;
                X = range_query(0, 1, 1, N[0], x1+1, x2+1);
                Y = range_query(1, 1, 1, N[1], y1+1, y2+1);
                Z = range_query(2, 1, 1, N[2], z1+1, z2+1);
                lli ans = 0;
                ans += X.red*Y.green*Z.green;
                ans += X.green*Y.red*Z.green;
                ans += X.green*Y.green*Z.red;
                ans += X.red*Y.red*Z.red;
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
