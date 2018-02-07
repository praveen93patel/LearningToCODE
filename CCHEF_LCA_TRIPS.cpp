#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

#define MAXN 100005
#define MAXLN 20
#define MAXSQRT 320

int N, X, Y, D, M, L, C, Q;
vector<pair<int, int> > adj[MAXN];
int H[MAXN], P[MAXN][MAXLN], DST[MAXN], Z[MAXN][MAXLN];

void init()
{
    for(int i=0; i<=N; ++i)
        for(int j=0; j<MAXLN; ++j)
            P[i][j] = -1;
}

void init2()
{
    for(int i=0; i<=N; ++i)
        for(int j=0; j<MAXLN; ++j)
            Z[i][j] = -1;
}

void dfs(int u)
{
    if(P[u][0]==-1)
    {
        DST[u] = 0;
        H[u] = 0;
    }
    int v;
    for(int i=0; i<adj[u].size(); ++i)
    {
        v = adj[u][i].first;
        if(v==P[u][0])
            continue;
        DST[v] = DST[u] + adj[u][i].second;
        H[v] = H[u] + 1;
        P[v][0] = u;
        for(int i=1; i<MAXLN; ++i)
            P[v][i] = (P[v][i-1]==-1)? -1 : P[P[v][i-1]][i-1];
        dfs(v);
    }
}

int KthAncestor(int u, int k)
{
    for(int i=0; i<MAXLN; ++i)
    {
        if(u==-1 || k==0)
            break;
        if(k%(1<<i))
            u = P[u][i];
        k/=2;
    }
    return u;
}

void dfs(int c, int u)
{
    for(int i=1; i<=N; ++i)
    {
        Z[i][0] = KthAncestor(i, c);
    }
    for(int j=1; j<MAXLN; ++j)
    {
        for(int i=1; i<=N; ++i)
            if(Z[i][j-1] != -1)
                Z[i][j] = Z[Z[i][j-1]][j-1];
    }
}

int LCA(int u, int v)
{
    if(H[u]<H[v])
    {
        int t = u;
        u = v;
        v = t;
    }
    for(int i=MAXLN; i>=0; --i)
    {
        if(P[u][i]==-1)
            continue;
        if(H[P[u][i]] >= H[v])
            u = P[u][i];
    }
    if(u==v)
        return u;
    for(int i=MAXLN; i>=0; --i)
    {
        if(P[u][i] != P[v][i])
        {
            u = P[u][i];
            v = P[v][i];
        }
    }
    return P[u][0];
}

int single_jump(int u, int c)
{
    int st = DST[u];
    int v;
    for(int i=MAXLN; i>=0; --i)
    {
        v = P[u][i];
        if(v==-1 || st-DST[v]>c)
            continue;
        u = v;
    }
    return u;
}

struct info
{
    int steps;
    int rem_dist;
};

info move_up(int u, int w, int c)
{
    int steps = 0;
    int rem_dist = 0;
    while(u!=w)
    {
        int tmp = single_jump(u, c);
        if(H[tmp] > H[w])
        {
            ++steps;
            u = tmp;
        }
        else
        {
            rem_dist = DST[u] - DST[w];
            break;
        }
    }
    return info{steps, rem_dist};
}

info move_up(int u, int w)
{
    int steps = 0;
    for(int i=MAXLN; i>=0; --i)
    {
        int tmp = Z[u][i];
        if(tmp!=-1 && H[tmp]>H[w])
        {
            steps += (1<<i);
            u = tmp;
        }
    }
    return info{steps, DST[u] - DST[w]};
}

struct query
{
    int c, u, v, ind;
};

bool myCompare(query a, query b)
{
    return a.c < b.c;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>N;
    for(int i=0; i<N-1; ++i)
    {
        cin>>X>>Y>>D;
        adj[X].push_back(make_pair(Y, D));
        adj[Y].push_back(make_pair(X, D));
    }
    init();
    dfs(1);
    cin>>Q;
    vector<query> queries(Q);
    for(int i=0; i<Q; ++i)
    {
        cin>>X>>Y>>C;
        queries[i].c = C;
        queries[i].u = X;
        queries[i].v = Y;
        queries[i].ind = i;
    }
    sort(queries.begin(), queries.end(), myCompare);
    int prevC = 0;
    vector<int> res(Q);
    for(int i=0; i<Q; ++i)
    {
        C = queries[i].c;
        X = queries[i].u;
        Y = queries[i].v;
        L = LCA(X, Y);
        info l1, l2;
        if(C>=(int)sqrt(N))
        {
            l1 = move_up(X, L, C);
            l2 = move_up(Y, L, C);
        }
        else
        {
            if(C!=prevC)
                dfs(C, 1);
            l1 = move_up(X, L);
            l2 = move_up(Y, L);
        }
        int ans = l1.steps+l2.steps;
        ans += ceil((double)(l1.rem_dist+l2.rem_dist)/(double)C);
        res[queries[i].ind] = ans;
    }
    for(int i=0; i<Q; ++i)
        cout<<res[i]<<endl;
    return 0;
}
