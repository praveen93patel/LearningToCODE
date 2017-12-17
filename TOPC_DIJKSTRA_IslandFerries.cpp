// DebugCode.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
typedef int lli;
#define INF 202020
#define MAX_I 50
#define MAX_F 15
bool visited[MAX_I][2000];    //[islands][10 bit ferries]
bool graph[MAX_I][MAX_I][MAX_F];
class node
{
public:
    lli island;
    lli ferry;          //10 bits used
    lli cost;
    node(int i, int f, int c)
    {
        island = i;
        ferry = f;
        cost = c;
    }
};

class myComparator
{
public:
    lli operator() (const node& a, const node& b)
    {
        return a.cost > b.cost;
    }
};

class IslandFerries
{
    lli I;
    lli F;
    priority_queue<node, vector<node>, myComparator> pq;
    vector<vector<lli> > stringToInt(vector<string> prices);
    void connections(vector<string> legs);
    void visitNearIsland(lli island, lli ferry, lli cost);
public:
    vector<lli> costs(vector<string> legs, vector<string> prices);
};

vector<lli> IslandFerries::costs(vector<string> legs, vector<string> prices)
{
    I = prices.size();
    F = legs.size();
    //cout<<"Test1"<<endl;
    vector<lli> route(I-1, INF);
    vector<vector<lli> > Prices = stringToInt(prices);
   // cout<<"Test2"<<endl;
    lli i, j, k;
    for(i=0; i<MAX_I; ++i)
        for(j=0; j<2000; ++j)
            visited[i][j] = false;
    for(i=0; i<MAX_I; ++i)
        for(j=0; j<MAX_I; ++j)
            for(k=0; k<MAX_F; ++k)
                graph[i][j][k] = false;
   // cout<<"Test3"<<endl;
    connections(legs);
    //cout<<"Test4"<<endl;
    lli cost, ferry, island;
    pq.push(node(0, 0, 0));
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
      //  cout<<"Test: "<<top.island<<" "<<top.ferry<<" "<<top.cost<<endl;
        if(visited[top.island][top.ferry])
            continue;
        visited[top.island][top.ferry] = true;
        if(top.island != 0)
            route[top.island-1] = min(route[top.island-1], top.cost);
        lli i, j, k;
        island = top.island;
        ferry = top.ferry;
        cost = top.cost;
        //cout<<"Test: "<<top.island<<" "<<top.ferry<<" "<<top.cost<<endl;
        visitNearIsland(island, ferry, cost);
       // cout<<"Test2: "<<top.island<<" "<<top.ferry<<" "<<top.cost<<endl;
		lli cost1, cost2, cost3;
		cost1 = cost2 = cost3 = cost;
		lli ferry1, ferry2, ferry3;
		ferry1 = ferry2 = ferry3 = ferry;
        for(i=0;i<F;++i)
        {
			if(ferry & (1<<i)) continue;
            cost1 = top.cost+Prices[top.island][i];
            ferry1 = top.ferry | (1<<i);
            visitNearIsland(island, ferry1, cost1);
            for(j=0;j<F;++j)
            {
                if(i==j)
                    continue;
                if(ferry & (1<<j)) continue;
                cost2 = cost1 + Prices[top.island][j];
                ferry2 = ferry1 | (1<<j);

                visitNearIsland(island, ferry2, cost2);
                for(k=0;k<F;++k)
                {
                    if(k==j || k==i)
                        continue;
                    if(ferry & (1<<k)) continue;
                    cost3 = cost2 + Prices[top.island][k];
                    ferry3 = ferry2 | (1<<k);
                    visitNearIsland(island, ferry3, cost3);
                }
            }
        }
    }
	for(i=0; i<I-1; ++i)
		if(route[i] == INF)
			route[i] = -1;
    return route;
}

void IslandFerries::visitNearIsland(lli island, lli ferry, lli cost)
{
    lli i, f, island2;
    for(i=0; i<F; ++i)
    {
        f = ferry&(1<<i);
        if(f)
        {
            f = ferry^(1<<i);
            for(island2=0; island2<I;++island2)
            {
                if(graph[island][island2][i])
                    pq.push(node(island2, f, cost));
            }
        }
    }
}
void IslandFerries::connections(vector<string> legs)
{
    lli N = legs.size();
    lli i, j, M, val;
    lli island1, island2;
	island1 = island2 = 0;
    for(i=0; i<N; ++i)
    {
        M = legs[i].size();
        j=0;
        while(j<M)
        {
            val = 0;
            while(j<M && legs[i][j]!=' ')
            {
                if(legs[i][j]=='-')
                {
                    island1=val;
                    val=0;
                }
                else
                {
                    val = 10*val + (legs[i][j]-'0');
                }
                ++j;
            }
            island2 = val;
            graph[island1][island2][i] = true;
            ++j;
        }
    }
}

vector<vector<lli> > IslandFerries::stringToInt(vector<string> prices)
{
    lli N = prices.size();
    vector<vector<lli> > ans;
    vector<lli> temp;
    lli i, j, M, val;
    for(i=0; i<N; ++i)
    {
        temp.clear();
        M=prices[i].size();
        j=0;
        while(j<M)
        {
            val = 0;
            while(j<M && prices[i][j]!=' ')
            {
                val = 10*val + (prices[i][j]-'0');
                ++j;
            }
            temp.push_back(val);
            ++j;
        }
        ans.push_back(temp);
    }
    return ans;
}

int main()
{
    vector<string> prices;
    vector<string> legs;
    /*legs.push_back("0-1 1-2 2-3"), legs.push_back("0-1 2-3");
    prices.push_back("1 10"), prices.push_back("20 25"),
    prices.push_back("50 50"), prices.push_back("1000 1000"),
    prices.push_back("1000 1000");*/
	legs.push_back("0-1"), legs.push_back("1-0"),
	legs.push_back("0-2"), legs.push_back("2-3");
	prices.push_back("1 1 1000 1000"),
	prices.push_back("1000 1000 10 100"),
	prices.push_back("1000 1000 1000 1000"),
	prices.push_back("1000 1000 1000 1000");
    IslandFerries IF;
    vector<lli> ans = IF.costs(legs, prices);
    for(lli i=0; i<ans.size(); ++i)
        cout<<ans[i]<<" ";
    cout<<endl;
	char ch;
	cin>>ch;
	cout<<ch;
    return 0;
}


//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//
