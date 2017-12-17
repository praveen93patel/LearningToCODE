#include<iostream>
#include<vector>
#include<string>
#include<queue>
using namespace std;

#define DIM 500

struct node
{
    int x, y;
    int life;
};

class Escape
{
    node start;
    int visited[501][501];   // normal-0, harmful-1, deadly-2
    void Visit(node &n);
    bool isVisited(node &n);
    bool isValid(node &n);
    bool isDestination(node &n);
    void setHarmfulUtil(int x1, int x2, int y1, int y2, int val);
    void setHarmful(vector<string> &A, int lf=1);
    void setDeadly(vector<string> &A);
    void printVisited();
    queue<node> Q;
public:
    Escape()
    {
        start.x = 0;
        start.y = 0;
        start.life = 0;
        for(int i=0; i<=DIM; ++i)
            for(int j=0; j<=DIM; ++j)
                visited[i][j] = 0;
    }
    int lowest(vector<string> harmful, vector<string> deadly);
};

void Escape::printVisited()
{
    for(int i=0; i<=DIM; ++i)
    {
        for(int j=0; j<=DIM;++j)
            cout<<visited[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

int Escape::lowest(vector<string> harmful, vector<string> deadly)
{
    setHarmful(harmful);
   // printVisited();
    setDeadly(deadly);
   // printVisited();
    visited[start.x][start.y] = 0;
    Q.push(start);
    node curr, tmp;
    int _x[] = {0, 0, 1,-1};
    int _y[] = {1,-1, 0, 0};
    while(!Q.empty())
    {
        curr = Q.front();
        Q.pop();
        if(!isValid(curr))
            continue;
        Visit(curr);

        if(isDestination(curr))
            return curr.life;
        for(int i=0;i<4;++i)
        {
            tmp.x = curr.x+_x[i];
            tmp.y = curr.y+_y[i];

           // cout<<"NODE: "<<tmp.x<<" "<<tmp.y<<" "<<tmp.life<<endl;
            if(isValid(tmp))
            {
                tmp.life = curr.life+visited[tmp.x][tmp.y];
                Q.push(tmp);
            }
        }
    }
    //printVisited();
    return -1;
}

bool Escape::isValid(node &n)
{
    if(n.x<0 || n.x>DIM || n.y<0 || n.y>DIM || isVisited(n))
        return false;
    return true;
}

void Escape::Visit(node &n)
{
    visited[n.x][n.y] = 2;
}
bool Escape::isVisited(node &n)
{
    if(visited[n.x][n.y] < 2)
        return false;
    return true;
}
bool Escape::isDestination(node &n)
{
    if(n.x==DIM && n.y==DIM)
        return true;
    return false;
}
void Escape::setHarmfulUtil(int x1, int x2, int y1, int y2, int val)
{
    for(int i=x1; i<=x2; ++i)
        for(int j=y1; j<=y2; ++j)
            visited[i][j] = val;
}
void Escape::setHarmful(vector<string> &A, int lf)
{
    int N=A.size();
    int val, i, j, k, M;
    k=0;
    int  v[4];
    for(i=0;i<N;++i)
    {
        j=0;
        k=0;
        M = A[i].size();
        while(j<M)
        {
            val = 0;
            while(j<M && A[i][j] != ' ')
            {
                val = 10*val + (int)(A[i][j]-'0');
                ++j;
            }
            v[k++] = val;
            ++j;
        }
        setHarmfulUtil(min(v[0], v[2]), max(v[0], v[2]), min(v[1], v[3]), max(v[1], v[3]), lf);
    }
}
void Escape::setDeadly(vector<string> &A)
{
    setHarmful(A, 2);
}

int main()
{
    vector<string> h;
    vector<string> d;
    h.push_back("500 0 0 500");
    d.push_back("0 0 0 0");
    Escape E;
    cout<<E.lowest(h, d)<<endl;
}
