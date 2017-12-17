#include<iostream>
#include<cstdio>
using namespace std;
typedef long long int  lli;

struct node
{
    lli maxspace, used, waste;
    void init(lli val)
    {
        maxspace = val;
        used = 0;
        waste = 0;
    }
    void identity()
    {
        maxspace = 0;
        used = 0;
        waste = 0;
    }
    void merge(node& l, node& r)
    {
        maxspace = max(l.maxspace, r.maxspace);
        used = l.used+r.used;
        waste = l.waste+r.waste;
    }
    void split(node &l, node &r)
    {
    }
};

node Tree[4000006];
lli K, N;

void buildTree(lli si, lli ss, lli se)
{
    if(ss==se)
    {
        Tree[si].init(K);
        return;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    buildTree(lc, ss, sm);
    buildTree(rc, sm+1, se);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

void update_single_node(node& n, lli vol)
{
    n.maxspace -= vol;
    n.used = 1;
    n.waste = n.maxspace;
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, lli vol)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], vol);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) range_update(lc, ss, sm, qs, qe, vol);
    if(qe> sm) range_update(rc, sm+1, se, qs, qe, vol);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

void update(lli si, lli ss, lli se, lli qi, lli vol)
{
    range_update(si, ss, se, qi, qi, vol);
}

void binarySearch(lli si, lli ss, lli se, lli vol)
{
    if(ss==se)
    {
        update(1, 1, N, ss, vol);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    if(Tree[lc].maxspace>=vol)
        binarySearch(lc, ss, sm, vol);
    else
        binarySearch(rc, sm+1, se, vol);
}

void Main()
{
    scanf("%lld\n", &K);
    scanf("%lld\n", &N);

    buildTree(1, 1, N);
    lli i = 0;
    char str[100];
    lli vol, qnt, j;
    while(i<N)
    {
        scanf("%[^\n]%*c", str);
        if(str[0]=='b')
        {
            j= 2;
            qnt = 0;
            while(str[j]!=' ')
            {
                qnt = 10*qnt + str[j]-'0';
                ++j;
            }
            ++j;
            vol = 0;
            while(str[j]!='\0')
            {
                vol = 10*vol + str[j]-'0';
                ++j;
            }
            i+=qnt;
            while(qnt--)
                binarySearch(1, 1, N, vol);
        }
        else
        {
            ++i;
            j=0;
            vol = 0;
            while(str[j]!='\0')
            {
                vol = 10*vol + (str[j]-'0');
                ++j;
            }
            binarySearch(1, 1, N, vol);
        }
    }
    printf("%lld %lld\n", Tree[1].used, Tree[1].waste);
}

void Clear()
{
    for(lli i=0; i<1000006; ++i)
        Tree[i].identity();
}

int main()
{
    lli T;
    scanf("%lld\n", &T);
    while(T--)
    {
        Clear();
        Main();
    }
    return 0;
}

