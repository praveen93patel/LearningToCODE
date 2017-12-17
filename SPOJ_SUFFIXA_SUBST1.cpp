#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;

struct entry
{
    int nr[2];
    int p;
};

int cmp(struct entry a, struct entry b)
{
    return a.nr[0]==b.nr[0] ? (a.nr[1]<b.nr[1]? 1: 0) : (a.nr[0]<b.nr[0] ? 1: 0);
}

/*ll calculateLCP(vector<vector<ll> > &P, ll x, ll y, ll stp)
{
    ll k, ret = 0;
    ll N = P[0].size();
    if(x==y) return N-x;
    for(k=stp-1; k>=0; --k)
    {
        if(P[k][x] == P[k][y])
        {
            x += 1<<k;
            y += 1<<k;
            ret += 1<<k;
        }
    }
    return ret;
}*/

ll kasai(string str, vector<ll> rank)
{
    ll ans = 0;
    ll N = str.size();
    ll i, j, k = 0;
    vector<ll> SA(N, 0);
    for(i=0;i<N;++i)
        SA[rank[i]] = i;
    for(i=0;i<N;++i, k?k--:0)
    {
        if(rank[i]==N-1)
        {
            k=0;
            continue;
        }
        j = SA[rank[i]+1];
        while(i+k<N && j+k<N && str[i+k]==str[j+k])
            ++k;
        ans+=k;
    }
    return ans;
}

void RunCode()
{
    string A;
    cin>>A;
    A.push_back('@');
    ll N = A.size();
    vector<vector<ll> > P(17, vector<ll>(N));
    vector<struct entry> L(N);
    ll i, stp, cnt;
    for(i=0;i<N;++i)
        P[0][i] = A[i]-'A';
    for(stp=1, cnt=1; (cnt/2)<N; stp++, cnt <<= 1)
    {
        for(i=0;i<N;++i)
        {
            L[i].nr[0] = P[stp-1][i];
            L[i].nr[1] = (i+cnt < N) ? P[stp-1][i+cnt] : -1;
            L[i].p = i;
        }
        sort(L.begin(), L.end(), cmp);
        for(i=0;i<N;++i)
        {
            P[stp][L[i].p] = i;
            if(i>0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1])
                P[stp][L[i].p] = P[stp][L[i-1].p];
        }
    }
    ll ans = (N*(N-1))/2;
    /*for(i=1;i<N;++i)
    {
        ans -= calculateLCP(P, L[i-1].p, L[i].p, stp);
    }*/
    ans -= kasai(A, P[stp-1]);
    cout<<ans<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
        RunCode();
    return 0;
}
