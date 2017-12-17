#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<list>
using namespace std;

int N;

class Graph
{
    int V;
    pair<int, bool> *adj;
    bool *visited;
    bool *st;
    bool DFS(int u, bool val);
public:
    Graph()
    {
        V=N;
        adj = new pair<int, bool>[V];
        visited = new  bool[V];
        st = new bool[V];
        for(int i=0; i<V; ++i)
            visited[i] = false;
    }
    void addEdge(int u, int v, bool w);
    bool DFS();
};

void Graph::addEdge(int u, int v, bool w)
{
    adj[u] = make_pair(v, w);
}

bool Graph::DFS(int u, bool val)
{
    visited[u] = true;
    st[u] = val;
    int v;
    bool w;
    v = adj[u].first;
    w = adj[u].second;
    val = (st[u] == true) ? w : !w;
    if(!visited[v])
    {
        return DFS(v, val);
    }
    else
    {
        if(st[v]^val)
            return false;
    }
    return true;
}

bool Graph::DFS()
{
    for(int i=0; i<V; ++i)
    {
        for(int j=0; j<V; ++j)
            visited[j] = false;
        if(!DFS(i, true))
        {
            //cout<<"paradox"<<endl;
            return false;
        }
    }
    //cout<<"not paradox"<<endl;
    return true;
}

void RunCode()
{
    while(1)
    {
        cin>>N;
        if(N==0)
            break ;
        int i, j, v;
        bool w;
        string str;
        Graph g;
        for(i=0;i<N;i++)
        {
            cin>>v>>str;
            int M=str.size();
            //cout<<str<<" "<<M;
            /*v=0;
            int j=0;
            while(j<M && str[j]!=' ')
            {
                v = 10*v + (int)(str[j]-'0');
                ++j;
            }*/
            //cout<<str[0]<< " "<<str[1]<<endl;
            w = (str[0] == 't') ? true: false;
            g.addEdge(i, v-1, w);
        }
        if(!g.DFS())
            cout<<"PARADOX"<<endl;
        else
            cout<<"NOT PARADOX"<<endl;
    }
}

int main()
{
    RunCode();
    return 0;
}
