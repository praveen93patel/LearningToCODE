#include<iostream>
#include<cstdio>
using namespace std;

#define INF 202020

typedef int lli;

int Tree[100001];
int A[100001][2];

class NICEDAY
{
    lli N;
    void update(lli idx, lli val);
    lli read(lli idx);
    void init();
public:
    lli excellentContestants();
};

void NICEDAY::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] = min(Tree[idx], val);
        idx += (idx & (-idx));
    }
}

lli NICEDAY::read(lli idx)
{
    lli ans = INF;
    while(idx>0)
    {
        ans = min(ans, Tree[idx]);
        idx -= (idx & (-idx));
    }
    return ans;
}

void NICEDAY::init()
{
    for(int i=0; i<=N; ++i)
        Tree[i] = INF;
}

lli NICEDAY::excellentContestants()
{
    cin>>N;
    //scanf("%d", &N);
    init();
    int i, x;
    for(i=0; i<N; ++i)
    {
        //scanf("%d", &x);//
        cin>>x;
        //scanf("%d %d", &A[x][0], &A[x][1]); //
        cin>>A[x][0]>>A[x][1];

    }
    int ans = 0;
    int bi, ci, cj;
    for(i=1; i<=N; ++i)
    {
        bi = A[i][0];
        ci = A[i][1];
        cj = read(bi-1);
        if(cj>ci)
            ++ans;
        update(bi, ci);
    }
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    lli T;
    cin>>T;
    //scanf("%d", &T);
    NICEDAY nd;
    while(T--)
    {
      //  printf("%d\n", nd.excellentContestants());
        cout<<nd.excellentContestants()<<endl;
    }
    return 0;
}
