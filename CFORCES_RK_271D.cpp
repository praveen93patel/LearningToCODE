#include<iostream>
#include<string>
#include<vector>
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

ll RabinKarp(vector<ll> &arr, vector<ll> &countBad, ll len, ll k)
{
    ll ans = 0;
    ll n = arr.size();
    ll i, h1, h2;
    h1=h2=0;
    ll B = 29;
    ll E1 = pow(B, len-1, M1);
    ll E2 = pow(B, len-1, M2);
    unordered_map<ll, ll> MyMap;
    for(i=0;i<len; ++i)
    {
        h1 = mod(h1*B + arr[i], M1);
        h2 = mod(h2*B + arr[i], M2);
    }
    ll bad = countBad[len-1];
  //  cout<<"Test: : "<<h1<<" : "<<h2<<" : "<<bad<<endl;

    if(bad<=k)
    {
        ++ans;
        MyMap.insert(pair<ll,ll>(h1, h2));
    }
    for(i=len;i<n;++i)
    {
        h1 = mod(h1 - mod(arr[i-len]*E1, M1), M1);
        h1 = mod(h1*B, M1);
        h1 = mod(h1 + arr[i], M1);
        h2 = mod(h2 - mod(arr[i-len]*E2, M2), M2);
        h2 = mod(h2*B, M2);
        h2 = mod(h2 + arr[i], M2);

        bad = countBad[i]-countBad[i-len];
      //  cout<<"Test: : "<<h1<<" : "<<h2<<" : "<<bad<<endl;
        if(bad<=k)
        {
            if(MyMap.find(h1)==MyMap.end() || MyMap[h1]!=h2)
            {
                ++ans;
                MyMap.insert(pair<ll,ll>(h1, h2));
            }
        }
    }
  //  cout<<len<<" : "<<ans<<endl;
    return ans;
}

void RunCode()
{
    string str, bad;
    ll k, i;
    cin>>str;
    cin>>bad;
    cin>>k;
    ll n=str.size();
    vector<ll> countBad(n, 0);
    vector<ll> arr(n, 0);
    for(i=0; i<n; ++i)
    {
        arr[i] = str[i]-'a';
        if(bad[arr[i]]=='0')
            countBad[i] = 1;
    }
    for(i=1;i<n;++i)
        countBad[i] += countBad[i-1];
  /*  for(i=0;i<n;++i)
        cout<<str[i]<<" "<<arr[i]<<" "<<countBad[i]<<endl;
 */
    ll ans = 0;
    for(i=1; i<=n; ++i)
        ans+=RabinKarp(arr, countBad, i, k);
    cout<<ans<<endl;
}

int main()
{
    RunCode();
    return 0;
}
