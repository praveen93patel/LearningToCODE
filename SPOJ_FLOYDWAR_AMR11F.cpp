#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

#define INF 10000007L

typedef long long ll;

void FloydWarshall(vector<vector<ll> > &T)
{
    ll N = T.size();
    ll i, j, k;
    for(k=1; k<N; ++k)
    {
        for(i=1; i<N; ++i)
        {
            for(j=1; j<N; ++j)
            {
                if(T[i][k]!=INF && T[k][j]!=INF && T[i][k]+T[k][j] < T[i][j])
                    T[i][j] = T[i][k]+T[k][j];
            }
        }
    }
}

ll ABS(ll x)
{
    if(x<0)
        x *= -1;
    return x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll T, N, M, F, Q, bi, bj, fi, fj, t;
    cin>>T;
    while(T--)
    {
        cin>>N>>F>>M;
        vector<vector<pair<ll, ll> > > tower(N+1);
        vector<vector<ll> > SPT(N+2*M+1, vector<ll>(N+2*M+1, INF));
        //vector<pair<ll, ll> > index(N+M+1);
        for(ll i=1; i<=N; ++i)
        {
            tower[i].push_back(make_pair(1, i));
            //index[i] = make_pair(i, 1);
        }
        for(ll i=1; i<N; ++i)
        {
            SPT[i][i] = 0;
            SPT[i][i+1] = SPT[i+1][i] = 1;
        }
        SPT[N][N] = 0;
        SPT[N][1] = SPT[1][N] = 1;

        for(ll i=1; i<=M; ++i)
        {
            cin>>bi>>fi>>bj>>fj>>t;
            ll ii, jj;
            ii = N+2*i-1;
            jj = N+2*i;
            //index[ii] = make_pair(bi, fi);
            //index[jj] = make_pair(bj, fj);

            SPT[ii][jj] = t;
            SPT[jj][ii] = t;

            for(ll x = 0; x<tower[bi].size(); ++x)
            {
                t = ABS(tower[bi][x].first - fi);
                SPT[ii][tower[bi][x].second] = t;
                SPT[tower[bi][x].second][ii] = t;
            }
            for(ll x = 0; x<tower[bj].size(); ++x)
            {
                t = ABS(tower[bj][x].first - fj);
                SPT[jj][tower[bj][x].second] = t;
                SPT[tower[bj][x].second][jj] = t;
            }
            tower[bi].push_back(make_pair(fi, ii));
            tower[bj].push_back(make_pair(fj, jj));
        }
        FloydWarshall(SPT);
        cin>>Q;
        while(Q--)
        {
            cin>>bi>>fi>>bj>>fj;

            ll ii, jj, val, val2, ans = INF;
            for(ll i=0; i<tower[bi].size(); ++i)
            {
                val = ABS(fi - tower[bi][i].first);
                ii = tower[bi][i].second;
                for(ll j=0; j<tower[bj].size(); ++j)
                {
                    jj = tower[bj][j].second;
                    val2 = val;
                    val2 += ABS(fj - tower[bj][j].first);
                    if(SPT[ii][jj] != INF && SPT[ii][jj] + val2<ans)
                        ans = SPT[ii][jj]+val2;
                }
            }
            if(bi==bj)
                ans = min(ans, ABS(fi-fj));
            cout<<ans<<endl;
        }
    }

    return 0;
}
