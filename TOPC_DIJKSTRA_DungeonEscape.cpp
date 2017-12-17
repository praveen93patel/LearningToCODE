//#include"stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int, int> pii;

bool visited[50][50][250]; //[level][easting][flood]

class node
{
public:
    pii pos;
    int flood;
    int cost;
    node(pii p, int f, int c)
    {
        pos = p;
        flood = f;
        cost = c;
    }
};

class myComparator
{
public:
    int operator() (const node& a, const node& b)
    {
        return a.cost > b.cost;
    }
};

class DungeonEscape
{
    int finalLevel;
    int N, M;
    pii pos;
    int flood;
    int cost;
    int TFL; //topmost flooded level
    priority_queue<node, vector<node>, myComparator> pq;
public:
    DungeonEscape()
    {
        for(int i=0; i<50; ++i)
            for(int j=0; j<50; ++j)
                for(int k=0; k<250; ++k)
                    visited[i][j][k] = false;
    }
    int exitTime(vector<string> up, vector<string> down, vector<string> east, vector<string> west, int startLevel, int startEasting);
};

int DungeonEscape::exitTime(vector<string> up, vector<string> down, vector<string> east, vector<string> west, int startLevel, int startEasting)
{
    N = up.size();
    M = up[0].size();
    finalLevel = -1;
    pos.first = startLevel;
    pos.second = startEasting;
    flood = 0;
    cost = 0;
    pq.push(node(pos, flood, cost));
    //int x, y;
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(top.pos.first == finalLevel)
            return top.cost;
        pos = top.pos;
        flood = top.flood;
        cost = top.cost;
        if(visited[pos.first][pos.second][flood])
            continue;
        visited[pos.first][pos.second][flood] = true;
        TFL = N - (flood/M);
        //up
        pos.first = top.pos.first -1;
        pos.second = top.pos.second;
        if(pos.first < TFL && up[top.pos.first][top.pos.second] != 'x')
        {
            flood = top.flood + up[top.pos.first][top.pos.second] - '0';
            cost = top.cost + up[top.pos.first][top.pos.second] - '0';
            pq.push(node(pos, flood, cost));
        }
        //down
        pos.first = top.pos.first +1;
        pos.second = top.pos.second;
        if(pos.first<TFL && pos.first<N && down[top.pos.first][top.pos.second] != 'x')
        {
            flood = top.flood + down[top.pos.first][top.pos.second] - '0';
            cost = top.cost + down[top.pos.first][top.pos.second] - '0';
            pq.push(node(pos, flood, cost));
        }
        //east
        pos.first = top.pos.first;
        pos.second = top.pos.second+1;
        if(pos.first<TFL && pos.second<M && east[top.pos.first][top.pos.second] != 'x')
        {
            flood = top.flood + east[top.pos.first][top.pos.second] - '0';
            cost = top.cost +  east[top.pos.first][top.pos.second] - '0';
            pq.push(node(pos, flood, cost));
        }
        //west
        pos.first = top.pos.first;
        pos.second = top.pos.second-1;
        if(pos.first<TFL && pos.second>=0 && west[top.pos.first][top.pos.second] != 'x')
        {
            flood = top.flood + west[top.pos.first][top.pos.second] - '0';
            cost = top.cost +  west[top.pos.first][top.pos.second] - '0';
            pq.push(node(pos, flood, cost));
        }
    }
    return -1;
}

int main()
{
    vector<string> u;
    vector<string> d;
    vector<string> e;
    vector<string> w;
	int x, y;
    u.push_back("xxxxxxxxx1"),
    u.push_back("xxxx999991"),
    u.push_back("x999999991");
    d.push_back("1111111111"),
    d.push_back("1111111111"),
    d.push_back("1111111111");
    e.push_back("1111122242"),
    e.push_back("2222222241"),
    e.push_back("2111111111");
    w.push_back("xxxxxxxxx1"),
    w.push_back("1111111111"),
    w.push_back("xxxxxxxxx1");
	/*u.push_back("0x4"),
    u.push_back("0x3"),
    u.push_back("0x3");
    d.push_back("0x9"),
    d.push_back("009"),
    d.push_back("0x9");
    e.push_back("0x9"),
    e.push_back("1x9"),
    e.push_back("009");
    w.push_back("0x9"),
    w.push_back("0x0"),
    w.push_back("009");*/
    x = 2;
    y = 0;
    DungeonEscape de;
    cout<<de.exitTime(u, d, e, w, x, y)<<endl;
    return 0;
}
