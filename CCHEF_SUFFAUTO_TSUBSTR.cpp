#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXLEN 250005
typedef long long ll;

ll N, Q, K;
string S;
string alpha;
string ans;
vector<ll> adj[MAXLEN];
bool visited[MAXLEN];

struct state
{
    ll len, link, ds;
    ll next[26];
};

state st[2*MAXLEN];
ll sz;
ll last;

void sa_init()
{
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].ds = 1;
    sz++;
    for(ll i=0; i<2*MAXLEN; ++i)
        for(ll j=0; j<26; ++j)
            st[i].next[j] = -1;
}

void sa_extend(char ch)
{
    ll c = ch-'a';
    ll cur = sz++;
    st[cur].len = st[last].len + 1;
    ll p;
    for(p = last ; p!=-1 && st[p].next[c]==-1; p = st[p].link)
        st[p].next[c] = cur;
    if(p==-1)
        st[cur].link = 0;
    else
    {
        ll q = st[p].next[c];
        if(st[q].len == st[p].len+1)
            st[cur].link = q;
        else
        {
            ll clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            for(ll i=0; i<26; ++i)
                st[clone].next[i] = st[q].next[i];
            for(; p!=-1 && st[p].next[c]==q ; p = st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void dfs(ll u)
{
    ll org_last = last;
    ll ss = adj[u].size();
    ll v;
    visited[u] = true;
    for(ll i=0; i<ss; ++i)
    {
        v = adj[u][i];
        if(visited[v])
            continue;
        sa_extend(S[v]);
        dfs(v);
        last = org_last;
    }
}

void distinct_substr()
{
    ll i, j, v, w;
    vector<pair<ll, ll> > vec(sz);
    for(i=0; i<sz; ++i)
        vec[i] = make_pair(st[i].len, i);
    sort(vec.begin(), vec.end());

    for(i=sz-1; i>=0; --i)
    {
        v = vec[i].second;
        st[v].ds = 1;
        for(j=0; j<26; ++j)
        {
            w = st[v].next[j];
            if(w==-1)
                continue;
            st[v].ds += st[w].ds;
        }
    }
}

void build_sa()
{
    sa_init();
    sa_extend(S[0]);
    dfs(0);
    distinct_substr();
}

void KthSubstring(ll v, ll K, string &ans)
{
    ll i, j, w;
    while(K)
    {
        for(i=0; i<26; ++i)
        {
            j = alpha[i]-'a';
            w = st[v].next[j];
            if(w==-1)
                continue;
            if(st[w].ds>=K)
            {
                ans.push_back(alpha[i]);
                --K;
                v = w;
                break;
            }
            K -= st[w].ds;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>Q;
    cin>>S;
    ll x, y;
    for(ll i=0; i<N-1; ++i)
    {
        cin>>x>>y;
        --x, --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    build_sa();
    cout<<st[0].ds<<endl;
    while(Q--)
    {
        cin>>alpha>>K;
        ans = "";
        if(K==1)
            cout<<ans<<endl;
        else if(K>st[0].ds)
            cout<<"-1"<<endl;
        else
        {
            KthSubstring(0, K-1, ans);
            cout<<ans<<endl;
        }
    }
    return 0;
}
