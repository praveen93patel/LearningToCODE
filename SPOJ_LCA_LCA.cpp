#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define MAXN 10003
#define MAXLOGN 20
int N, Q;
vector<int> adj[MAXN];
int E[2*MAXN], L[2*MAXN], H[MAXN], P[2*MAXN][MAXLOGN];
int index;

void Clear()
{
    for(int i=0; i<=N; ++i)
        adj[i].clear();
}

void EulerPath(int node, int level, int prev)
{
    E[index] = node;
    L[index] = level;
    if(!H[node])
        H[node] = index;
    ++index;
    for(int i=0; i<adj[node].size(); ++i)
    {
        if(adj[node][i]==prev)
            continue;
        EulerPath(adj[node][i], level+1, node);
        E[index] = node;
        L[index] = level;
        ++index;
    }
}

void BuildSparseTable()
{
    int i, j;
    int NN = 2*N;
    for(i=1; i<NN; ++i)
        P[i][0] = i;
    for(j=1; (1<<j) <= NN; ++j)
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

void LCAtoRMQ()
{
    for(int i=1; i<=N; ++i)
        H[i]=0;
    index = 1;
    EulerPath(1, 1, 0);
    BuildSparseTable();
}

int RMQ(int i, int j)
{
	if(j<i)
	{
		int t = i;
		i=j;
		j=t;
	}
    int k=0;
	 for(k=0; (1<<k)<=(j-i+1); ++k);
	 --k;
    int pow2k = (1<<k);
    int ind;
    if(L[P[i][k]] <= L[P[j-pow2k+1][k]])
        ind = P[i][k];
    else
        ind = P[j-pow2k+1][k];
    return E[ind];
}

void RunCode(int T)
{
    cin>>N;
    Clear();
    int M, i, j;
    for(i=1; i<=N; ++i)
    {
        cin>>M;
        while(M--)
        {
            cin>>j;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    LCAtoRMQ();
    cin>>Q;
    int x, y, ans;
    cout<<"Case "<<T<<":"<<endl;
    while(Q--)
    {
        cin>>x>>y;
        ans = RMQ(H[x], H[y]);
        cout<<ans<<endl;
    }
}

int main()
{
    int T;
    cin>>T;
    for(int t=1; t<=T; ++t)
    {
        RunCode(t);
    }
    return 0;
}
