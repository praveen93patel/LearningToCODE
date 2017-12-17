#include<iostream>
#include<algorithm>
#include<vector>
#define MOD 5000000
using namespace std;
typedef long long int lli;

class INCSEQ
{
    lli N, K;
    lli *Tree;
    void init();
    lli read(lli idx);
    void update(lli idx, lli val);
    lli mod(lli a, lli b);
    void normalization(vector<lli> &A);
public:
    INCSEQ(lli n, lli k)
    {
        N=n;
        K=k;
        Tree = new lli[N+1];
    }
    lli increasingSequences(vector<lli> &A);
};


void INCSEQ::init()
{
    for(lli i=0; i<=N; ++i)
        Tree[i] = 0;
}
lli INCSEQ::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans = mod(ans, Tree[idx]);
        idx -= (idx & (-idx));
    }
    return ans;
}
void INCSEQ::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] = mod(Tree[idx], val);
        idx += (idx & (-idx));
    }
}
lli INCSEQ::mod(lli a, lli b)
{
    lli ans = a+b;
    while(ans>=MOD)
    {
        ans = ans - MOD;
    }
    return ans;
}
void INCSEQ::normalization(vector<lli> &A)
{
    lli M = A.size();
    vector<lli> tmp(M);
    for(lli i=0; i<M; ++i)
        tmp[i] = A[i];
    sort(tmp.begin(), tmp.end());
    for(lli i=0; i<M; ++i)
        A[i] = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin() + 1;
}
lli INCSEQ::increasingSequences(vector<lli> &A)
{
    normalization(A);
    vector<vector<lli> > DP(N, vector<lli>(K+1));
    lli i, p;
    for(i=0;i<N;++i)
        DP[i][1] = 1;
    for(p=2; p<=K; ++p)
    {
        init();
        for(i=1;i<N;++i)
        {
            update(A[i-1], DP[i-1][p-1]);
            DP[i][p] = mod(DP[i][p], read(A[i]-1));
        }
    }
    lli ans = 0;
    for(i=0;i<N;++i)
        ans = mod(ans, DP[i][K]);
    return ans;
}

int main()
{
    lli n, k;
    cin>>n>>k;
    INCSEQ IS(n,k);
    vector<lli> A(n);
    for(lli i=0; i<n; ++i)
        cin>>A[i];
    cout<<IS.increasingSequences(A)<<endl;
    return 0;
}
