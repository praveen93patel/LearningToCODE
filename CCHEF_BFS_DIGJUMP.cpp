#include<iostream>
#include<queue>
#include<list>
#include<cstdio>
#include<string>
using namespace std;

int parent[100005];
int index[10];

class Graph
{
    int V;
    list<int> *adj;
    bool *visited;
    queue<pair<int, int> > Q;
public:
    Graph(int N)
    {
        V = N;
        adj = new list<int>[V];
        visited = new bool[V];
        for(int i=0; i<V; ++i) visited[i] = false;
    }
    void addEdge(int u, int v);
    int BFS();
};
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
int Graph::BFS()
{
    int u, v, d;
    visited[0] = true;
    Q.push(make_pair(0, 0));
    pair<int, int> p;
    while(!Q.empty())
    {
        p = Q.front();
        u = p.first;
        d = p.second;
        //6cout<<u<<" "<<d<<endl;
        Q.pop();
        if(u==V-1)
            return d;
        list<int>::iterator itr;
        for(itr = adj[u].begin(); itr!= adj[u].end(); ++itr)
        {
            v = *itr;
            if(!visited[v])
            {
                visited[v] = true;
                Q.push(make_pair(v, d+1));
            }
        }
    }
    return V-1;
}

void RunCode()
{
    string str;
    cin>>str;
    int N = str.size();
    Graph g(N);
    int d, j;
    for(int i=0; i<10; ++i)
        index[i] = -1;
    for(int i=0; i<N; ++i)
        parent[i] = -1;
    for(int i=0;i<N;++i)
    {
        if(i!=N-1)
            g.addEdge(i, i+1);
        d = str[i]-'0';
        for(j=0; j<i; ++j)
        {
            int k = j;
            if(str[j]-'0' == d)
                g.addEdge(i, j);
            j++;
            while(j<i && str[j]-'0' == d)
                j++;
            if(j-1 != k)
                g.addEdge(i, j);

        }
    }
    //cout<<"Test1"<<endl;
    //cout<<g.BFS()<<endl;
    printf("%d\n", g.BFS());
}

int main()
{
    RunCode();
    return 0;
}
