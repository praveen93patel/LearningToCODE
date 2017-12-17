#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<cstdio>

using namespace std;

typedef long long int lli;

class  MChaos
{
    lli N;
    lli *Tree;
    void update(lli idx, lli val);
    lli read(lli idx);
    lli RStringToNum(string str);
    void normalization(vector<lli> &A);
public:
    MChaos(lli n)
    {
        N = n;
        Tree = new lli[N+1];
        for(lli i=0; i<=N; ++i)
            Tree[i] = 0;
    }
    lli ChaosDegree(vector<string> &A);
};

void MChaos::update(lli idx, lli val)
{
    while(idx<=N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}
lli MChaos::read(lli idx)
{
    lli ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

lli MChaos::RStringToNum(string str)
{
    lli num = 0;
    lli base = 31;
    lli M = str.size();
    lli L = 10 - M;
    lli i, cn;
    for(i=M-1; i>=0; --i)
    {
        cn = str[i]-'a'+1;
        num = base*num + cn;
    }
    while(L--)
        num *= base;
    return num;
}
void MChaos::normalization(vector<lli> &A)
{
    lli n = A.size();
    vector<lli> tmp(n);
    for(lli i=0; i<n; ++i)
        tmp[i] = A[i];
    sort(tmp.begin(), tmp.end());
    for(lli i=0; i<n; ++i)
        A[i] = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin() + 1;
}

lli MChaos::ChaosDegree(vector<string> &A)
{
    N = A.size();
    sort(A.begin(), A.end());
    lli i, cn;
    lli ans = 0;
    vector<lli> B(N);
    for(i=N-1; i>=0; --i)
        B[i] = RStringToNum(A[i]);
    normalization(B);
    for(i=N-1; i>=0; --i)
    {
        ans += read(B[i]-1);
        update(B[i], 1);
    }
    return ans;
}

void RunCode()
{
    int n;
    scanf("%d", &n);
    MChaos chaos(n);
    vector<string> A;
    string tmp;
    for(lli i=0; i<n; ++i)
    {
        //cin>>tmp;
        char str[11];
        tmp.clear();
        scanf("%s", str);
        tmp = str;
//        if(tmp.size() == 0)
//            continue;
        A.push_back(tmp);
    }
    cout<<chaos.ChaosDegree(A)<<endl;
}

int main()
{
    lli T=1;
    //cin>>T;
    while(T--)
        RunCode();
    return 0;
}
