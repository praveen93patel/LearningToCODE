#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long int lli;

lli Tree[2][100001];

class Horrible
{
    lli N;
    lli C;
    void update(lli t, lli idx, lli val);
    lli read(lli t, lli idx);
public:
    Horrible(lli n, lli c)
    {
        N=n;
        C=c;
        for(lli i=0; i<=N; ++i)
            Tree[0][i] = Tree[1][i] = 0;
    }
    void HorribleQueries();
};

void Horrible::update(lli t, lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[t][idx] += val;
        idx += (idx & (-idx));
    }
}

lli Horrible::read(lli t, lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[t][idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

void Horrible::HorribleQueries()
{
    lli p, q, v, ch, x, y;
    while(C--)
    {
        cin>>ch>>p>>q;
        if(ch==1)
        {
            x = read(0, q)*q - read(1, q);
            y = read(0, p-1)*(p-1) - read(1, p-1);
            cout<<x-y<<endl;
        }
        else
        {
            cin>>v;
            update(0, p, v);
            update(0, q+1, -v);
            update(1, p, v*(p-1));
            update(1, q+1, -v*q);
        }
    }
}

int main()
{
    lli n, c, t;
    cin>>t;
    while(t--)
    {
        cin>>n>>c;
        Horrible H(n, c);
        H.HorribleQueries();
    }
    return 0;
}
