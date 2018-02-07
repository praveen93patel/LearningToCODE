#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

#define MAXLEN 250005
typedef long long ll;
char txt[MAXLEN];
char pat[MAXLEN];
int N, M, start, len;

struct state
{
    int len, link;
    int next[26];
};

state st[2*MAXLEN];
int sz, last;

void sa_init()
{
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
	 sz++;
    for(ll i=0; i<2*MAXLEN; ++i)
        for(ll j=0; j<26; ++j)
            st[i].next[j] = -1;
}

void sa_extend(int c)
{
    int curr = sz++;
    st[curr].len = st[last].len + 1;
    int p;
    for(p = last; p!=-1 && st[p].next[c]==-1; p = st[p].link)
        st[p].next[c] = curr;
    if(p==-1)
        st[curr].link = 0;
    else
    {
        int q = st[p].next[c];
        if(st[q].len == st[p].len + 1)
            st[curr].link = q;
        else
        {
            int clone = sz++;
            st[clone].len = st[p].len+1;
            st[clone].link = st[q].link;
            for(ll i=0; i<26; ++i) st[clone].next[i] = st[q].next[i];
            for( ; p!=-1 && st[p].next[c]==q ; p=st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[curr].link = clone;
        }
    }
    last = curr;
}

void sa_build()
{
    sa_init();
    for(ll i=0; i<N; ++i)
        sa_extend(txt[i]-'a');
}

void search_long()
{
    len = 0;
    int l, s;
    int v = 0;
    int w, c;
    for(int i=0; i<M; ++i)
    {
        c = pat[i]-'a';
        while(v && st[v].next[c]==-1)
        {
            v = st[v].link;
            l = st[v].len;
        }
        if(st[v].next[c]!=-1)
        {
            v = st[v].next[c];
            ++l;
        }
        if(l>len)
        {
            len = l;
            start = i-l+1;
        }
    }
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //cin>>txt;
    //cin>>pat;
    scanf("%s", txt);
    scanf("%s", pat);
    //N = txt.size();
    //M = pat.size();
    N = strlen(txt);
    M = strlen(pat);
    sa_build();
    search_long();
    if(len==0)
    {
        printf("0\n");
        //cout<<"0"<<endl;
        return 0;
    }
    //cout<< pat.substr(start, len) <<endl;
    //cout<<len<<endl;
    for(int i=start; i<start+len; ++i)
        printf("%c", pat[i]);
    printf("\n%d\n", len);
    return 0;
}
