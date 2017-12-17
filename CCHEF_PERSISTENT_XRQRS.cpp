#include<cstdio>
using namespace std;

#define MAXN 1000006
#define MBIT 30
struct node
{
    int count;
    node *left, *right;
    node() : count(0), left(NULL), right(NULL) {}
} all[20000000];
int tot;

typedef node * pnode;

pnode root[MAXN];
pnode null = new node();

pnode update(pnode t, int x)
{
    pnode ret = &all[tot++];
    pnode tmp = ret;
    tmp->count = t->count+1;
    for(int i=MBIT; i>=0; --i)
    {
        if((1<<i)&x)
        {
            tmp->left = t->left;
            tmp->right = &all[tot++];
            t = t->right;
            tmp = tmp->right;
        }
        else
        {
            tmp->left = &all[tot++];
            tmp->right = t->right;
            t = t->left;
            tmp = tmp->left;
        }
        tmp->count = t->count + 1;
    }
    return ret;
}

int maximize(pnode r, pnode l, int x)
{
    int y = 0;
    int lc, rc;
    for(int i=MBIT; i>=0; --i)
    {
        lc = r->left->count - l->left->count;
        rc = r->right->count - l->right->count;

        //if(lc==0 && rc==0)
          //  break;

        if((1<<i)&x)
        {
            if(lc)
            {
                r = r->left;
                l = l->left;
                //y = y | (1<<i);
            }
            else
            {
                r = r->right;
                l = l->right;
                y = y | (1<<i);
            }
        }
        else
        {
            if(rc)
            {
                r = r->right;
                l = l->right;
                y = y | (1<<i);
            }
            else
            {
                r = r->left;
                l = l->left;
            }
        }
    }
    return y;
}

int getLessCount(pnode pn, int x)
{
    int count = 0;
    for(int i=MBIT; i>=0; --i)
    {
        if((1<<i)&x)
        {
            count += pn->left->count;
            pn = pn->right;
        }
        else
            pn = pn->left;
    }
    return count;
}

int getKth(pnode high, pnode low, int k)
{
    int count;
    int ans = 0;
    for(int i=MBIT; i>=0; --i)
    {
        count = high->left->count - low->left->count;
        if(count < k)
        {
            high = high->right;
            low = low->right;
            k -= count;
            ans = ans | (1<<i);
        }
        else
        {
            high = high->left;
            low = low->left;
        }
    }
    return ans;
}

int main()
{
    int M, i, j, t, x, y, L, R, k;
    scanf("%d", &M);
    root[0] = &all[tot++];
    //null->left = null->right = null;
    root[0]->left = root[0]->right = root[0];
    j = 1;
    for(i=1; i<=M; ++i)
    {
        scanf("%d", &t);
        switch(t)
        {
        case 0:
            scanf("%d", &x);
            root[j] = update(root[j-1], x);
            ++j;
            break;
        case 1:
            scanf("%d%d%d", &L, &R, &x);
            y = 0;
            y = maximize(root[R], root[L-1], x);
            //y = y^x;
            printf("%d\n", y);
            break;
        case 2:
            scanf("%d", &k);
            j -= k;
            break;
        case 3:
            scanf("%d%d%d", &L, &R, &x);
            y = getLessCount(root[R], x+1) - getLessCount(root[L-1], x+1);
            printf("%d\n", y);
            break;
        case 4:
            scanf("%d%d%d", &L, &R, &k);
            y = getKth(root[R], root[L-1], k);
            printf("%d\n", y);
            break;
        default:
            ;
        }
    }
    return 0;
}
