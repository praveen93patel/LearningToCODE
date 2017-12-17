#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<unordered_map>
#include<map>
using namespace std;
typedef long long int lli;
typedef pair<lli, lli> pii;
typedef pair<bool, lli> pbi;

#define INF 202020

class node
{
public:
    pii pos;
    lli cost;
    lli dir;
    lli forwd;
    node(pii p, lli c, lli d, lli f)
    {
        pos = p;
        cost = c;
        dir = d;
        forwd = f;
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

class RoboCourier
{
    lli num;
    lli dir, cost, forwd;
    pii pos;
    lli ax[6] = { 0, 1, 1, 0,-1,-1};
    lli ay[6] = { 2, 1,-1,-2,-1, 1};
    //vector<node> Scout;
    priority_queue <node, vector<node>, myComparator> pq;
    map<pii, pbi> visited;
    pii fin;
public:
    lli timeToDeliver(vector<string> path);
};

lli RoboCourier::timeToDeliver(vector<string> path)
{
    lli N = path.size();
    lli M;
    dir = 0;
    pos = make_pair(0, 0);
    visited[pos] = make_pair(false, 0);
    for(lli i=0; i<N; ++i)
    {
        M = path[i].size();
        for(lli j=0; j<M; ++j)
        {
            //cout<<path[i][j]<<" ::: "<<dir<<endl;
            if(path[i][j] == 'F')
            {
                visited[pos].second = visited[pos].second | (1<<dir);
                //cout<<"Test: "<<pos.first<<" "<<pos.second<<" : "<<visited[pos].second<<endl;
                pos.first += ax[dir];
                pos.second += ay[dir];
                //cout<<"Mid: "<<pos.first<<" "<<pos.second<<" : "<<dir<<endl;
                if(visited.find(pos) == visited.end())
                {
                    visited[pos] = make_pair(false, 0);
                }
                visited[pos].second = visited[pos].second | (1<<((dir+3)%6));
            }
            else if(path[i][j] == 'L')
            {
                dir = (dir+5)%6;
            }
            else
            {
                dir = (dir+1)%6;
            }
        }
    }
    fin = pos;
    //cout<<"start : "<<0<<" "<<0<<endl;
    //cout<<"end   : "<<fin.first<<" "<<fin.second<<endl;
    dir = 0;
    pos = make_pair(0, 0);
    pq.push(node(pos, 0, 0, 0));
    // node(pos, cost, dir, forwd)
    lli valid;
    while(!pq.empty())
    {
        node top = pq.top();
        pq.pop();
        if(visited[top.pos].first)
            continue;
        visited[top.pos].first = true;
        valid = visited[top.pos].second;
        //cout<<"Test2: "<<top.pos.first<<" "<<top.pos.second<<" : "<<visited[top.pos].second<<endl;
        //cout<<"Test3: "<<((valid>>0)&1)<<endl;
        if(top.pos == fin)
            return top.cost;
        for(lli i=0; i<6; ++i)
        {
            dir = (top.dir+i)%6;
            //cout<<"dir: "<<dir<<" : ";
            lli val = (valid>>dir)&1;
            //cout<< val<<endl;
            if(val == 0)
                continue;
            //cout<<"dir2: "<<dir<<endl;
            pos.first = top.pos.first + ax[dir];
            pos.second = top.pos.second + ay[dir];
            cost = top.cost;

            switch(i)
            {
            case 0:
                forwd = top.forwd+1;
                cost = cost + 2 + ((forwd<=2) ? 2 : 0);
                //cout<<"Cost: "<<cost<<endl;
                break;
            case 1:
            case 5:
                forwd = 1;
                cost = cost + 3 + 4;
                //cout<<"Cost: "<<cost<<endl;
                break;
            case 2:
            case 4:
                forwd = 1;
                cost = cost + 6 + 4;
                //cout<<"Cost: "<<cost<<endl;
                break;
            default:
                //cout<<"Not a Error"<<endl;
                forwd = 1;
                cost = cost + 9 + 4;
            }
            if((visited.find(pos) != visited.end()) && !visited[pos].first)
            {
                pq.push(node(pos, cost, dir, forwd));
            }
        }
    }
    return -1;
}

int main()
{
    vector<string> str;
    //str.push_back("FRRFLLFLLFRRFLF");
    //str.push_back("FFFFFFFFFRRFFFFFFRRFFFFF");
    //str.push_back("FLLFFFFFFLLFFFFFFRRFFFF");
    //str.push_back("RFLLF");
    //str.push_back("FLFRRFRFRRFLLFRRF");
    /*str.push_back("LLFLFRLRRLRFFLRRRRFFFLRFFRRRLLFLFLLRLRFFLFRRFFFLFL"),
    str.push_back("RLFFRRLRLRRFFFLLLRFRLLRFFLFRLFRRFRRRFRLRLRLFFLLFLF"),
    str.push_back("FRFLRFRRLLLRFFRRRLRFLFRRFLFFRLFLFLFRLLLLFRLLRFLLLF"),
    str.push_back("FFLFRFRRFLLFFLLLFFRLLFLRRFRLFFFRRFFFLLRFFLRFRRRLLR"),
    str.push_back("FFFRRLLFLLRLFRRLRLLFFFLFLRFFRLRLLFLRLFFLLFFLLFFFRR"),
    str.push_back("LRFRRFLRRLRRLRFFFLLLLRRLRFFLFRFFRLLRFLFRRFLFLFFLFR"),
    str.push_back("RFRRLRRFLFFFLLRFLFRRFRFLRLRLLLLFLFFFLFRLLRFRLFRLFR"),
    str.push_back("LLFLFRLFFFFFFFRRLRLRLLRFLRLRRRRRRRRLFLFLFLRFLFRLFF"),
    str.push_back("RLFRRLLRRRRFFFRRRLLLLRRLFFLLLLLRFFFFRFRRLRRRFFFLLF"),
    str.push_back("FFFFLRRLRFLLRRLRLRFRRRRLFLLRFLRRFFFRFRLFFRLLFFRRLL");
    */
    str.push_back("RFLLFLFLFRFRRFFFRFFRFFRRFLFFRLRRFFLFFLFLLFRFLFLRFF"),
    str.push_back("RFFLFLFFRFFLLFLLFRFRFLRLFLRRFLRFLFFLFFFLFLFFRLFRLF"),
    str.push_back("LLFLFLRLRRFLFLFRLFRF");
    RoboCourier rc;
    cout<<rc.timeToDeliver(str)<<endl;
    return 0;

}
