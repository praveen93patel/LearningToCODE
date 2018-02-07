#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

typedef int ll;

#define cti(x) (x)

struct state
{
    ll len, link, ds;
    //map<char, int> next;
    ll next[26];
};

const ll MAXLEN = 100005;
state st[2*MAXLEN];
ll sz, last;

char S[MAXLEN];
char ans[MAXLEN];

ll w;

void sa_init()
{
    sz = last = 0;
    st[sz].len = 0;
    st[sz].link = -1;
    ++sz;
    for(ll i=0; i<2*MAXLEN; ++i)
        for(ll j=0; j<26; ++j)
            st[i].next[j] = -1;
}

void sa_extend(char ch)
{
    int c = ch-'a';
    int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p;
	for (p=last; p!=-1 && st[p].next[c]==-1; p=st[p].link)
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].link = st[q].link;
			for(ll i=0; i<26; ++i) st[clone].next[i] = st[q].next[i];
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void CalcDiffSubstrings(ll v)
{
    vector<pair<ll, ll> > vec(sz);
    for(ll i=0; i<sz; ++i)
        vec[i] = make_pair(st[i].len, i);
    sort(vec.begin(), vec.end());
    for(ll i=sz-1; i>=0; --i)
    {
        v = vec[i].second;
        st[v].ds = 1;
        for(ll j=0; j<26; ++j)
            if(st[v].next[j]!=-1)
                st[v].ds += st[st[v].next[j]].ds;
    }
}

void KthSubstring(ll K)
{
    ll v, w;
    ll i, j, index;
    v=0;
    index = 0;
    while(K && v>=0)
    {
        for(i=0; i<26; ++i)
        {
            w = st[v].next[i];
            if(w==-1)
                continue;
            if(st[w].ds>=K)
            {
                ans[index++] = 'a'+i;
                --K;
                break;
            }
            K -= st[w].ds;
        }
        v = w;
    }
    ans[index] = '\0';
}

int main()
{
    fgets(S, MAXLEN, stdin);
    ll len = strlen(S) - 1;
    sa_init();
    for(ll i=0; i<len; ++i)
    {
        sa_extend(S[i]);
    }
    CalcDiffSubstrings(0);
    ll Q, K;
    scanf("%d", &Q);
    while(Q--)
    {
        scanf("%d", &K);

        KthSubstring(K);
        printf("%s\n", ans);
    }
    return 0;
}
