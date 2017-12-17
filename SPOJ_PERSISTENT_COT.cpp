#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

#define sz size()
#define pb push_back
#define rep(i,n) for(int i=0; i<n; i++)
#define fd(i,a,b) for(int i=a; i>=b; --i)

#define N 100005
#define LN 19

int v[N], M[N], pa[N][LN], RM[N], depth[N], valid[N], maxi = 0;
vector<int> adj[N];

struct node
{
    int count;
    node *left, *right;
    node(int count, node *left, node *right) :
        count(count), left(left), right(right) {}

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
        return new node(this->count+1, this->left->insert(l,m,w), this->right->insert(m,r,w));

    }
    return this;
}

node *root[N];

void dfs(int curr, int prev)
{
    pa[curr][0] = prev;
    depth[curr] = (prev == -1 ? 0 : depth[prev]+1);

    root[curr] = (prev==-1 ? null : root[prev])->insert(0, maxi, M[curr]);

    rep(i, adj[curr].sz)
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
            u = pa[u][i];
    }
    if(u==v)
        return u;

    fd(i, LN-1, 0)
    {
        if(pa[u][i] != pa[v][i])
        {
            u = pa[u][i];
            v = pa[v][i];
        }
    }
    return pa[u][0];
}

int query(node *a, node *b, node *c, node *d, int l, int r, int k)
{
    if(l+1 == r)
        return l;

    int count = a->left->count + b->left->count - c->left->count - d->left->count;
    int m = (l+r)>>1;
    if(count>=k)
        return query(a->left, b->left, c->left, d->left, l, m, k);
    return query(a->right, b->right, c->right, d->right, m, r, k-count);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    rep(i, n)
    {
        scanf("%d", &v[i]);
    }

    //normalization
    vector<int> tmp(n);
    rep(i, n)
        tmp[i] = v[i];
    sort(tmp.begin(), tmp.end());
    maxi = n+1;
    rep(i, n)
    {
        M[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin();
        RM[M[i]] = v[i];
        valid[M[i]] = 1;
    }

    rep(i, n-1)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    memset(pa, -1, sizeof(pa));

    null->left = null->right = null;

    dfs(0, -1);

    //Build jump table for LCA in O(log N)
    rep(i, LN-1)
        rep(j, n)
            if(pa[j][i] != -1)
                pa[j][i+1] = pa[pa[j][i]][i];

    while(m--)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        --u; --v;
        int lca = LCA(u, v);

        int ans = query(root[u], root[v], root[lca], (pa[lca][0]==-1 ? null : root[pa[lca][0]]), 0, maxi, k);
        //while(ans>0 && valid[ans]==0)
        //    --ans;
        ans = RM[ans];
        printf("%d\n", ans);
    }
    return 0;
}
