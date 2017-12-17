#include<iostream>
#include<vector>
#include<string>
#include<list>

using namespace std;

class Graph
{
    int V;
    list<pair<int, int> > *adj;
    int *visited;
    int *cost;
    int DFS(int u);
public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<pair<int, int> >[V];
        visited = new int[V];
        cost = new int[V];
        for(int i=0; i<V; ++i)
        {
            visited[i] = cost[i] = 0;
        }
    }
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
    }
    int howLong();
};

int Graph::DFS(int u)
{
    if(visited[u])
        return cost[u];
    visited[u] = true;
    int dist, max_dist = 0;
    int v, w;
    list<pair<int, int> >::iterator it;
    pair<int, int> p;
    for(it = adj[u].begin(); it!= adj[u].end(); ++it)
    {
        p = *it;
        v = p.first;
        w = p.second;
        dist = DFS(v) + w;
        max_dist = max(max_dist, dist);
    }
    cost[u] = max_dist;
    return cost[u];
}

int Graph::howLong()
{
    int ans = 0;
    int d;
    for(int i=0; i<V; ++i)
    {
        d = DFS(i);
        ans = max(ans, d);
    }
    return ans;
}

class Circuits
{
    Graph *g;
    void addEdges(int u, string &connect, string &cost);
public:
    int howLong(vector<string> connects, vector<string> costs);
};
void Circuits::addEdges(int u, string &connect, string &cost)
{
    int N = connect.size();
    int i = 0;
    int j, v, w;
    while(i<N)
    {
        v = w = 0;
        j = i;
        while(j<N && connect[j]!=' ')
        {
            v = 10*v + (int)(connect[j]-'0');
            ++j;
        }
        j = i;
        while(j<N && cost[j]!=' ')
        {
            w = 10*w + (int)(cost[j]-'0');
            ++j;
        }
        g->addEdge(u, v, w);
        i=j+1;
    }
}
int Circuits::howLong(vector<string> connects, vector<string> costs)
{
    int N = connects.size();
    g = new Graph(N);
    for(int i=0; i<N; ++i)
    {
        addEdges(i, connects[i], costs[i]);
    }
    return g->howLong();
}
