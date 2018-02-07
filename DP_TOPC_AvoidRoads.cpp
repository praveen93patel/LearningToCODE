#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

class AvoidRoads
{
    int N;
    vector<vector<int> > bura;
    void printBura();
    bool isBad(int x1, int y1, int x2, int y2);
public:
    long numWays(int width, int height, vector<string> bad);
};

bool AvoidRoads::isBad(int x1, int y1, int x2, int y2)
{
    for(int i=0; i<N; ++i)
    {
        if((bura[i][0]==x1 && bura[i][1]==y1) && (bura[i][2]==x2 && bura[i][3]==y2))
            return true;
        if((bura[i][0]==x2 && bura[i][1]==y2) && (bura[i][2]==x1 && bura[i][3]==y1))
            return true;
    }
    return false;
}

void AvoidRoads::printBura()
{
    for(int i=0; i<N;++i)
        cout<<bura[i][0]<<" "<<bura[i][1]<< " " <<bura[i][2]<<" "<<bura[i][3]<<endl;
}

long AvoidRoads::numWays(int width, int height, vector<string> bad)
{
    N = bad.size();
    vector<int> temp;
    for(int i=0; i<N; ++i)
    {
        temp.clear();
        string b = bad[i];
        int M = b.size();
        int j=0;
        int x = 0;
        while(j<M)
        {
            x = 0;
            while(j<M && b[j]!=' ')
            {
                x = 10*x + (b[j]-'0');
                ++j;
            }
            temp.push_back(x);
            ++j;
        }
        bura.push_back(temp);
    }
    printBura();
    ++width;
    ++height;
    vector<vector<long> > DP(width, vector<long>(height, 0));
    DP[0][0] = 1;
    int i, j;
    for(j=1; j<height; ++j)
        if(!isBad(0, j, 0, j-1))
            DP[0][j] = DP[0][j-1];
    for(i=1; i<width; ++i)
        if(!isBad(i, 0, i-1, 0))
            DP[i][0] = DP[i-1][0];
    cout<<isBad(1, 0, 0, 0)<<endl;
    for(i=1; i<width; ++i)
    {
        for(j=1; j<height; ++j)
        {
            DP[i][j] = 0;
            if(!isBad(i, j, i-1, j))
                DP[i][j] += DP[i-1][j];
            if(!isBad(i, j, i, j-1))
                DP[i][j] += DP[i][j-1];
        }
    }
    for(i=0; i<width; ++i)
    {
        cout<<endl;
        for(j=0; j<height; ++j)
        {
            cout<<setw(4)<<DP[i][j]<<" ";
        }
    }
    cout<<endl;
    return DP[width-1][height-1];
}

int main()
{
    vector<string> bbad;
    bbad.push_back("0 0 0 1");
    bbad.push_back("6 6 5 6");
    AvoidRoads ar;
    cout<<ar.numWays(6, 6, bbad);
    return 0;
}
