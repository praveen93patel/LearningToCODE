#include<iostream>
#include<string>
#include<queue>
#include<cstdio>
using namespace std;
typedef pair<int, int> pii;

bool board[8][8];

void visit(pii m)
{
    board[m.first][m.second] = true;
}

bool isValid(int x, int y)
{
    if(x<0 || x>=8 || y<0 || y>=8 || board[x][y])
        return false;
    return true;
}

bool IsEqual(pii a, pii b)
{
    if(a.first==b.first && a.second==b.second)
        return true;
    return false;
}

int MinMove(pii s, pii f)
{
    queue<pair<pii, int> > Q;
    Q.push(make_pair(s, 0));
    pair<pii, int> P;
    pii m;
    int val;
    visit(s);
    int ax[] = { 2, 2,-2,-2, 1, 1,-1,-1};
    int ay[] = { 1,-1, 1,-1, 2,-2, 2,-2};
    int x, y;
    while(!Q.empty())
    {
        P = Q.front();
        Q.pop();
        m = P.first;
        val = P.second;
        if(IsEqual(m, f))
        {
            return val;
        }
        for(int i=0;i<8;++i)
        {
            x=m.first+ax[i];
            y=m.second+ay[i];
            if(isValid(x, y) && !board[x][y])
                Q.push(make_pair(make_pair(x, y), val+1));
        }
    }
    return -1;
}

void RunCode()
{
    //string str;
    //getline(cin, str);
    //cin>>str;
    //cout<<str.size()<<endl;
    char str[5];
    scanf("%[^\n]%*c", str);
    pii start;
    pii finish;

    start.first = str[0]-'a';
    start.second = str[1]-'1';
    finish.first = str[3]-'a';
    finish.second = str[4]-'1';
    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<8; ++j)
            board[i][j] = false;
    }
    cout<<MinMove(start, finish)<<endl;
}

int main()
{
    int T;
    //cin>>T;
    scanf("%d\n", &T);
    while(T--)
        RunCode();
    return 0;
}
