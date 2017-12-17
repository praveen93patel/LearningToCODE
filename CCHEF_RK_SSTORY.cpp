#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

typedef long long ll;

#define M1 1000000007
#define M2 100000007

ll mod(ll a, ll b)
{
    return (a%b + b)%b;
}

ll pow(ll x, ll y, ll M)
{
    ll temp;
    if( y == 0)
        return 1;
    temp = pow(x, y/2, M);
    temp = (temp*temp)%M;
    if (y%2 == 0)
        return temp;
    else
        return (x*temp)%M;
}

bool RabinKarp(string &txt, string &pat, ll len, string &s)
{
    ll n, m, i;
    n = txt.size();
    m = pat.size();
    ll B=26;
    unordered_map<ll, ll> MyMap;
    ll h1t, h2t, E1, E2;
    h1t = h2t = 0;
    E1 = pow(B, len-1, M1);
    E2 = pow(B, len-1, M2);
    for(i=0;i<len;++i)
    {
        h1t = mod(h1t*B + txt[i], M1);
        h2t = mod(h2t*B + txt[i], M2);
    }
   // cout<<"text: "<<h1t<<" "<<h2t<<endl;
    MyMap.insert(pair<ll, ll>(h1t, h2t));
    for(i=len;i<n;++i)
    {
        h1t = mod(h1t - mod(txt[i-len]*E1, M1), M1);
        h1t = mod(h1t*B, M1);
        h1t = mod(h1t + txt[i], M1);
        h2t = mod(h2t - mod(txt[i-len]*E2, M2), M2);
        h2t = mod(h2t*B, M2);
        h2t = mod(h2t + txt[i], M2);
        MyMap.insert(pair<ll, ll>(h1t, h2t));

       // cout<<"text: "<<h1t<<" "<<h2t<<endl;
    }
    ll h1p, h2p;
    h1p = h2p = 0;
    for(i=0;i<len;++i)
    {
        h1p = mod(h1p*B + pat[i], M1);
        h2p = mod(h2p*B + pat[i], M2);
    }
    //cout<<"pat: "<<h1p<<" "<<h2p<<endl;
    if(MyMap.find(h1p)!=MyMap.end() && MyMap[h1p]==h2p)
    {
        s = pat.substr(0, len);
        return true;
    }
    for(i=len;i<m;++i)
    {
        h1p = mod(h1p - mod(pat[i-len]*E1, M1), M1);
        h1p = mod(h1p*B, M1);
        h1p = mod(h1p + pat[i], M1);
        h2p = mod(h2p - mod(pat[i-len]*E2, M2), M2);
        h2p = mod(h2p*B, M2);
        h2p = mod(h2p + pat[i], M2);
        if(MyMap.find(h1p)!=MyMap.end() && MyMap[h1p]==h2p)
        {
            s = pat.substr(i-len+1, len);
            return true;
        }
    }
    return false;
}

void BinarySearchLen(string &txt, string &pat, ll low, ll high, string &ans, ll &len)
{
    if(high<low)
        return;
    ll mid = low + (high-low)/2;
   // cout<<"Test: "<<mid<<endl;
    if(!RabinKarp(txt, pat, mid, ans))
        BinarySearchLen(txt, pat, low, mid-1, ans, len);
    else
    {
        len = mid;
        BinarySearchLen(txt, pat, mid+1, high, ans, len);
    }
}

void RunCode()
{
    string txt, pat;
    cin>>txt;
    cin>>pat;
    ll n, m;
    n = txt.size();
    m = pat.size();
    ll len=0;
    string ans;
    BinarySearchLen(txt, pat, 0, m, ans, len);
    if(len!=0)
        cout<<ans<<endl;
    cout<<len<<endl;
}

int main()
{
    RunCode();
    return 0;
}
