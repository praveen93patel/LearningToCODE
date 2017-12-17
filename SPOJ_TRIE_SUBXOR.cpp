#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
typedef long long ll;

struct trieNode
{
    ll cnt[2];
    trieNode *child[2];
    trieNode()
    {
        cnt[0] = cnt[1] = 0;
        child[0] = child[1] = NULL;
    }
};

class SUBXOR
{
    trieNode *root;
    ll N, K, H;
    ll count;
    void queryTrie(ll Q);
    void insertTrie(ll Q);
public:
    SUBXOR(ll N, ll K)
    {
        count = 0;
        this->N = N;
        this->K = K;
        this->H = 20;
        root = new trieNode();
    }
    ll CountSubarrays(vector<ll> &A);
};

ll SUBXOR::CountSubarrays(vector<ll> &A)
{
    //cout<<"test: "<<N<<" "<<H<<" "<<K<<endl;
    ll Q = 0;
    for(ll i=0; i<N; ++i)
    {
        insertTrie(Q);
        Q = Q^A[i];
        queryTrie(Q);
    }
    return count;
}

void SUBXOR::insertTrie(ll Q)
{
    ll nbit = 1<<(H-1);
    //cout<<"test1: nbit :"<<Q<< " "<<nbit<<endl;
    trieNode *curr = root;
    ll index;
    while(nbit>0)
    {
        index = 0;
        if(nbit&Q)
            index = 1;
        if(curr->child[index] == NULL)
            curr->child[index] = new trieNode();
        curr->cnt[index]++;
        curr = curr->child[index];
        nbit = nbit>>1;
        //cout<<"test1: nbit :"<<nbit<<endl;
    }
}

void SUBXOR::queryTrie(ll Q)
{
    ll nbit = 1<<(H-1);
    trieNode *curr = root;
    //cout<<"test2: nbit :"<<Q<< " "<< nbit<<endl;
    while(nbit>0)
    {
        if(nbit&K)
        {
            if(nbit&Q)
            {
                count += curr->cnt[1];
                curr = curr->child[0];
            }
            else
            {
                count += curr->cnt[0];
                curr = curr->child[1];
            }
        }
        else
        {
            if(nbit&Q)
                curr = curr->child[1];
            else
                curr = curr->child[0];
        }
        if(curr == NULL)
            return ;
        nbit = nbit>>1;
        //cout<<"test2: nbit :"<<nbit<<endl;
    }
}

void RunCode()
{
    ll N, K;
    cin>>N>>K;
    vector<ll> A(N);
    ll mx = 0;
    for(ll i=0; i<N; ++i)
        cin>>A[i];
    //cout<<"test: "<<mx<<endl;
    SUBXOR sxor(N, K);
    cout<<sxor.CountSubarrays(A)<<endl;
}

int main()
{
    ll T;
    cin>>T;
    while(T--)
    {
        RunCode();
    }
    return 0;
}
