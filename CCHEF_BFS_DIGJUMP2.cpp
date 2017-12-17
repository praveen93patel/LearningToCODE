#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<cstdio>
using namespace std;
typedef pair<int, int> pii;
bool visited[100005];
char str[100005];
void RunCode()
{
    //string str;
    //cin>>str;
    scanf("%s", str);

    vector<int> occ[10];
     // N~=100000
    int i, j, d, jumps, ind, N;
    for(i=0;i<N;++i)
        visited[i] = false;
    i=0;
    while(str[i]!='\0')
    {
        d = str[i]-'0';
        occ[d].push_back(i);
        ++i;
    }
    N = i;
    queue<pii> Q;
    pii p;
    Q.push(make_pair(0, 0));
    visited[0] = true;
    int ans = N-1;
    while(!Q.empty())
    {
        p = Q.front();
        Q.pop();
        ind = p.first;
        jumps = p.second;
        //cout<<ind<<" "<<jumps<<endl;
        if(ind == N-1)
        {
            ans = jumps;
            break;
        }
        i = ind-1;
        j = jumps+1;
        if(i>0 && !visited[i])
        {
            Q.push(make_pair(i, j));
            visited[i] = true;
        }
        i = ind+1;
        if(i<N && !visited[i])
        {
            Q.push(make_pair(i, j));
            visited[i] = true;
        }
        d = str[ind]-'0';
        for(vector<int>::iterator it = occ[d].begin(); it!=occ[d].end(); ++it)
        {
            if(!visited[*it])
            {
                Q.push(make_pair(*it, j));
                visited[*it] =true;
            }
        }
        occ[d].clear();
    }
    cout<<ans<<endl;
}

int main()
{
    RunCode();
    return 0;
}
