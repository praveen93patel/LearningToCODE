#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 250005
#define MOD 65536
struct node
{
	vector<int> A;
	node() {}
	void init(int val)
	{
		A.push_back(val);
	}
	void Merge(node &l, node &r);
};

node Tree[4*MAXN];
int Temp[MAXN];

void node::Merge(node &l, node &r)
{
	int N, M, i, j;
	N = l.A.size();
	M = r.A.size();
	i=j=0;
	while(i<N && j<M)
	{
		if(l.A[i]<r.A[j])
		{
			A.push_back(l.A[i]);
			++i;
		}
		else
		{
			A.push_back(r.A[j]);
			++j;
		}
	}
	while(i<N)
	{
		A.push_back(l.A[i]);
		++i;
	}
	while(j<M)
	{
		A.push_back(r.A[j]);
		++j;
	}
}

class FloatingMedian
{
	void buildTree(int si, int ss, int se);
	node query(int si, int ss, int se, int qs, int qe);
public:
	long long sumOfMedians(int seed, int mul, int add, int N, int K);
};

long long FloatingMedian::sumOfMedians(int seed, int mul, int add, int N, int K)
{
	Temp[0] = seed;
	for(int i=1; i<N; ++i)
		Temp[i] = ((Temp[i-1]*mul)%MOD + add) % MOD;

	buildTree(0, 0, N-1);

	long long ans = 0;
	for(int i=0, j=K; j<=N; ++i, ++j)
	{
		node res = query(0, 0, N-1, i, j-1);
		int M = res.A.size()-1;
		ans += res.A[M/2];
	}
	return ans;
}

void FloatingMedian::buildTree(int si , int ss, int se)
{
	if(ss>se)
		return;
	if(ss == se)
	{
		Tree[si].init(Temp[ss]);
		return;
	}
	int sm = ss+(se-ss)/2;
	int lc = 2*si+1;
	int rc = lc+1;
	buildTree(lc, ss, sm);
	buildTree(rc, sm+1, se);
	Tree[si].Merge(Tree[lc], Tree[rc]);
}

node FloatingMedian::query(int si, int ss, int se, int qs, int qe)
{
	if(ss>se || ss>qe || se<qs)
	{
        node a;
		return a;
	}
	if(ss>=qs && se<=qe)
		return Tree[si];
	int sm = ss+(se-ss)/2;
	int lc = 2*si+1;
	int rc = lc+1;
	node l = query(lc, ss, sm, qs, qe);
	node r = query(rc, sm+1, se, qs, qe);
	node res;
	res.Merge(l, r);
    return res;
}

int main()
{
    FloatingMedian fm;
    cout<<fm.sumOfMedians(3,1,1,10,3)<<endl;
    return 0;
}
