#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int, int> pii;
bool visited[50][50][101]; // [pos][pos][bombs]
class node
{
public:
    pii pos;
    int bombs;
    int time;
    node(pii p, int b, int t)
    {
        pos = p;
        bombs = b;
        time = t;
    }
};

class myComparator
{
public:
    int operator() (const node& a, const node& b)
    {
        return a.time > b.time;
    }
};

class BombMan
{
    int N, M;
    pii startPos;
    pii endPos;
    priority_queue<node, vector<node>, myComparator> pq;
    int ax[4] = { 0, 0, 1,-1};
    int ay[4] = { 1,-1, 0, 0};
    bool isValid(pii p);
public:
    int shortestPath(vector<string> maze, int bombs);
};
int BombMan::shortestPath(vector<string> maze, int bombs)
{
    N = maze.size();
    M = maze[0].size();
    int i, j;
    for(i=0;i<N;++i)
    {
        for(j=0;j<M;++j)
        {
            if(maze[i][j]=='B')
                startPos.first = i , startPos.second = j;
            if(maze[i][j]=='E')
                endPos.first = i, endPos.second = j;
        }
    }
    pq.push(node(startPos, bombs, 0));
    int time;
    pii pos;
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(top.pos == endPos)
            return top.time;
        if(visited[top.pos.first][top.pos.second][top.bombs])
            continue;
        for(i=0; i<4; ++i)
        {
            pos.first = top.pos.first + ax[i];
            pos.second = top.pos.second + ay[i];
            time = top.time + 1;
            bombs = top.bombs;
            if(!isValid(pos))
                continue;
            if(maze[pos.first][pos.second] == '#' && bombs>0)
                pq.push(node(pos, bombs-1, time+2));
            else
                pq.push(node(pos, bombs, time));
        }
    }
    return -1;
}

bool BombMan::isValid(pii p)
{
    int x = p.first;
    int y = p.second;
    if(x<0 || x>=N || y<0 || y>=M)
        return false;
    return true;
}

int main()
{
    vector<string> maze;
    int bombs;
    maze.push_back("B.#.#.#...E");
    bombs = 2;
    BombMan bm;
    cout<<bm.shortestPath(maze, bombs)<<endl;
    char ch;
    cin>>ch;
    return 0;
}
