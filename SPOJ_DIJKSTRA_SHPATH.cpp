#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<unordered_map>
//#include<list>
#include<cstdio>
// optimizations :  vector / list
//                  unordered_map / map
//                  scanf,printf / cin, cout
//                  pq / set
using namespace std;
typedef int lli;
typedef pair<lli, lli> pii;
#define INF 200000

int M, u, v, w, cnt, ans;
char city[10];
char city2[10];

class node
{
public:
    lli city;
    lli dist;
    node(lli c, lli d)
    {
        city = c;
        dist = d;
    }
};

class myComparator
{
public:
    lli operator() (const node &a, const node &b)
    {
        return a.dist > b.dist;
    }
};

class Graph
{
    lli N;
    bool *visited;
    vector<pii> *adj;
public:
    unordered_map<string, int> MyMap;
    Graph(lli N)
    {
        this->N = N;
        visited = new bool[N];
        adj = new vector<pii>[N];
        for(lli i=0; i<N; ++i)
            visited[i] = false;
    }
    void addEdge(lli u, lli v, lli w)
    {
        adj[u].push_back(make_pair(v, w));
    }
    void init();
    lli shortestPath(lli city1, lli city2);
};

void Graph::init()
{
    for(int i=0;i<N;++i)
        visited[i] = false;

}

lli Graph::shortestPath(lli city1, lli city2)
{
    priority_queue<node, vector<node>, myComparator> pq;
    pq.push(node(city1, 0));
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(top.city == city2)
            return top.dist;
        if(visited[top.city])
            continue;
        visited[top.city] = true;
        //int u, v, w;
        u = top.city;
        vector<pii>::iterator it;
        for(it = adj[u].begin(); it!=adj[u].end(); ++it)
        {
            v = (*it).first;
            w = (*it).second;
            if(!visited[v])
                pq.push(node(v, top.dist+w));
        }
    }
    return INF;
}

void RunCode()
{
    lli N;
    scanf("%d", &N);
    Graph g(N);
    string ct;
    cnt = 0;
    for(int i=0; i<N; ++i)
    {
		cin>>ct;
        //scanf_s("%s", city);
        //ct = city;
        scanf("%d", &M);
        u = cnt;
        g.MyMap[ct] = cnt;
        ++cnt;
        while(M--)
        {
            scanf("%d%d", &v, &w);
            g.addEdge(u, v-1, w);
        }
    }
    scanf("%d", &M);
    while(M--)
    {
        //scanf_s("%s %s", city, city2);
		string ct1, ct2;
		cin>>ct1>>ct2;
        u = g.MyMap[ct1];
        v = g.MyMap[ct2];
        g.init();
        ans = g.shortestPath(u, v);
        printf("%d\n", ans);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
        RunCode();
    return 0;
}
