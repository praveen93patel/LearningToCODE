#include<iostream>
#include<set>
#include<vector>
using namespace std;

#define INF 1000006
#define MAXN 100005
#define parent(i) (i-1)/2
#define leftChild(i) 2*i+1
#define rightChild(i) 2*i+2

vector<pair<int, int> > ad[MAXN];
int DIST[MAXN], MAP[MAXN];
int N, M;
pair<int, int> HEAP[MAXN];
int HeapSize;

void MinHeapify(int i)
{
    while(i<HeapSize)
    {
        int smallest = i;
        if(leftChild(i)<HeapSize && HEAP[leftChild(i)].first<HEAP[smallest].first)
            smallest = leftChild(i);
        if(rightChild(i)<HeapSize && HEAP[rightChild(i)].first<HEAP[smallest].first)
            smallest = rightChild(i);
        if(smallest == i)
            return;
        pair<int, int> p = HEAP[i];
        HEAP[i] = HEAP[smallest];
        HEAP[smallest] = p;
        MinHeapify(smallest);
    }
}

int HeapExtractMin()
{
    if(HeapSize==0)
        return -1;
    --HeapSize;
    int min = HEAP[0].second;
    HEAP[0] = HEAP[HeapSize];
    MinHeapify(0);
    return min;
}

void HeapInsert(pair<int, int> p)
{
    HEAP[HeapSize] = p;
    int i = HeapSize++;
    while(i>0 && HEAP[parent(i)].first > HEAP[i].first)
    {
        p = HEAP[i];
        HEAP[i] = HEAP[parent(i)];
        HEAP[parent(i)] = p;
        i = parent(i);
    }
}

void ShortestPath()
{
    for(int z = 0; z<N; z++)
    {
        int u = HeapExtractMin();    //HEAP implementation
        if(u==-1 || u==N-1)
            return;

        for(int i=0; i<ad[u].size(); ++i)
        {
            int v = ad[u][i].first;
            int d = ad[u][i].second;
            if(DIST[u] + d < DIST[v])
            {
                DIST[v] = DIST[u] + d;
                HeapInsert(make_pair(DIST[v], v));
            }
        }
    }
    return;
}

int main()
{
    int x, y;
    cin>>N>>M;
    set<int> adj[N];
    for(int i=0; i<M; ++i)
    {
        cin>>x>>y;
        --x, --y;
        if(x!=y)
            adj[x].insert(y);
    }

    for(int i=0; i<N; ++i)
    {
        set<int>::iterator it;
        for(it = adj[i].begin(); it!=adj[i].end(); ++it)
        {
            y = *it;
            ad[i].push_back(make_pair(y, 0));
            ad[y].push_back(make_pair(i, 1));
        }
    }

    for(int i=0; i<N; ++i)
    {
        DIST[i] = INF;
    }
    HEAP[0] = make_pair(0, 0);
    HeapSize = 1;
    DIST[0] = 0;
    ShortestPath();
    if(DIST[N-1]==INF)
        cout<<"-1"<<endl;
    else
        cout<<DIST[N-1]<<endl;
    return 0;
}
