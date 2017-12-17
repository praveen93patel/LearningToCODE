#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;

void BinarySearch(ll N, ll C, vector<ll> &stall, ll mi, ll mx, ll &ans)
{
    if(mi>mx)
        return;
    ll mid = mi + (mx-mi)/2;
    ll count = 1;
    ll prev = 0;
    for(ll i=1; i<N; ++i)
    {
        if(stall[i]-stall[prev]< mid)
            continue;
        ++count;
        prev = i;
        if(count==C)
        {
            ans = mid;
            BinarySearch(N, C, stall, mid+1, mx, ans);
            return ;
        }
    }
    BinarySearch(N, C, stall, mi, mid-1, ans);
}

void RunCode()
{
    ll N, C;
    cin>>N>>C;
    if(N<2) return;
    vector<ll> stall(N);
    ll i;
    for(i=0;i<N;++i)
        cin>>stall[i];
    sort(stall.begin(), stall.end());
    ll mi, mx;
    mi = stall[1]-stall[0];
    for(i=2;i<N;++i)
        mi = min(mi, stall[i]-stall[i-1]);
    if(C==N)
    {
        cout<<mi<<endl;
        return;
    }
    mx = (stall[N-1]-stall[0])/(C-1);
    ll ans = 0;
    BinarySearch(N, C, stall, mi, mx, ans);
    cout<<ans<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        RunCode();
    }
    return 0;
}
