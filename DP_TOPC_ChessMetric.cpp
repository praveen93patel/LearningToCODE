#include<iostream>
#include<vector>
using namespace std;

class ChessMetric
{
    int N;
    bool isValid(int a, int b);
public:
    long howMany(int size, vector<int> start, vector<int> end, int numMoves);
};

bool ChessMetric::isValid(int a, int b)
{
    if(a<0 || a>=N)
        return false;
    if(b<0 || b>=N)
        return false;
    return true;
}

long ChessMetric::howMany(int size, vector<int> start, vector<int> end, int numMoves)
{
    N = size;
    vector<vector<vector<long long> > > DP(numMoves+1, vector<vector<long long> >(size, vector<long long>(size, 0)));
    DP[0][start[0]][start[1]] = 1;
    int i, j, k, m, _x, _y;
    int x[] = { 0, 0, 1, 1, 1, 1, 1, 2, 2,-1,-1,-1,-1,-1,-2,-2};
    int y[] = { 1,-1, 0, 1, 2,-1,-2, 1,-1, 0, 1, 2,-1,-2, 1,-1};
    for(m = 0; m<numMoves; m++)
    {
        for(i=0; i<size; ++i)
        {
            for(j=0; j<size; ++j)
            {
                if(DP[m][i][j]==0)
                    continue;
                for(k=0; k<16; ++k)
                {
                    _x = i+x[k];
                    _y = j+y[k];
                    if(!isValid(_x, _y))
                        continue;
                    DP[m+1][_x][_y] += DP[m][i][j];
                }
            }
        }
    }
    return DP[numMoves][end[0]][end[1]];
}
