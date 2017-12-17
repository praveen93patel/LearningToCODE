#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;

class grafixMask
{
    int *D;
    vector<vector<bool> > visited;
 	void stringToDim(string rec);
 	int DFS(int r, int c);
 	bool isValid(int r, int c);
 	public:
    grafixMask();
    vector<int> sortedAreas(vector<string> rectangles);
};
grafixMask::grafixMask()
{
    D = new int[4];
    vector<bool> tmp(600, false);
    for(int i=0; i<400; ++i)
        visited.push_back(tmp);
}
vector<int> grafixMask::sortedAreas(vector<string> rectangles)
{
    int N = rectangles.size();
    for(int i=0; i<N; ++i)
    {
        stringToDim(rectangles[i]);
        for(int j = D[0]; j<D[2]; ++j)
            for(int k = D[1]; k<D[3]; ++k)
                visited[j][k] = true;
    }
    vector<int> ans;
    for(int i=0; i<400; ++i)
    {
        for(int j=0; j<600; ++j)
        {
            if(!visited[i][j])
                ans.push_back(DFS(i, j));
        }
    }
    sort(ans.begin(), ans.end());
   return ans;
}
void grafixMask::stringToDim(string rec)
{
    int N = rec.size();
    int i=0;
    int j=0;
    int num;
    while(i<N)
    {
        num = 0;
        while(i<N && rec[i]!=' ')
        {
            num = 10*num + (int)(rec[i]-'0');
            ++i;
        }
        if(j<4)
            D[j] = num;
        ++j;
        ++i;
    }
}
int grafixMask::DFS(int r, int c)
{
    stack<pair<int, int> > S;
    S.push(make_pair(r, c));
    pair<int, int> p;
    int x[] = {0, 0, 1,-1};
    int y[] = {1,-1, 0, 0};
    int count = 0;
    while(!S.empty())
    {
        p = S.top();
        S.pop();
        r = p.first;
        c = p.second;
        visited[r][c] = true;
        ++count;
        for(int i=0; i<4; ++i)
        {
            if(isValid(r+x[i], c+y[i]))
                S.push(make_pair(r+x[i], c+y[i]));
        }
    }
    return count;
}

bool grafixMask::isValid(int r, int c)
{
    if(r<0 || r>399 || c<0 || c>599 || visited[r][c])
        return false;
    return true;
}
