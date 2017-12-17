#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<stack>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    int *visited;
public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
        visited = new int[V];
        for(int i=0;i<V;++i)
            visited[i] = -1;
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool DFS(int u, int csm);
    long howMany();
};

long Graph::howMany()
{
    long ans=0;
    for(int i=0; i<V; ++i)
    {
        if(visited[i] != -1)
        {
            ++ans;
            if(!DFS(i, 0))
                return -1;
        }
    }
    return 2*ans;
}
bool Graph::DFS(int u, int csm)
{
    visited[u] = csm;
    list<int>::iterator it;
    for(it=adj[u].begin(); it!=adj[u].end(); ++it)
    {
        if(visited[*it] == csm)
            return false;
    }
    for(it=adj[u].begin(); it!=adj[u].end(); ++it)
    {
        if(visited[*it] == -1 && !DFS(*it, 1-csm))
            return false;
    }
    return true;
}

class Marketing
{
    long ways;
    Graph *g;
    void stringToEdges(int i, string cmp);
public:
    Marketing()
    {
        ways = 0;
    }
    long howMany(vector<string> compete);
};

void Marketing::stringToEdges(int u, string cmp)
{
    int N = cmp.size();
    int i=0;
    int num;
    while(i<N)
    {
        num = 0;
        while(i<N && cmp[i]!=' ')
        {
            num = 10*num + (int)(cmp[i]-'0');
            ++i;
        }
        g->addEdge(u, num);
        ++i;
    }
}

long Marketing::howMany(vector<string> compete)
{
    int N = compete.size();
    g = new Graph(N);
    for(int i=0; i<N; ++i)
        stringToEdges(i, compete[i]);
    return g->howMany();
}
