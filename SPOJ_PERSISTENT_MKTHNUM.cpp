#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

#define sz size()
#define pb push_back
#define rep(i,n) for(int i=0; i<n; ++i)
#define fd(i,a,b) for(int i=a; i>=b; --i)

#define N 100005

struct node
{
    int count;
    node *left, *right;

    node(int count, node *left, node *right) :
        count(count), left(left), right(right) {}

    node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);

node* node::insert(int l, int r, int w)
{
    if(l<=w && w<r)
    {
        if(l+1==r)
            return new node(this->count+1, null, null);
        int m = (l+r)>>1;
        return new node(this->count+1, this->left->insert(l, m, w), this->right->insert(m, r, w));
    }
    return this;
}

int query(node *a, node *b, int l, int r, int k)
{
    if(l+1==r)
        return l;
    int m = (l+r)>>1;
    int count = a->left->count-b->left->count;
    if(count>=k)
        return query(a->left, b->left, l, m, k);
    return query(a->right, b->right, m, r, k-count);
}

int A[N], M[N], RM[N];
node *root[N];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, n)
        scanf("%d", &A[i]);
    //normalization
    vector<int> temp(n);
    rep(i, n)
        temp[i] = A[i];
    sort(temp.begin(), temp.end());
    rep(i,n)
    {
        M[i] = lower_bound(temp.begin(), temp.end(), A[i]) - temp.begin() ;
        RM[M[i]] = A[i];
    }
    //cout<<"Test1"<<endl;
    int maxi = n+1;
    null->left = null->right = null;
    rep(i,n)
    {
        root[i] = (i==0 ? null : root[i-1])->insert(0, maxi, M[i]);
    }
    //cout<<"Test2"<<endl;
    while(m--)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        --u; --v;
        int ans = query(root[v], (u==0 ? null : root[u-1]), 0, maxi, k);
        ans = RM[ans];
        printf("%d\n", ans);
    }
    return 0;
}
