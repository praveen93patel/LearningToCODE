#include<iostream>
#include<cstdio>

using namespace std;
typedef int lli;

struct node
{
    lli openBr, closeBr;
    void init(char val)
    {
        if(val=='(')
        {
            openBr = 1;
            closeBr = 0;
        }
        else
        {
            openBr = 0;
            closeBr = 1;
        }
    }
    void identity()
    {
        openBr = closeBr = 0;
    }
    void mergeChildren(node l, node r)
    {
        lli p = min(l.openBr, r.closeBr);
        openBr = l.openBr+r.openBr-p;
        closeBr = l.closeBr+r.closeBr-p;
    }
    bool valid()
    {
        if(openBr==0 && closeBr==0)
            return true;
        return false;
    }
};

node Tree[100005];
char A[30003];

void buildTree(lli si, lli ss, lli se)
{
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

node modify(lli si, lli ss, lli se, lli qi, char val)
{
    if(ss>se)
    {
        node a;
        a.identity();
        return a;
    }
    if(ss>qi || se<qi)
    {
        return Tree[si];
    }
    if(ss==qi && se==qi)
    {
        Tree[si].init(val);
        return Tree[si];
    }
    lli sm = ss + (se-ss)/2;
    node l = modify(2*si, ss, sm, qi, val);
    node r = modify(2*si+1, sm+1, se, qi, val);
    Tree[si].mergeChildren(l, r);
    return Tree[si];
}

int main()
{
    lli T, N, Q, k;
    T = 10;
    for(lli i=1; i<=T; ++i)
    {
        printf("Test %d:\n", i);
        scanf("%d\n", &N);
        scanf("%[^\n]%*c", A+1);
        if(N%2 != 0)
        {
            scanf("%d", &Q);
            while(Q--)
            {
                scanf("%d", &k);
                if(k==0)
                    printf("NO\n");
            }
        }
        else
        {
            buildTree(1,1,N);
            scanf("%d", &Q);
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
                    if(A[k] == '(')
                        A[k] = ')';
                    else
                        A[k] = '(';
                    modify(1, 1, N, k, A[k]);
                }
            }
        }
    }
    return 0;
}
