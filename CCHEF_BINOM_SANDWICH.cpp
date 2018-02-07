#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

typedef long long ll;

ll Fact[1000006];

class COMBINATION
{
    ll MOD;
    vector<pair<ll, ll> > pfM;   //first->prime, second->prime power
    void FindFactors();
    ll Lucas(ll n, ll r, pair<ll, ll> P);
    ll SubProb(ll N, ll M, ll R, ll p, ll mod);
    void CalculateFactorials(ll p, ll mod);
    ll Factorial(ll n);
    ll Power(ll x, ll y, ll mod);
    ll ModInverse(ll n,ll p, ll mod);
    ll Power(pair<ll, ll> p);
    ll CRT(vector<pair<ll, pair<ll, ll> > > &ans);
public:
    COMBINATION(ll M) : MOD(M) {}
    ll comb(ll n, ll r);
};

ll COMBINATION::comb(ll n, ll r)
{
    //Find prime factors (and multiplicities) of MOD
    FindFactors();
    ll sz = pfM.size();
    vector<pair<ll, pair<ll, ll> > > ans;
    for(ll i=0; i<sz; ++i)
    {
        pair<ll, ll> p = pfM[i];
        //Use (generalized) Lucas’ Theorem to find all sub problems
        ll tmp = Lucas(n, r, p);
        ll mod = Power(p);
        ans.push_back(make_pair(tmp, make_pair(p.first, mod)));
    }
	 //Use Chinese Remainder Theorem to combine sub results
    ll res = CRT(ans);
    return res;
}

void COMBINATION::FindFactors()
{
    ll M = MOD;
    for(ll f=2; f<=sqrt(M); ++f)
    {
        ll c=0;
        while(M && M%f==0)
        {
            M = M/f;
            ++c;
        }
        if(c)
            pfM.push_back(make_pair(f, c));
    }
    if(M>1)
        pfM.push_back(make_pair(M, 1));
}

ll COMBINATION::Lucas(ll n, ll r, pair<ll, ll> P)
{
    ll p = P.first;
    ll q = P.second;
    ll m = n-r;
    vector<ll> ni;
    while(n)
    {
        ni.push_back(n%p);
        n = n/p;
    }
    ll d = ni.size();
    vector<ll> mi;
    vector<ll> ri;
    for(ll i=0; i<d; ++i)
    {
        mi.push_back(m%p);
        ri.push_back(r%p);
        m = m/p;
        r = r/p;
    }
    ll mx = max(d, q);
    vector<ll> ei(mx+1, 0);
    for(ll i=d-1; i>=0; --i)
    {
        ei[i] = ei[i+1];
        if(ni[i]<mi[i])
            ei[i] += 1;
    }
    vector<ll> Ni(d, 0);
    vector<ll> Mi(d, 0);
    vector<ll> Ri(d, 0);
    ll j;
    ll pp = 1;
    for(j=0; j<q; ++j)
    {
        if(j>=d)
            break;
        Ni[0] += ni[j]*pp;
        Mi[0] += mi[j]*pp;
        Ri[0] += ri[j]*pp;
        pp *= p;
    }
    pp = Power(make_pair(p, q-1));
    ll tmpn, tmpm, tmpr;
    for(j=1; j<d; ++j)
    {
        tmpn = (j+q-1<d) ? ni[j+q-1]*pp : 0;
        tmpm = (j+q-1<d) ? mi[j+q-1]*pp : 0;
        tmpr = (j+q-1<d) ? ri[j+q-1]*pp : 0;

        Ni[j] = (Ni[j-1]-ni[j-1])/p + tmpn;
        Mi[j] = (Mi[j-1]-mi[j-1])/p + tmpm;
        Ri[j] = (Ri[j-1]-ri[j-1])/p + tmpr;
    }
    ll res = 1;
    ll mod = pp*p;
    CalculateFactorials(p, mod);
    for(ll i=0; i<d; ++i)
    {
        //Solve sub problems with Euler's Theorem, Fermat’s little theorem or Pascal’s Triangle
        res = (res*SubProb(Ni[i], Mi[i], Ri[i], p, mod))%mod;
    }
    res = (res*Power(make_pair(p, ei[0])))%mod;
    if((p==2 && q>=3) || ei[q-1]%2==0)
        res *= 1;
    else
    {
        res *= -1;
        res += mod;
    }

    return res;
}

void COMBINATION::CalculateFactorials(ll p, ll mod)
{
    Fact[0] = 1;
	for(int i=1;i<mod;i++){
		if(i%p != 0)
			Fact[i] = (1ll * Fact[i-1] * i) % mod;
		else
			Fact[i] = Fact[i-1];
	}
}

ll COMBINATION::SubProb(ll N, ll M, ll R, ll p, ll mod)
{
    ll ans = 1;
    ans = (ans*Factorial(N))%mod;
    ans = (ans*ModInverse(Factorial(M), p, mod))%mod;
    ans = (ans*ModInverse(Factorial(R), p, mod))%mod;
    return ans;
}

ll COMBINATION::Factorial(ll n)
{
    return Fact[n];
}

ll COMBINATION::Power(ll x, ll y, ll mod)
{
    ll ans = 1;
    while(y>0)
    {
        if(y&1)
            ans = (ans*x)%mod;
        y = y>>1;
        x = (x*x)%mod;
    }
    return ans;
}

ll COMBINATION::ModInverse(ll a, ll p, ll mod)
{
    if(a<0)
        a+=mod;
    ll phi = mod - (mod/p);
    return Power(a, phi-1, mod);
}

ll COMBINATION::Power(pair<ll, ll> p)
{
    ll x = p.first;
    ll y = p.second;
    ll ans = 1;
    while(y>0)
    {
        if(y&1)
            ans *= x;
        y = y>>1;
        x *= x;
    }
    return ans;
}

ll COMBINATION::CRT(vector<pair<ll, pair<ll, ll> > > &ans)
{
    ll sz = ans.size();
    ll res = 0;
    ll ai, ni, mi, mii, ci;
    ll n =MOD;
    for(ll i=0; i<sz; ++i)
    {
        ai = ans[i].first;
        ni = ans[i].second.second;
        mi = n/ni;
        mii = ModInverse(mi%ni, ans[i].second.first, ni);
        ci = (mi*mii)%n;
        res = (res+(ci*ai)%n)%n;
    }
    return res;
}

void RunCode()
{
    ll N, M, K;
    cin>>N>>K>>M;
    ll n, r, m, k;
    if(K>N)
        K=N;
    n=N/K;
    if(n*K==N)
    {
        cout<<n<<" 1"<<endl;
        return;
    }
    ++n;
    r = K - (N%K);
    COMBINATION C(M);
    ll ans = C.comb(n+r-1, r);
    if(ans<0)
        ans += M;
    cout<<n<<" "<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        RunCode();
    }
    return 0;
}
