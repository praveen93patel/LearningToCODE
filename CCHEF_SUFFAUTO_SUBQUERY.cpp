#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

#define MAXLEN 200005
#define cti(x) (x-'a')
string S;
int ss;

struct state
{
    int len, link;
    bool Clone;
    int cnt;
    int next[26];
};

state st[2*MAXLEN];
int sz, last;

void sa_init()
{
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].Clone = false;
    st[0].cnt = 1;
    sz++;
    for(int i=0; i<2*MAXLEN; ++i)
    {
        st[i].cnt = 0;
        st[i].Clone = false;
        for(int j = 0; j<26; ++j)
            st[i].next[j] = -1;
    }
}

void sa_extend(char c)
{
    int curr = sz++;
    st[curr].len = st[last].len + 1;
    st[curr].cnt = 1;
    int p;
    for(p = last; p!=-1 && st[p].next[cti(c)]==-1; p = st[p].link)
        st[p].next[cti(c)] = curr;
    if(p==-1)
        st[curr].link = 0;
    else
    {
        int q = st[p].next[cti(c)];
        if(st[p].len+1 == st[q].len)
            st[curr].link = q;
        else
        {
            int clone = sz++;
            st[clone].len = st[p].len +1;
            st[clone].link = st[q].link;
            st[clone].Clone = true;
            for(int i=0; i<26; ++i)
                st[clone].next[i] = st[q].next[i];
            for( ; p!=-1 && st[p].next[cti(c)]==q; p = st[p].link)
                st[p].next[cti(c)] = clone;
            st[q].link = st[curr].link = clone;
        }
    }
    last = curr;
}

void sa_cntstr()
{
    vector<pair<int, int> > vec(sz);
    for(int i=1; i<sz; ++i)
    {
        vec[i].first = st[i].len;
        vec[i].second = i;
    }
    sort(vec.begin()+1, vec.end());
    for(int i=sz-1, v; i>0; --i)
    {
        v = vec[i].second;
        st[st[v].link].cnt += st[v].cnt;
    }
}

void build_sa()
{
    sa_init();
    ss = S.size();
    for(int i=0; i<ss; ++i)
        sa_extend(S[i]);
    sa_cntstr();
}

vector<int> vb[MAXLEN+1];
vector<int> ve[MAXLEN+1];

void create_sol()
{
    int x, y;
    for(int i=1; i<sz; ++i)
    {
        x = st[st[i].link].len + 1;
        y = st[i].len;
        vb[st[i].cnt].push_back(x);
        ve[st[i].cnt].push_back(y+1);
    }
    for(int i=1; i<=ss; ++i)
    {
        sort(vb[i].begin(), vb[i].end());
        sort(ve[i].begin(), ve[i].end());
    }
}

int not_greater_than(vector<int> &vec, int val)
{
    int l = 0, r = vec.size()-1;
    int m;
    int ans=0;
    while(l<=r)
    {
        m = (l+r)/2;
        if(vec[m]<=val)
        {
            ans = m+1;
            l = m+1;
        }
        else
            r = m-1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>S;
    build_sa();
    create_sol();

    int N, L, P;
    cin>>N;
    while(N--)
    {
        cin>>L>>P;
        cout<<(not_greater_than(vb[P], L) - not_greater_than(ve[P], L))<<endl;
    }
    return 0;
}
