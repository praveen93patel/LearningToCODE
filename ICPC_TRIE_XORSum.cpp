#include<iostream>
#include<cmath>
#include<vector>

using namespace std;
typedef unsigned long long ll;

struct trieNode
{
    trieNode *child[2];
    ll LeafIndex;
    trieNode()
    {
        child[0] = child[1] = NULL;
    }
};

class XORSUM
{
    trieNode *root;
    ll max_;
    ll N, H;
    void insertTrie(ll Q);
    void queryTrie(ll Q);
public:
    XORSUM(int N)
    {
        this->N = N;
        H = 31;
        max_ = 0;
        root = new trieNode();
    }
    ll maxXOR(vector<ll> &A);
};

ll XORSUM::maxXOR(vector<ll> &A)
{
    ll Q = 0;
    insertTrie(Q);
    for(ll i=0; i<N; ++i)
    {
        Q = Q^A[i];
        queryTrie(Q);
        insertTrie(Q);
    }
    return max_;
}

void XORSUM::insertTrie(ll Q)
{
    ll nbit = 1<<(H-1);
    ll index;
    trieNode *curr = root;
    while(nbit>0)
    {
        index = 0;
        if(nbit&Q)
            index = 1;
        if(curr->child[index] == NULL)
            curr->child[index] = new trieNode();
        curr= curr->child[index];
        nbit >>= 1;
    }
}
void XORSUM::queryTrie(ll Q)
{
    ll nbit = 1<<(H-1);
    ll index, rindex, sum;
    trieNode *curr = root;
    sum = 0;
    while(nbit>0)
    {
        sum <<= 1;
        index = 0;
        if(nbit&Q)
            index = 1;
        rindex = 1-index;
        if(curr->child[rindex])
        {
            curr = curr->child[rindex];
            sum+=1;
        }
        else
            curr = curr->child[index];
        nbit >>= 1;
    }
    if(sum>max_)
        max_ = sum;
}

void RunCode()
{
    ll N;
    cin>>N;
    XORSUM xs(N);
    vector<ll> A(N);
    for(ll i=0; i<N; ++i)
        cin>>A[i];
    cout<<xs.maxXOR(A)<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
        RunCode();
    return 0;
}
