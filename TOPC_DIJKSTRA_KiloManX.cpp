#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

bool visited[32768];

class node
{
    int weapons;
    int shots;
public:
    node(int w, int s)
    {
        weapons = w;
        shots = s;
    }
    int getW() const { return weapons; }
    int getS() const { return shots; }
};

class myComparator
{
public:
    int operator() (const node& a, const node& b)
    {
        return a.getS() > b.getS();
    }
};

class KiloManX
{
    priority_queue<node, vector<node>, myComparator> pq;
    int numW;
public:
    KiloManX()
    {
        for(int i=0; i<32768; ++i)
            visited[i] = false;
    }
    int leastShots(vector<string> damageChart, vector<int> bossHealth);
};

int KiloManX::leastShots(vector<string> damageChart, vector<int> bossHealth)
{
    numW = damageChart.size();
    pq.push(node(0, 0));
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(visited[top.getW()])
            continue;
        visited[top.getW()] = true;
        if(top.getW() == (1<<numW)-1)
            return top.getS();
        for(int i=0; i<numW; ++i)
        {
            if((top.getW() >> i) & 1)
                continue;
            int best = bossHealth[i];
            for(int j=0; j<numW; ++j)
            {
                if(i==j)
                    continue;
                if(((top.getW() >> j) & 1) && damageChart[j][i] != '0')
                {
                    int shotsNeeded = bossHealth[i]/(damageChart[j][i]-'0');
                    if(bossHealth[i]%(damageChart[j][i]-'0') != 0)
                        shotsNeeded++;
                    best = min(best, shotsNeeded);
                }
            }
            pq.push(node(top.getW() | (1<<i), top.getS() + best));
        }
    }
}

int main()
{
    KiloManX kmx;
    vector<string> dc;
    vector<int> bh;
    dc.push_back("070");
    dc.push_back("500");
    dc.push_back("140");
    bh.push_back(150);
    bh.push_back(150);
    bh.push_back(150);
    cout<<kmx.leastShots(dc, bh)<<endl;
    return 0;
}
