#include<iostream>
#include<vector>
using namespace std;
tpyedef long long int lli;
#define MOD 65536

struct node
{
    int low, mid, high;
} tree[5005];

class FloatingMedian
{
    void init();
    int MAX_K;
    int nextVal(int val, int mul, int add);
    void update(int idx, int val);
    int read(int idx);
public:
    long sumOfMedians(int seed, int mul, int add, int N, int K);
};

void FloatingMedian::init()
{
    for(int i=0; i<=MAX_K; ++i)
        tree[i].low = tree[i].mid = tree[i].high = -1;
}

long FloatingMedian::sumOfMedians(int seed, int mul, int add, int N, int K)
{
    int idx, val;
    MAX_K = K;
    val = seed;
    init();
    long ans = 0;
    for(idx=1; idx<=K; ++idx)
    {
        update(idx, val);
        val = nextVal(val, mul, add);
    }
    ans += read(K);
    for(;idx<=N;++idx)
    {
        update(idx, val);
        ans += read(K);
        val = nextVal(val, mul, add);
    }
    return ans;
}
int FloatingMedian::nextVal(int val, int mul, int add)
{
    long long tmp;
    tmp = (val*mul)%MOD;
    tmp = (tmp+add)%MOD;
    return (int)tmp;
}

void FloatingMedian::update(int idx, int val)
{
    while(idx <= MAX_K)
    {
        if(tree[idx].mid == -1)
            tree[idx].mid = val;
        else if(tree[idx].high == -1)
        {
            tree[idx].mid = min(tree[idx].mid, val);
            tree[idx].high = max(tree[idx].mid, val);
        }
        else if(tree[idx].low == -1)
        {
            if(val <= tree[idx].mid)
                tree[idx].low = val;
            else if(val < tree[idx].high)
            {
                tree[idx].low = tree[idx].mid;
                tree[idx].mid = val;
            }
            else
            {
                tree[idx].low = tree[idx].mid;
                tree[idx].mid = tree[idx].high;
                tree[idx].high = val;
            }
        }
        else
        {
            if(val > tree[idx].low && val <= tree[idx].mid)
            {
                tree[idx].high = tree[idx].mid;
                tree[idx].mid = val;
            }
            else if(val < tree[idx].high && val >= tree[idx].mid)
        }
        idx += (idx & (-idx));
    }
}

int FloatingMedian::read(int idx)
{

}
