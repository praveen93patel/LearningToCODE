#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<cstdio>
using namespace std;
typedef long long int ll;
ll N, M;

class Graph
{
    ll V;
    list<ll> *adj;
    bool *visited;
    bool *inStack;
    bool *gender;
    bool DFS(ll u, bool val);
public:
    Graph(ll n)
    {
        V = n;
        adj = new list<ll>[V];
        visited = new bool[V];
        gender = new bool[V];
        inStack = new bool[V];
    }
    void addEdge(ll u, ll v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool DFS();
};

bool Graph::DFS(ll u, bool val)
{
    visited[u] = true;
    inStack[u] = true;
    gender[u] = val;
    val = !val;
    list<ll>::iterator it;
    ll v;
    for(it=adj[u].begin(); it!=adj[u].end(); ++it)
    {
        v = *it;
        if(!visited[v])
        {
            if(DFS(v, val))
                return true;
        }
        else
        {
            if(inStack[v] && gender[v]!=val)
                return true;
        }
    }
    return false;
}

bool Graph::DFS()
{
    for(ll i=0; i<V; ++i)
    {
        for(ll j=0; j<V; ++j)
            inStack[j] = false;
        if(!visited[i] && DFS(i, true))
            return true;
    }
    return false;
}

bool RunCode()
{
    scanf("%lld%lld", &N, &M);
    Graph g(N);
    ll x, y;
    for(int i=0; i<M; ++i)
    {
        scanf("%lld%lld", &x, &y);
        g.addEdge(x-1, y-1);
    }
    return g.DFS();
}

int main()
{
    bool ans;
    ll T;
    scanf("%lld", &T);

    for(ll i=1; i<=T; ++i)
    {
        ans = RunCode();
        printf("Scenario #%lld:\n", i);
        if(ans)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");
    }
    return 0;
}
