#include<iostream>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<vector>
using namespace std;

#define endl "\n"
typedef long long int lli;

struct node
{
    lli val;
    void init()
    {
        val = 0;
    }
    void identity()
    {
        val = 0;
    }
    void merge(node& l, node& r)
    {
        val = l.val + r.val;
    }
    void split(node& l, node& r)
    {
    }
};

node Tree[1000006];
char token[200005];
lli A[200005];
bool exist[200005];
unordered_map<lli, lli> MyMap;

node range_query(lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>=qs && se<=qe)
        return Tree[si];
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    node l, r;
    l.identity();
    r.identity();
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) l = range_query(lc, ss, sm, qs, qe);
    if(qe> sm) r = range_query(rc, sm+1, se, qs, qe);
    Tree[si].merge(Tree[lc], Tree[rc]);
    node res;
    res.merge(l, r);
    return res;
}

void update_single_node(node &n, lli val)
{
    n.val += val;
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, lli val)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], val);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli lc = 2*si;
    lli rc = lc+1;
    Tree[si].split(Tree[lc], Tree[rc]);
    if(qs<=sm) range_update(lc, ss, sm, qs, qe, val);
    if(qe> sm) range_update(rc, sm+1, se, qs, qe, val);
    Tree[si].merge(Tree[lc], Tree[rc]);
}

void update(lli si, lli ss, lli se, lli qi, lli val)
{
    range_update(si, ss, se, qi, qi, val);
}

void normalization(lli N)
{
    vector<lli> tmp(N);
    lli i, val;
    for(i=1; i<=N; ++i)
        tmp[i-1] = A[i];
    sort(tmp.begin(), tmp.end());
    for(i=1; i<=N; ++i)
    {
		if(token[i] != 'K')
        {
			val = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin() + 1;
			MyMap[val] = A[i];
			A[i] = val;
		}
    }
}

lli binarySearch(lli l, lli r, lli K, lli N)
{
    if(l>r)
        return -1;
    lli m = l+(r-l)/2;
    node cnt = range_query(1, 1, N, 1, m);
    if(cnt.val==K)
    {
        if(exist[m])
            return m;
        else
            return binarySearch(l, m-1, K, N);
    }
    if(cnt.val>K)
        return binarySearch(l, m-1, K, N);
    return binarySearch(m+1, r, K, N);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
    lli Q;
	cin>>Q;
    //scanf_s("%lld\n", &Q);
    lli i, N, z;
    for(i=1; i<=Q; ++i)
    {
		char ch;
		lli a;
		cin>>ch>>a;
        //scanf_s("%c %lld\n", &ch, &a);
		token[i] = ch;
		A[i] = a;
    }
    normalization(Q);
    N = Q;
    for(i=0; i<=Q; ++i)
        exist[i] = false;
    for(i=1; i<=Q; ++i)
    {
        switch(token[i])
        {
        case 'I':
            if(!exist[A[i]])
            {
                update(1, 1, N, A[i], 1);
                exist[A[i]] = true;
            }
            break;
        case 'D':
            if(exist[A[i]])
            {
                update(1, 1, N, A[i], -1);
                exist[A[i]] = false;
            }
            break;
        case 'C':
            if(A[i]==1)
                printf("0\n");//cout<<"0"<<endl; //
            else
            {
                node res;
                res = range_query(1, 1, N, 1, A[i]-1);
                printf("%lld\n", res.val); //cout<<res.val<<endl; //
            }
            break;
        case 'K':
            z = binarySearch(1, Q, A[i], N);
            if(z == -1)
                printf("invalid\n");  //cout<<"invalid"<<endl; //
            else
                printf("%lld\n", MyMap[z]); //cout<<MyMap[z]<<endl; //
            break;
        default:;
        }
    }
    return 0;
}
