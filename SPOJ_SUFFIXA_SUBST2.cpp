#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 50005
char A[MAXN];
long long n;
long long RA[MAXN], tempRA[MAXN];
long long SA[MAXN], tempSA[MAXN];
long long c[MAXN];

void countingSort(long long k)
{
    long long i, sum, maxi=max((long long)300, n);
    memset(c, 0, sizeof(c));
    for(i=0;i<n;++i)
        c[i+k<n ? RA[i+k] : 0]++;
    for(i=sum=0; i<maxi;++i)
    {
        long long t=c[i];
        c[i] = sum;
        sum +=t;
    }
    for(i=0;i<n;++i)
    {
        tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
    }
    for(i=0;i<n;++i)
        SA[i] = tempSA[i];
}

void constructSA()
{
    long long i, k, r;
    for(i=0;i<n;++i) RA[i] = A[i];
    for(i=0;i<n;++i) SA[i] = i;

    for(k=1;k<n;k<<=1)
    {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for(i=1;i<n;++i)
        {
            tempRA[SA[i]] = (RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k]) ? r : ++r;
        }
        for(i=0;i<n;++i)
            RA[i] = tempRA[i];
        if(RA[SA[n-1]] == n-1) break;
    }
}

long long kasai()
{
    long long ans = 0;
    long long k=0;
    for(long long i=0;i<n; ++i)
        RA[SA[i]] = i;
    for(long long i=0;i<n;++i, k? --k : 0)
    {
        if(RA[i]==n-1)
        {
            k=0;
            continue;
        }
        long long j = SA[RA[i]+1];
        while(i+k<n && j+k<n && A[i+k]==A[j+k]) k++;
        ans+=k;
    }
    return ans;
}

void RunCode()
{
    //gets(A);
    cin>>A;
    n = strlen(A);
    A[n++] = '@';
    constructSA();
    /*cout<<"Suffix arr:: ";
    for(int i=0;i<n;++i)
        cout<<SA[i]<<" ";
    cout<<endl;*/
    long long ans= (n*(n-1))/2;
    ans -= kasai();
    cout<<ans<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
        RunCode();
    return 0;
}
