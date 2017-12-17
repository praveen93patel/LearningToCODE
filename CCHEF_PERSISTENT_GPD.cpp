#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<vector>
using namespace std;

typedef long long ll;

#define MAXN 300005
#define MAXKEY 2147483647

struct node
{
    ll count;
    node *left, *right;
    node() : count(0), left(NULL), right(NULL) {}
    node(ll c, node *l, node *r) :
        count(c), left(l), right(r) {}
};

typedef node * pnode;

pnode null = new node();
pnode root[MAXN];
vector<pair<ll, ll> > adj[MAXN];

pnode update(pnode t, ll low, ll high, ll val)
{
    pnode res = new node();
    res->count = t->count+1;
    res->left = t->left;
    res->right = t->right;
    if(low<high)
    {
        ll mid = low + (high-low)/2;
        if(val<=mid)
            res->left = update(t->left, low, mid, val);
        else
            res->right = update(t->right, mid+1, high, val);
    }
    return res;
}

ll query(pnode root, ll low, ll high, ll k, bool isFindMax)
{
    if(low==high)
        return low;
    ll mid = low+(high-low)/2;
    if(root->left->count>0 && (k<=mid ^ isFindMax))
        return query(root->left, low, mid, k, isFindMax);
    else
        return query(root->right, mid+1, high, k, isFindMax);
}


ll query_min(pnode root, ll low, ll high, ll k, ll bit)
{
    if(low==high)
        return low;
    ll mid = low+(high-low)/2;
    if((!((1<<(30-bit))&k) && root->left->count>0) || root->right->count==0)
        return query_min(root->left, low, mid, k, bit+1);
    else
        return query_min(root->right, mid+1, high, k, bit+1);
}

ll query_max(pnode root, ll low, ll high, ll k, ll bit)
{
    if(low==high)
        return low;
    ll mid = low+(high-low)/2;
    if((((1<<(30-bit))&k) && root->left->count>0) || root->right->count==0)
        return query_max(root->left, low, mid, k, bit+1);
    else
        return query_max(root->right, mid+1, high, k, bit+1);
}

void dfs(ll curr, ll prev, ll val)
{
    root[curr] = update((prev==-1) ? null : root[prev], 0, MAXKEY, val);
    for(ll i=0; i<adj[curr].size(); ++i)
        dfs(adj[curr][i].first, curr, adj[curr][i].second);
}

int main()
{
    unordered_map<ll, ll> MapIdtoIndex;
    ll N, Q, ind;
    cin>>N>>Q;
    ll R, key;
    cin>>R>>key;
    ind = 0;
    MapIdtoIndex[R] = ind;
    null->left = null->right = null;
    //root[0] = update(null, 0, MAXKEY, key);
    ll u, v, k, uind, vind;
    for(ll i=0; i<N-1; ++i)
    {
        cin>>u>>v>>k;
        ++ind;
        MapIdtoIndex[u] = ind;
        uind = ind;
        vind = MapIdtoIndex[v];
        adj[vind].push_back(make_pair(uind, k));
        //root[uind] = update(root[vind], 0, MAXKEY, k);
    }
    dfs(0, -1, key);
    ll last_ans = 0;
    ll t;
    for(ll i=0; i<Q; ++i)
    {
        cin>>t;
        t ^= last_ans;
        if(t==0)
        {
            cin>>v>>u>>k;
            v ^= last_ans;
            u ^= last_ans;
            k ^= last_ans;
            ++ind;
            uind = ind;
            MapIdtoIndex[u] = uind;
            vind = MapIdtoIndex[v];
            root[uind] = update(root[vind], 0, MAXKEY, k);
        }
        else
        {
            cin>>v>>k;
            v ^= last_ans;
            k ^= last_ans;
            ll min_val, max_val;
            min_val = query_min(root[MapIdtoIndex[v]], 0, MAXKEY, k, 0);
            max_val = query_max(root[MapIdtoIndex[v]], 0, MAXKEY, k, 0);
            cout<<(min_val^k)<<" "<<(max_val^k)<<endl;
				last_ans = min_val^max_val;
        }
    }
    return 0;
}
