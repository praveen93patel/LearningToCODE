#include<iostream>
#include<algorithm>
#include<cstdio>
#include<random>
using namespace std;

typedef long long ll;
const int N = 4e5+7;
ll h[N];

struct node
{
    node *left, *right;
    ll h0, h1;
    int sw;

    node(node *l, node *r, ll h0, ll h1, int sw) :
        left(l), right(r), h0(h0), h1(h1), sw(sw) {}
    node() {}
};

node *rt[N];
vector<int> ind;

node *push(node *t)
{
    if(!t->sw)
        return t;
    node *r1, *r2;
    if(t->left)
        r1 = new node(t->left->left, t->left->right, t->left->h1, t->left->h0, t->left->sw ^ 1);
    else
        r1 = t->left;
    if(t->right)
        r2 = new node(t->right->left, t->right->right, t->right->h1, t->right->h0, t->right->sw ^ 1);
    else
        r2 = t->right;
    return new node(r1, r2, t->h0, t->h1, 0);
}

node *upd(node *t, int l, int r, int tl, int tr)
{
    if(tl>=r || tr<=l)
        return t;
    if(l<=tl && r>=tr)
        return new node(t->left, t->right, t->h1, t->h0, t->sw ^ 1);
    int tm = (tl+tr)/2;
    node *x = push(t);          //lazy propagation
    auto a = upd(x->left, l, r, tl, tm);
    auto b = upd(x->right, l, r, tm, tr);
    return new node(a, b, a->h0 ^ b->h0, a->h1 ^ b->h1, x->sw);
}

bool sml(node *a, node *b, int tl, int tr)
{
    if(tr-tl==1)
        return (a->h0 && b->h1);
    int tm = (tl+tr)/2;
    a = push(a);
    b = push(b);
    if(a->left->h0 == b->left->h0)
        return sml(a->right, b->right, tm, tr);
    return sml(a->left, b->left, tl, tm);
}

node *build(int l, int r)
{
    if(r-l==1)
        return new node(0, 0, h[l], 0, 0);
    int m = (l+r)/2;
    auto a = build(l, m);
    auto b = build(m, r);
    return new node(a, b, a->h0 ^ b->h0, a->h1 ^ b->h1, 0);
}

void dfs(node *t, int l, int r)
{
    if(r-l==1)
    {
        ind.push_back(bool(t->h1));
        return;
    }
    int m = (l+r)/2;
    t = push(t);
    dfs(t->left, l, m);
    dfs(t->right, m, r);
}

class Main
{
public:
    void solve(istream &in, ostream &out)
    {
        mt19937 Rand(2281488);
        for(int i=0; i<N; ++i)
        {
            rt[i] = 0;
            h[i] = Rand();
            while(h[i]==0)
            {
                h[i] = Rand();
            }
        }
        ind.clear();
        int n, q;
        in>>n>>q;
        rt[0] = build(0, n);
        int curr = 0;
        for(int i=1; i<=q; ++i)
        {
            int l, r;
            in>>l>>r;
            l--; r--;
            rt[i] = upd(rt[i-1], l, r+1, 0, n);
            if(sml(rt[curr], rt[i], 0, n))
            {
                curr = i;
            }
        }
        dfs(rt[curr], 0, n);
        for(int c : ind)
        {
            out<<c;
        }
        out<<'\n';
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    Main solver;
    istream &in(cin);
    ostream &out(cout);
    solver.solve(in, out);
    return 0;
}
