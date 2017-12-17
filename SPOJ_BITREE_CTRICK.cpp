#include<iostream>
#include<vector>
using namespace std;

typedef long long int lli;

lli Tree[200001];
lli Perm[200001];

class CardTrick
{
    lli N;
    lli read(lli idx);
    void update(lli idx, lli val);
    void init();
    lli BinarySearch(lli curr_val, lli prev_idx);
public:
    void Permutation(lli n);
};

void CardTrick::init()
{
    for(lli i=0; i<=N; ++i)
        Tree[i] = Perm[i] = 0;
}

lli CardTrick::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

void CardTrick::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}

lli CardTrick::BinarySearch(lli curr_val, lli prev_idx)
{
    lli pfp, pfs;    // position-from previous index / start
    lli x, y, LS;
    LS = N-curr_val+1;
    x = prev_idx - read(prev_idx);
    y = LS - x;
    pfp = curr_val%LS + 1;
    if(pfp<=y)
        pfs = x+pfp;
    else
        pfs = pfp-y;

    lli low, high, mid;
    low = 1;
    high = N;
    lli space;
    while(low<=high)
    {
        mid = low + (high-low)/2;
        space = mid - read(mid);
        if(space == pfs && Perm[mid]==0)
        {
            return mid;
        }
        if(space>0 && space >= pfs)
            high = mid-1;
        else
            low = mid+1;
    }
    return 0;
}

void CardTrick::Permutation(lli n)
{
    N = n;
    init();
    lli idx;
    lli prev_idx = 0;
    for(lli i=1; i<=N; ++i)
    {
        idx = BinarySearch(i, prev_idx);
        Perm[idx] = i;
        update(idx, 1);
        prev_idx = idx;
    }
    for(lli i=1; i<=N; ++i)
        cout<<Perm[i]<<" ";
    cout<<endl;
}

int main()
{
    lli T, N;
    cin>>T;
    CardTrick ct;
    while(T--)
    {
        cin>>N;
        ct.Permutation(N);
    }
    return 0;
}
