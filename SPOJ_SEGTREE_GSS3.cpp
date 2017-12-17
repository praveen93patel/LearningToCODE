#include<iostream>
#include<cstdio>

using namespace std;

#define INF 202020
typedef long long int lli;

struct node
{
     lli presum;
     lli postsum;
     lli sum;
     lli maxsum;
     void init(lli val)
     {
         presum = postsum = sum = maxsum = val;
     }
     void infinity()
     {
         presum = postsum = sum = maxsum = -INF;
     }
     void mergeChildren(node l, node r)
     {
         presum = max(l.presum, l.sum + r.presum);
         postsum = max(r.postsum, r.sum + l.postsum);
         sum = l.sum + r.sum;
         maxsum = max(l.postsum+r.presum, max(l.maxsum, r.maxsum));
     }
     lli getMax()
     {
         return maxsum;
     }
};

node Tree[200005];
lli A[50005];

void buildTree(lli si, lli ss, lli se)
{
    if(ss>se)
    {
        Tree[si].infinity();
        return ;
    }
    if(ss == se)
    {
        Tree[si].init(A[ss]);
        return ;
    }
    lli sm = ss + (se-ss)/2;
    buildTree(2*si, ss, sm);
    buildTree(2*si+1, sm+1, se);
    Tree[si].mergeChildren(Tree[2*si], Tree[2*si+1]);
}

node query(lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>se || ss>qe || se<qs)
    {
        node a;
        a.infinity();
        return a;
    }
    if(ss>=qs && se<=qe)
    {
        return Tree[si];
    }
    lli sm = ss + (se-ss)/2;
    node l = query(2*si, ss, sm, qs, qe);
    node r = query(2*si+1, sm+1, se, qs, qe);
    node res;
    res.mergeChildren(l, r);
    return res;
}

node modify(lli si, lli ss, lli se, lli qi, lli newVal)
{
    if(ss>se)
    {
        node a;
        a.infinity();
        return a;
    }
    if(ss>qi || se<qi)
    {
        return Tree[si];
    }
    if(ss==se && qi==ss)
    {
        A[qi] = newVal;
        Tree[si].init(newVal);
        return Tree[si];
    }
    lli sm = ss + (se-ss)/2;
    node l = modify(2*si, ss, sm, qi, newVal);
    node r = modify(2*si+1, sm+1, se, qi, newVal);
    Tree[si].mergeChildren(l, r);
    return Tree[si];
}

int main()
{
    lli N, Q, x, y, ch, i;
    scanf("%lld", &N);
    for(i=1; i<=N; ++i)
        scanf("%lld", &A[i]);
    buildTree(1, 1, N);
    scanf("%lld", &Q);
    while(Q--)
    {
        scanf("%lld %lld %lld", &ch, &x, &y);
        if(ch==0)
        {
            modify(1, 1, N, x, y);
        }
        else
        {
            node res;
            res = query(1, 1, N, x, y);
            printf("%lld\n", res.getMax());
        }
    }
    return 0;
}
