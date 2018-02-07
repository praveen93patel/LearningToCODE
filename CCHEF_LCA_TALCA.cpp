#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 200005
#define MAXLN 20
int N, Q;
vector<int> adj[MAXN];
int E[2*MAXN], L[2*MAXN], H[MAXN], P[2*MAXN][MAXLN];
int index;

void EulerPath(int node, int level, int prev)
{
    E[index] = node;
    L[index] = level;
    if(!H[node])
        H[node] = index;
    ++index;
    for(int i=0; i<adj[node].size(); ++i)
    {
        if(adj[node][i] == prev)
            continue;
        EulerPath(adj[node][i], level+1, node);
        E[index] = node;
        L[index] = level;
        ++index;
    }
}

void BuildSparseTable()
{
    int NN = 2*N;
    int i,j;
    for(i=1; i<NN; ++i)
        P[i][0] = i;
    for(j=1; (1<<j) <= NN ; ++j)
    {
        for(i=1; i+(1<<(j-1)) < NN; ++i)
        {
            if(L[P[i][j-1]] < L[P[i+(1<<(j-1))][j-1]])
                P[i][j] = P[i][j-1];
            else
                P[i][j] = P[i+(1<<(j-1))][j-1];
        }
    }
}

int RMQ(int i, int j)
{
    if(i>j)
    {
        int t = i;
        i = j;
        j = t;
    }
    int k ;
    for(k=0; (1<<k) <= (j-i+1); ++k);
    --k;
    int pow2k = (1<<k);
    if(L[P[i][k]] <= L[P[j-pow2k+1][k]])
        return E[P[i][k]];
    return E[P[j-pow2k+1][k]];
}

int LCA(int u, int v)
{
    return RMQ(H[u], H[v]);
}

void LCAtoRMQ()
{
    index = 1;
    for(int i=0; i<=N; ++i)
        H[i] = 0;
    EulerPath(1,1,0);
    BuildSparseTable();
}

int Dist(int u, int v)
{
    int l = LCA(u, v);
    return L[H[u]]+L[H[v]]-2*L[H[l]];
}

int main()
{
    cin>>N;
    int r, u, v;
    for(int i=0; i<N-1; ++i)
    {
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LCAtoRMQ();
    cin>>Q;
    int x[6];

    while(Q--)
    {
        cin>>r>>u>>v;
        /*x[0] = r;
        x[1] = u;
        x[2] = v;*/
        x[3] = LCA(r, u);
        x[4] = LCA(r, v);
        x[5] = LCA(u, v);
		  int ans, t, d = 3*MAXN;
        for(int i=3; i<6; ++i)
        {
            t = Dist(x[i], r) + Dist(x[i], u) + Dist(x[i], v);
            if(t<d)
            {
                d = t;
                ans = x[i];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
