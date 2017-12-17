#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
typedef int lli;
int Tree[300005];
int LastOcc[1000005];
int A[300005];
int Result[300005];

struct node
{
    int l, r, idx;
   // node(int l, int r, int i) : l(l), r(r), idx(i) {}
};

bool myCompare(const node a, const node b)
{
    return a.r < b.r ;
}

class DistinctQuery
{
    int N, Q;
    lli read(lli idx);
    void update(lli idx, lli val);
    void normalization();
    void init();
public:
    DistinctQuery(int n, int q)
    {
        N = n;
        Q = q;
        init();
    }
    void distinctElements();
};

lli DistinctQuery::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}
void DistinctQuery::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}
void DistinctQuery::normalization()
{
    vector<lli> tmp(N);
    for(int i=0; i<N; ++i)
        tmp[i] = A[i];
    sort(tmp.begin(), tmp.end());
    for(int i=1; i<=N; ++i)
        A[i] = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin();
}
void DistinctQuery::init()
{
    for(int i=0; i<=N; ++i)
        Tree[i] = 0;
    for(int i=0; i<1000005; ++i)
        LastOcc[i] = 0;
}
void DistinctQuery::distinctElements()
{
    lli i, j, l, r, idx;
    vector<node> Query(Q+1);
    for(i=1; i<=Q; ++i)
    {
        //cin>>Query[i].l>>Query[i].r;
        scanf("%d %d", &Query[i].l, &Query[i].r);
        Query[i].idx = i;
    }
    //normalization();
    sort(Query.begin(), Query.end(), myCompare);

    j=1;
    for(i=1; i<=N; ++i)
    {
        if(LastOcc[A[i]])
            update(LastOcc[A[i]], -1);
		LastOcc[A[i]] = i;
        update(i, 1);
        while(j<=Q)
        {
            r = Query[j].r;
            if(r!=i)
                break;
            l = Query[j].l;
            idx = Query[j].idx;
            Result[idx] = read(r) - read(l-1);
            ++j;
        }
        if(j>Q)
            return;
    }
}

int main()
{
    //std::ios_base::sync_with_stdio(false);
    int N, Q;
    //cin>>N;
    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
        scanf("%d", &A[i]);     //cin>>A[i];
    //cin>>Q;
    scanf("%d", &Q);
    DistinctQuery DQ(N, Q);
    DQ.distinctElements();
    for(int i=1; i<=Q; ++i)
        printf("%d\n", Result[i]);//cout<<Result[i]<<endl;
    return 0;
}
