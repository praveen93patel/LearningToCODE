#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long int lli;

class MaxSum
{
    lli N, Q;
    lli *Tree;
    lli read(lli idx);
    void update(lli idx, lli val);
public:
    MaxSum(lli n, lli q)
    {
        N = n;
        Q = q;
        Tree = new lli[N+1];
        for(lli i=0; i<=N; ++i)
            Tree[i] = 0;
    }
    lli queries(vector<lli> &A);
};

lli MaxSum::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}
void MaxSum::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}
lli MaxSum::queries(vector<lli> &A)
{
    lli l, r;
    while(Q--)
    {
        cin>>l>>r;
        update(l, 1);
        update(r+1, -1);
    }
    vector<lli> B(N);
    for(lli i=0; i<N; ++i)
        B[i] = read(i+1);
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    lli ans=0;
    for(lli i=0; i<N; ++i)
        ans += A[i]*B[i];
    return ans;
}

void RunCode()
{
    lli n, q;
    cin>>n>>q;
    MaxSum ms(n, q);
    vector<lli> A(n);
    for(lli i=0; i<n; ++i)
        cin>>A[i];
    cout<<ms.queries(A)<<endl;
}

int main()
{
    lli T = 1;
    //cin>>T;
    while(T--)
        RunCode();
    return 0;
}
