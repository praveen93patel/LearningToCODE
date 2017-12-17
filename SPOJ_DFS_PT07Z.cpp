#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    bool *visited;
    bool *inStack;
    int *d1;
    int *d2;
    int DFS(int u, int val);
    int max_path;
public:
    Graph(int N)
    {
        V = N;
        adj = new list<int>[V];
        visited = new bool[V];
        inStack = new bool[V];
        d1 = new int[V];
        d2 = new int[V];
        max_path = 0;
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int DFS();
};

int Graph::DFS(int u, int val)
{
    visited[u] = true;
    d1[u] = val;
    list<int>::iterator itr;
    int v, max1, max2, ret;
    max1 = max2 = -1;
    for(itr = adj[u].begin(); itr != adj[u].end(); ++itr)
    {
        v = *itr;
        if(!visited[v])
        {
            ret = DFS(v, val+1);
            if(max1==-1)
                max1 = ret;
            else if(ret > max1)
            {
                max1 = ret;
                max2 = max1;
            }
            else if(ret> max2)
            {
                max2 = ret;
            }

        }
    }
    if(max1==-1)
        max1 = 0;
    if(max2 == -1)
        max2 = 0;
    d1[u] = max(d1[u], max1+max2);
    return max1;
}

int Graph::DFS()
{
    for(int i=0;i<V;++i)
    {
        visited[i] = inStack[i] = false;
    }
    for(int i=0; i<V; ++i)
    {
        if(!visited[i])
        {
            visited[i] = true;
            DFS(i, 0);
        }
    }
    int _max=0;
    for(int i=0; i<V; ++i)
    {
        //cout<<"dist: "<<d1[i]<<" "<<d2[i]<<endl;
        _max = max(_max, max(d1[i], d2[i]));
        //cout<<"max: "<<_max<<endl;
    }
    return _max;
}

void RunCode()
{
    int N;
    cin>>N;
    Graph g(N);
    int u, v;
    for(int i=0; i<N-1; ++i)
    {
        cin>>u>>v;
        g.addEdge(u-1, v-1);
    }
    cout<<g.DFS()<<endl;
}

int main()
{
    RunCode();
    return 0;
}

