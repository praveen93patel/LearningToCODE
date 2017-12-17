#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
//bool visited[20][20][20][20];
struct node
{
    int x1, y1;
    int x2, y2;
    int steps;
};

class PathFinding
{
    int M, N;
    bool visited[20][20][20][20];
    queue<node> Q;
    node start;
    bool isVisited(node &nd);
    bool valid(node &nd, vector<string> &board);
    bool cross(node &a, node &b);
    bool exchangePos(node &nd);
    void getStart(vector<string> &board);
public:
    PathFinding();
    int minTurns(vector<string> board);
};

PathFinding::PathFinding()
{
    for(int i=0; i<20; ++i)
        for(int j=0; j<20; ++j)
            for(int k=0; k<20; ++k)
                for(int l=0; l<20; ++l)
                    visited[i][j][k][l] = false;
}

void PathFinding::getStart(vector<string> &board)
{
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            if(board[i][j] == 'A')
                start.x1 = i, start.y1 = j;
            else if(board[i][j] == 'B')
                start.x2 = i, start.y2 = j;
        }
    }
    start.steps = 0;
}

int PathFinding::minTurns(vector<string> board)
{
    M = board.size();
    N = board[0].size();
    visited[start.x1][start.y1][start.x2][start.y2] = true;
    getStart(board);
    Q.push(start);
    node curr, tmp;
    while(!Q.empty())
    {
        curr = Q.front();
        Q.pop();
        visited[curr.x1][curr.y1][curr.x2][curr.y2] = true;
        if(exchangePos(curr))
            return curr.steps;
        for(int dx1 = -1; dx1<=1; ++dx1)
            for(int dy1 = -1; dy1<=1; ++dy1)
                for(int dx2 = -1; dx2<=1; ++dx2)
                    for(int dy2 = -1; dy2<=1; ++dy2)
                    {
                        tmp.x1 = curr.x1+dx1;
                        tmp.y1 = curr.y1+dy1;
                        tmp.x2 = curr.x2+dx2;
                        tmp.y2 = curr.y2+dy2;
                        tmp.steps = curr.steps+1;
                        if(valid(tmp, board) && !isVisited(tmp) && !cross(curr, tmp))
                            Q.push(tmp);
                    }
    }
    return -1;
}

bool PathFinding::isVisited(node &nd)
{
    return visited[nd.x1][nd.y1][nd.x2][nd.y2];
}

bool PathFinding::cross(node &a, node &b)
{
    if(a.x1==b.x2 && a.y1==b.y2 && a.x2==b.x1 && a.y2==b.y1)
        return true;
    return false;
}

bool PathFinding::exchangePos(node &nd)
{
    if(nd.x1==start.x2 && nd.y1==start.y2 && nd.x2==start.x1 && nd.y2==start.y1)
        return true;
    return false;
}

bool PathFinding::valid(node &nd, vector<string> &board)
{
    if(nd.x1<0 || nd.x1>=M || nd.y1<0 || nd.y1>=N || nd.x2<0 || nd.x2>=M || nd.y2<0 || nd.y2>=N)
        return false;
    if(visited[nd.x1][nd.y1][nd.x2][nd.y2])
        return false;
    if(board[nd.x1][nd.y1]=='X' || board[nd.x2][nd.y2]=='X')
        return false;
    return true;
}

int main()
{
    vector<string> board;
    board.push_back("...A.XXXXX.....");
    board.push_back(".....XXXXX.....");
    board.push_back("...............");
    board.push_back(".....XXXXX.B...");
    board.push_back(".....XXXXX.....");
    PathFinding p;
    cout<<p.minTurns(board)<<endl;
    return 0;
}
