#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

typedef long long ll;
#define MAXLEN 100005
#define MOD 1000000009

struct state
{
    ll len, link, ds;
    //ll next[201];
    map<ll, ll> next;
};

state st[2*MAXLEN];
ll sz, last;
ll N;
ll A[MAXLEN];

void sa_init()
{
    sz = last =0;
    st[0].len = 0;
    st[0].link = -1;
    ++sz;
    /*for(ll i=0; i<2*MAXLEN; ++i)
        for(ll j=0; j<201; ++j)
            st[i].next[j] = -1;*/
    for(ll i=0; i<2*MAXLEN; ++i)
        st[i].next.clear();
}

void sa_extend(ll c)
{
    ll curr = sz++;
    st[curr].len = st[last].len+1;
    ll p;
    for(p = last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c] = curr;
    if(p==-1)
        st[curr].link = 0;
    else
    {
        ll q = st[p].next[c];
        if(st[q].len == st[p].len+1)
            st[curr].link = q;
        else
        {
            ll clone = sz++;
            st[clone].len = st[p].len+1;
            st[clone].link = st[q].link;
            st[clone].next = st[q].next;
            //for(ll i=0; i<201; ++i) st[clone].next[i] = st[q].next[i];
            for(; p!=-1 && st[p].next[c] == q; p = st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[curr].link = clone;
        }
    }
    last = curr;
}

void distinct_substr()
{
    vector<pair<ll, ll> > vec(sz);
    for(ll i=0; i<sz; ++i)
        vec[i] = make_pair(st[i].len, i);
    sort(vec.begin(), vec.end());
    ll v, w;
    map<ll, ll>::iterator it;
    for(ll i=sz-1; i>=0; --i)
    {
        v = vec[i].second;
        st[v].ds = 1;
        /*for(ll j=0; j<201; ++j)
        {
            w = st[v].next[j];
            if(w==-1)
                continue;
            st[v].ds = (st[v].ds + st[w].ds)%MOD;
        }*/
        for(it=st[v].next.begin(); it!=st[v].next.end(); ++it)
        {
            w = (*it).second;
            st[v].ds = (st[v].ds + st[w].ds)%MOD;
        }
    }
}

void build_sa()
{
    sa_init();
    for(ll i=0; i<N; ++i)
        sa_extend(A[i]);
    distinct_substr();
}

void RunCode()
{
    cin>>N;
    for(ll i=0; i<N; ++i)
        cin>>A[i];
    for(ll i=0; i<N-1; ++i)
        A[i] = A[i+1]-A[i]+100;
    --N;
    build_sa();
    ll ans = (st[0].ds-1+MOD)%MOD;
    cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll T;
    cin>>T;
    while(T--)
    {
        RunCode();
    }
    return 0;
}
