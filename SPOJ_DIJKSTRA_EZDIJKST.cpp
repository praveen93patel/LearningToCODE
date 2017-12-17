//#include"stdafx.h"
#include<iostream>
#include<vector>
#include<queue>
#include<list>
using namespace std;

typedef pair<int, int> pii;

class node
{
public:
    int v;
    int dist;
    node(int v, int d)
    {
        this->v = v;
        dist = d;
    }
};

class myComparator
{
public:
    int operator() (const node &a, const node &b)
    {
        return a.dist > b.dist;
    }
};

class Graph
{
    int N;
    bool *visited;
    list<pii> *adj;
    priority_queue<node, vector<node>, myComparator> pq;
public:
    Graph(int N)
    {
        this->N = N;
        visited = new bool[N];
        adj = new list<pii>[N];
        for(int i=0; i<N; ++i)
            visited[i] = false;
    }
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
    }
    int shortestPath(int source, int dest);
};

int Graph::shortestPath(int source, int dest)
{
    pq.push(node(source, 0));
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(top.v == dest)
            return top.dist;
        if(visited[top.v])
            continue;
        visited[top.v] = true;
        list<pii>::iterator it;
        for(it=adj[top.v].begin(); it!=adj[top.v].end(); ++it)
        {
            int u = (*it).first;
            int w = (*it).second;
            if(!visited[u])
                pq.push(node(u, top.dist+w));
        }
    }
    return -1;
}

void RunCode()
{
    int N, M;
    cin>>N>>M;
    Graph g(N);
    int u, v, w;
    for(int i=0; i<M; ++i)
    {
        cin>>u>>v>>w;
        g.addEdge(u-1,v-1,w);
    }
    cin>>u>>v;
    int ans = g.shortestPath(u-1, v-1);
    if(ans == -1)
        cout<<"NO"<<endl;
    else cout<<ans<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
        RunCode();
    return 0;
}
