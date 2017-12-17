#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long int lli;
lli Tree[200005];

class Inversions
{
    lli MAX_N;
    lli cntInv;
    void shrinkValue(vector<lli> &A);
    void init();
public:
    void update(lli idx, lli val);
    lli read(lli idx);
    lli countInv();
};

void Inversions::init()
{
    for(lli i=0; i<=MAX_N; ++i)
        Tree[i] = 0;
}

void Inversions::update(lli idx, lli val)
{
    while(idx<=MAX_N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}

lli Inversions::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

lli Inversions::countInv()
{
    lli N;
    cin>>N;
    vector<lli> A(N);
    for(lli i=0; i<N; ++i)
        cin>>A[i];
    shrinkValue(A);
    cntInv = 0;
	MAX_N = N;
    init();
    for(lli i=N-1; i>=0; --i)
    {
        cntInv += read(A[i]-1);
        update(A[i], 1);
    }
    return cntInv;
}

void Inversions::shrinkValue(vector<lli> &A)
{
    lli N = A.size();
    vector<lli> tmp(N);
    for(lli i=0; i<N;++i)
        tmp[i] = A[i];
    sort(tmp.begin(), tmp.end());
    for(lli i=0; i<N; ++i)
        A[i] = (lli)(lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin()) + 1;
}

int main()
{
    lli T;
    cin>>T;
    while(T--)
    {
        Inversions INV;
        lli ans = INV.countInv();
        cout<<ans<<endl;
    }
    return 0;
}
