#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

#define sz size()
#define pb push_back
#define rep0(i, n) for(int i=0; i<n; ++i)
#define rep(i, n) for(int i=1; i<=n; ++i)
#define fd(i, a, b) for(int i=a; i>=b; --i)

#define N 300004

struct node
{
    int count;
    node *left, *right;
    node(int count, node *left, node *right) :
        count(count), left(left), right(right) {}
    node *insert(int l, int r, int w);
};

node* null = new node(0, NULL, NULL);

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

node* root[N];

int query(node *a, node *b, int l, int r, int k)
{
    if(l<=k && k<r && l+1<r)
    {
        int m =(l+r)>>1;
        if(m>k)
            return query(a->left, b->left, l, m, k) + (a->right->count - b->right->count);
        return query(a->right, b->right, m, r, k);
    }
    return 0;
}

int A[N];

int main()
{
    int n, m;
    scanf("%d", &n);
    rep(i, n)
        scanf("%d", &A[i]);
    vector<int> temp(n);
    rep(i, n)
        temp[i-1] = A[i];
    sort(temp.begin(), temp.end());
    null->left = null->right = null;
    root[0] = null;
    int maxi=n+1;
    rep(i, n)
    {
        A[i] = lower_bound(temp.begin(), temp.end(), A[i]) - temp.begin() + 1 ;
        root[i] = root[i-1]->insert(0, maxi, A[i]);
        //printf("A==%d\n", A[i]);
    }
    scanf("%d", &m);
    int last_ans=0;
    while(m--)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        //printf("%d\t%d\t%d\n", u, v, k);
        u = u^last_ans;
        v = v^last_ans;
        k = k^last_ans;
        //printf("%d\t%d\t%d\n", u, v, k);
        if(u<1)
            u=1;
        if(v>n)
            v=n;
        int ans;
        if(u>v)
            ans = 0;
        else
        {
            //printf("Test1:%d\t%d\t%d\n", u, v, k);
            k = upper_bound(temp.begin(), temp.end(), k) - temp.begin();
            //printf("Test2:%d %d %d\n", u, v, k);
            ans = query(root[v], root[u-1], 0, maxi, k);
            //printf("ans==%d\n", ans);
            //printf("== %d - %d\n", query(root[v], null, 0, maxi, k), query(root[u-1], null, 0, maxi, k));
        }
        //printf("%d\t%d\t%d\n", u, v, k);
        printf("%d\n", ans);
        last_ans = ans;
    }
    return 0;
}
