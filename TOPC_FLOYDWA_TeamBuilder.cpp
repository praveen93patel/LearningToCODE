#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define MAX_N 51
class TeamBuilder
{
    int N;
public:
    vector<int> specialLocations(vector<string> paths);
};

vector<int> TeamBuilder::specialLocations(vector<string> paths)
{
    N = paths.size();
    int i, j, k;
    for(k=0; k<N; ++k)
    {
        paths[k][k] = '1';
        for(i=0; i<N; ++i)
        {
            for(j=0; j<N; ++j)
            {
                if(i==j || paths[i][j] == '1')
                    continue;
                if(paths[i][k]=='1' && paths[k][j]=='1')
                    paths[i][j] = '1';
            }
        }
    }
    vector<int> ans(2, 0);
    int count;
    for(i=0;i<N;++i)
    {
        for(j=0;j<N;++j)
        {
            if(paths[i][j]=='0')
                break;
        }
        if(j==N)
            ans[0]++;
    }
    for(j=0;j<N;++j)
    {
        for(i=0; i<N;++i)
        {
            if(paths[i][j]=='0')
                break;
        }
        if(i==N)
            ans[1]++;
    }
    return ans;
}
