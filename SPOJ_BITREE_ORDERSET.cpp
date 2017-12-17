#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;
#define endl "\n"
typedef long long int lli;

lli Tree[200005];
char Token[200005];
lli A[200005];
bool exist[200005];

class ORDERSET
{
    lli N, Q;
    void init();
    lli read(lli idx);
    void update(lli idx, lli val);
    void normalization();
    lli binarySearch(lli l, lli r, lli K);
    unordered_map<lli, lli> MyMap;
public:
    ORDERSET(lli NQ)
    {
        N = Q = NQ;
    }
    void RunQueries();
};

lli ORDERSET::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

void ORDERSET::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}

void ORDERSET::normalization()
{
    vector<lli> tmp(N);
    lli i;
    for(i=0; i<N; ++i)
        tmp[i] = A[i+1];
    sort(tmp.begin(), tmp.end());
    for(i=1; i<=N; ++i)
    {
        if(Token[i]!='K')
        {
            lli val = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin() + 1;
            MyMap[val] = A[i];
            A[i] = val;
        }
    }
}

void ORDERSET::init()
{
    for(lli i=0; i<200005; ++i)
    {
        Tree[i] = 0;
        exist[i] = false;
    }
}

lli ORDERSET::binarySearch(lli l, lli r, lli K)
{
    if(l>r)
        return -1;
    lli m = l+(r-l)/2;
    lli val = read(m);
    if(val == K)
    {
        if(exist[m])
            return m;
        return binarySearch(l, m-1, K);
    }
    if(val>K)
        return binarySearch(l, m-1, K);
    return binarySearch(m+1, r, K);
}

void ORDERSET::RunQueries()
{
    char ch;
    lli val;
    lli i;
    for(i=1; i<=Q; ++i)
    {
        cin>>ch>>val;
        Token[i] = ch;
        A[i] = val;
    }
    normalization();
    init();
    for(i=1; i<=N; ++i)
    {
        switch(Token[i])
        {
        case 'I':
            if(!exist[A[i]])
            {
                update(A[i], 1);
                exist[A[i]] = true;
            }
            break;
        case 'D':
            if(exist[A[i]])
            {
                update(A[i], -1);
                exist[A[i]] = false;
            }
            break;
        case 'C':
            {
                lli ans = read(A[i]-1);
                cout<<ans<<endl;
            }
            break;
        case 'K':
            {
                lli ans = binarySearch(1, N, A[i]);
                if(ans == -1)
                    cout<<"invalid"<<endl;
                else
                    cout<<MyMap[ans]<<endl;
            }
            break;
        default: ;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(0);
    lli Q;
    cin>>Q;
    ORDERSET os(Q);
    os.RunQueries();
    return 0;
}
