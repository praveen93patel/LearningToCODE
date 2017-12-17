#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long int lli;
typedef pair<lli, lli> pii;
class node
{
public:
    pii pos;
    lli ammu;
    node(pii p, lli a)
    {
        pos = p;
        ammu = a;
    }
};

class myComparator
{
public:
    lli operator() (const node& a, const node& b)
    {
        return a.ammu > b.ammu;
    }
};

class TheEscape
{
    lli N;
    pii village;
    map<pii, bool> visited;
    priority_queue<node, vector<node>, myComparator> pq;
    lli square(lli a) { return a*a; }
public:
    lli minAmmu();
};

lli TheEscape::minAmmu()
{
    cin>>N;
    vector<pii> watchT(N+1);
    pii pos;
    lli i;
    lli ammu;
    for(i=0; i<N+1; ++i)
    {
        cin>>pos.first>>pos.second;
        watchT[i] = pos;
        visited[pos] = false;
    }
    village = pos;
    //ammu = 0;
    pos = make_pair(0, 0);
    pq.push(node(pos, 0));
    visited[pos] = false;
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(top.pos == village)
            return top.ammu;
        if(visited[top.pos])
            continue;
        visited[top.pos] = true;
        for(i=0; i<=N; ++i)
        {
            if(!visited[watchT[i]])
            {
                ammu = square(watchT[i].first-top.pos.first) + square(watchT[i].second-top.pos.second);
                ammu += top.ammu;
                pq.push(node(watchT[i], ammu));
            }
        }
    }
    return square(village.first)+square(village.second);
}

int main()
{
    TheEscape esc;
    cout<<esc.minAmmu()<<endl;
    return 0;
}
