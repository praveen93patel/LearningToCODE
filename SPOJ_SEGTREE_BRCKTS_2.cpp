#include<iostream>
#include<cstdio>

using namespace std;
typedef int lli;

struct node
{
    lli openBr, closeBr;
    void init(char val)
    {
        openBr = closeBr = 0;
        (val == '(') ? openBr = 1 : closeBr = 1;
    }
    void identity()
    {
        openBr = closeBr = 0;
    }
    void mergeC(node &l, node &r)
    {
        lli p = min(l.openBr, r.closeBr);
        openBr = l.openBr+r.openBr-p;
        closeBr = l.closeBr+r.closeBr-p;
    }
    void splitC(node &l, node &r)
    {
    }
    bool valid()
    {
        return (openBr==0 && closeBr==0);
    }
};

node Tree[100005];
char A[30004];

void buildTree(lli si, lli ss, lli se)
{
    if(ss == se)
    {
        Tree[si].init(A[ss]);
        return;
    }
    lli sm = ss+(se-ss)/2;
    lli leftC = 2*si;
    lli rightC = leftC+1;
    buildTree(leftC, ss, sm);
    buildTree(rightC, sm+1, se);
    Tree[si].mergeC(Tree[leftC], Tree[rightC]);
}

node range_query(lli si, lli ss, lli se, lli qs, lli qe)
{
    if(ss>=qs && se<=qe)
    {
        return Tree[si];
    }
    lli sm = ss + (se-ss)/2;
    lli leftC = 2*si;
    lli rightC = leftC+1;
    Tree[si].splitC(Tree[leftC], Tree[rightC]);
    node l, r;
    l.identity();
    r.identity();
    if(qs<=sm) l = range_query(leftC, ss, sm, qs, qe);
    if(qe>sm) r = range_query(rightC, sm+1, se, qs, qe);
    Tree[si].mergeC(Tree[leftC], Tree[rightC]);
    node res;
    res.mergeC(l, r);
    return res;
}

void update_single_node(node &n, char new_val)
{
    n.init(new_val);
}

void range_update(lli si, lli ss, lli se, lli qs, lli qe, char new_val)
{
    if(ss>=qs && se<=qe)
    {
        update_single_node(Tree[si], new_val);
        return ;
    }
    lli sm = ss+(se-ss)/2;
    lli leftC = 2*si;
    lli rightC = leftC+1;
    Tree[si].splitC(Tree[leftC], Tree[rightC]);
    if(qs<=sm) range_update(leftC, ss, sm, qs, qe, new_val);
    if(qe>sm) range_update(rightC, sm+1, se, qs, qe, new_val);
    Tree[si].mergeC(Tree[leftC], Tree[rightC]);
}

void update(lli si, lli ss, lli se, lli qi, char val)
{
    range_update(si, ss, se, qi, qi, val);
}

int main()
{
    lli T, N, Q, k, i;
    T = 10;
    for(i=1; i<=T; ++i)
    {
        printf("Test %d:\n", i);
        scanf("%d\n", &N);
        scanf("%[^\n]%*c", A+1);
        scanf("%d\n", &Q);
        if(N%2 != 0)
        {
            while(Q--)
            {
                scanf("%d", &k);
                if(k==0)
                    printf("NO\n");
            }
        }
        else
        {
            buildTree(1, 1, N);
            while(Q--)
            {
                scanf("%d", &k);
                if(k==0)
                {
                    if(Tree[1].valid())
                        printf("YES\n");
                    else
                        printf("NO\n");
                }
                else
                {
                    (A[k]=='(') ? (A[k]=')') : (A[k]='(');
                    char val = A[k];
                    update(1, 1, N, k, val);
                }
            }
        }
    }
    return 0;
}
