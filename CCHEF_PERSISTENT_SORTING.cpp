#include<cstdio>
using namespace std;

#define MAXN 1000006

struct node
{
    int L, R, sum;
    node *hL, *hR;
    node() {}
    node(int L, int R) : L(L), R(R), sum(0) {}
} all[20000000];
int tot;

typedef node * pnode;

pnode root[MAXN];
int A[MAXN], pos[MAXN], n, i;
long long ans;

pnode create(int L, int R)
{
    pnode ret = &all[tot++];
    ret->L = L, ret->R = R;
    ret->hL = ret->hR = NULL;
    if(L<R)
    {
        ret->hL = create(L, (L+R)/2);
        ret->hR = create((L+R)/2+1, R);
    }
    return ret;
}

pnode change(pnode t, int j)
{
    pnode ret = &all[tot++];
    ret->L = t->L, ret->R = t->R;
    ret->hL = t->hL, ret->hR = t->hR;
    ret->sum = t->sum + 1;
    if(t->L<t->R)
    {
        if(t->hL->R >= j)
            ret->hL = change(t->hL, j);
        else
            ret->hR = change(t->hR, j);
    }
    return ret;
}

int getKth(pnode low, pnode high, int key)
{
    if(low->L==low->R)
        return low->L;
    int val = high->hL->sum - low->hL->sum;
    if(val>=key)
        return getKth(low->hL, high->hL, key);
    else
        return getKth(low->hR, high->hR, key-val);
}

int qL[2000006], qR[2000006], q1, q2;

void solve(int L, int R)
{
    qL[q1] = L, qR[q1] = R;
    ++q1;
    q2 = 0;
    while(q1!=q2)
    {
        L = qL[q2], R = qR[q2];
        if(R-L+1>=2)
        {
            int pivot = A[getKth(root[L-1], root[R], (R-L+2)/2)];
            ans += (R-L+1);
            qL[q1] = L, qR[q1] = pivot-1;
            ++q1;
            qL[q1] = pivot+1, qR[q1] = R;
            ++q1;
        }
        ++q2;
    }
}

int main()
{
    scanf("%d", &n);
    for(i=1;i<=n;++i)
    {
        scanf("%d", &A[i]);
        pos[A[i]] = i;
    }
    root[0] = create(1, n);
    for(i=1;i<=n; ++i)
        root[i] = change(root[i-1], pos[i]);
    solve(1, n);
    printf("%lld\n", ans);
    return 0;
}
