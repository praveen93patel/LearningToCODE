#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

struct node
{
    int count;
    node *left, *right;
    node() : count(0), left(NULL), right(NULL) {}
    node(int c, node *l, node *r) :
        count(c), left(l), right(r) {}
    node* insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);

node* node::insert(int l, int r, int w)
{
    if(l<=w && w<r)
    {
        if(l+1==r)
        {
            return new node(this->count+1, null, null);
        }
        int m = (l+r)>>1;
        return new node(this->count+1, this->left->insert(l, m, w), this->right->insert(m, r, w));

    }
    return this;
}

#define MAXN 100005
#define LN 19
#define rep(i,n) for(int i=0; i<n; ++i)
#define fd(i,a,b) for(int i=a; i>=b; --i)

int A[MAXN], M[MAXN], PA[MAXN][LN], depth[MAXN], maxi;
vector<int> adj[MAXN];
node *root[MAXN];

void dfs(int curr, int prev)
{
    PA[curr][0] = prev;
    depth[curr] = (prev == -1 ? 0 : depth[prev]+1);

    root[curr] = (prev==-1 ? null : root[prev])->insert(0, maxi, M[curr]);

    rep(i, adj[curr].size())
    {
        if(adj[curr][i] != prev)
            dfs(adj[curr][i], curr);
    }
}

int LCA(int u, int v)
{
    if(depth[u] < depth[v])
        return LCA(v, u);
    int diff = depth[u] - depth[v];

    rep(i, LN)
    {
        if((diff>>i) & 1)
            u = PA[u][i];
    }
    if(u==v)
        return u;

    fd(i, LN-1, 0)
    {
        if(PA[u][i] != PA[v][i])
        {
            u = PA[u][i];
            v = PA[v][i];
        }
    }
    return PA[u][0];
}

int query(node *a, node *b, node *c, node *d, int l, int r, int k)
{
    int count = a->count + b->count - c->count - d->count;
    if(l+1 == r)
        return count;
    int m = (l+r)>>1;
    if(m>k)
        return query(a->left, b->left, c->left, d->left, l, m, k);
    return query(a->right, b->right, c->right, d->right, m, r, k);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, u, v, k;
    while(cin>>n)
    {
        cin>>m;
        rep(i,n)
            cin>>A[i];
        rep(i,n+1)
            delete root[i];
        rep(i,n+1)
            adj[i].clear();
        memset(PA, -1, sizeof(PA));

        rep(i, n-1)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        maxi = n+1;
        null->left = null->right = null;

        dfs(1, -1);

        //Build jump table for LCA in O(log N)
        rep(i, LN-1)
            rep(j, n)
                if(PA[j][i] != -1)
                    PA[j][i+1] = PA[PA[j][i]][i];

        while(m--)
        {
            cin>>u>>v>>k;
            int lca = LCA(u, v);
            int ans = query(root[u], root[v], root[lca], (PA[lca][0]==-1 ? null : root[PA[lca][0]]), 0, maxi, k);
            if(ans>0)
                cout<<"Find"<<endl;
            else
                cout<<"NotFind"<<endl;
        }
        cout<<endl;


    }
    return 0;
}
