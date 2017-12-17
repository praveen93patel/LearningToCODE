#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

typedef long long ll;

#define MAXN 100005
#define MAXC 1000000009

struct node
{
    ll _xor;
    node *left, *right;
    node() : _xor(0), left(NULL), right(NULL) {}
    node(ll xr, node *l, node *r) :
        _xor(xr), left(l), right(r) {}
    node *insert(ll l, ll r, ll w);
};

node *null = new node();

node* node::insert(ll l, ll r, ll w)
{
    if(l<=w && w<=r)
    {
        if(l==r)
            return new node(this->_xor^w, null, null);
        ll m = l+(r-l)/2;
        return new node(this->_xor^w, this->left->insert(l, m, w), this->right->insert(m+1, r, w));
    }
	 return this;
}

node* root[MAXN];
vector<pair<ll, ll> > adj[MAXN];
ll T, N, M;
/*
node* update(node *t, ll low, ll high, ll val)
{
    node *res = new node();
    res->_xor = t->_xor ^ val;
    res->left = t->left;
    res->right = t->right;
    if(low<high)
    {
        ll mid = low+(high-low)/2;
        if(val<=mid)
            res->left = update(t->left, low, mid, val);
        else
            res->right = update(t->right, mid+1, high, val);
    }
    return res;
}
*/

void dfs(ll curr, ll prev, ll val)
{
    root[curr] = ((prev==-1) ? null : root[prev])->insert( 0, MAXC, val);
    for(ll i=0; i<adj[curr].size(); ++i)
    {
	     if(adj[curr][i].first != prev)
            dfs(adj[curr][i].first, curr, adj[curr][i].second);
	 }
}

ll queryRange(node *a, node *b, ll low, ll high, ll qs, ll qe)
{
    if(low>high || qe<low || qs>high)
        return 0;
    if(qs<=low && qe>=high)
        return a->_xor ^ b->_xor;
    ll mid = low + (high-low)/2;
    return queryRange(a->left, b->left, low, mid, qs, qe) ^ queryRange(a->right, b->right, mid+1, high, qs, qe);
}

ll query(node *a, node *b, ll low, ll high, ll k)
{
    return queryRange(a, b, low, high, 0, k);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>N;
        for(ll i=0; i<=N; ++i)
            delete root[i];
        for(ll i=0; i<=N; ++i)
            adj[i].clear();
        for(ll i=0; i<N-1; ++i)
        {
            ll u, v, c;
            cin>>u>>v>>c;
            --u;
            --v;
            adj[u].push_back(make_pair(v, c));
            adj[v].push_back(make_pair(u, c));
        }
        null->left = null->right = null;
        dfs(0, -1, 0);
        cin>>M;
        while(M--)
        {
            ll u, v, k;
            cin>>u>>v>>k;
            --u;
            --v;
            ll ans = query(root[u], root[v], 0, MAXC, k);
            cout<<ans<<endl;
        }
    }
    return 0;
}
