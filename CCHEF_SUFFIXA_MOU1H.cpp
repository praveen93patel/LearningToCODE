#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>

using namespace std;

typedef long long ll;

#define MAXN 100005
#define MOD 1000000009

ll A[MAXN];
ll SA[MAXN], tempSA[MAXN];
ll RA[MAXN], tempRA[MAXN];
ll c[MAXN];
ll N;

void countingSort(ll k)
{
    ll i, sum, maxi = max((ll)300, N);
    memset(c, 0, sizeof(c));
    for(i=0;i<N;++i)
        c[i+k<N ? RA[i+k] : 0]++;
    for(i=sum=0;i<maxi; ++i)
    {
        ll t = c[i];
        c[i] = sum;
        sum += t;
    }
    for(i=0;i<N;++i)
    {
        tempSA[c[SA[i]+k<N ?RA[SA[i]+k] : 0]++] = SA[i];
    }
    for(i=0;i<N;++i)
        SA[i]=tempSA[i];
}

void constructSA()
{
    ll i, k, r;
    for(i=0;i<N;++i) RA[i] = A[i];
    for(i=0;i<N;++i) SA[i] = i;

    for(k=1;k<N;k<<=1)
    {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for(i=1;i<N;++i)
        {
            if(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k])
                tempRA[SA[i]] = r;
            else
                tempRA[SA[i]] = ++r;
        }
        for(i=0;i<N;++i)
            RA[i] = tempRA[i];
        if(RA[SA[N-1]] == N-1)
            break;
    }
}

ll kasai()
{
    ll ans = 0;
    ll k=0;
    for(ll i=0;i<N;++i, k?k--:0)
    {
        if(RA[i]==N-1)
        {
            k=0;
            continue;
        }
        ll j = SA[RA[i]+1];
        while(i+k<N && j+k<N && A[i+k]==A[j+k])
            k++;
        ans+=k;
    }
    return ans;
}

void RunCode()
{
    cin>>N;
    ll prev, curr;
    cin>>prev;
    ll i, j;
    for(i=0;i<N-1;++i)
    {
        cin>>curr;
        A[i] = curr-prev+101;
        prev = curr;
    }
    A[N-1] = 0;
    constructSA();
    ll ans;
    if(N%2==0)
        ans = (N-1)*(N/2);
    else
        ans = N*((N-1)/2);
    ans -= kasai();
    ans = ans%MOD;
    cout<<ans<<endl;
}

int main()
{
    ll T;
    cin>>T;
    while(T--)
        RunCode();
    return 0;
}
