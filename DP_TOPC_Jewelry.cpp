#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Jewelry
{
    int N, M;
    long long Comb(long long n, long long r);
public:
    long howMany(vector<int> values);
};

long long Jewelry::Comb(long long n, long long r)
{
    if(n-r< r)
        r = n-r;
    long long ans = 1;
    for(int i = 1; i<=r; ++i)
    {
        ans = ans*(n-i+1)/i;
    }
    return ans;
}

long Jewelry::howMany(vector<int> values)
{
    N = values.size();
    sort(values.begin(), values.end());
    M = 0;
    int i, j;
    for(i=0; i<N-1; ++i)
        M+=values[i];

    vector<int> count1(1001, 0);
    vector<int> count2(N, 1);
    for(i=0; i<N; ++i)
    {
        count1[values[i]]++;
        if(i>0)
            count2[i] += (values[i]==values[i-1]) ? count2[i-1] : 0;
    }

    vector<vector<long long > > A(M+1, vector<long long>(N+2, 0));
    vector<vector<long long > > B(M+1, vector<long long>(N+2, 0));
    for(j=0; j<N+2; ++j)
    {
        A[0][j] = B[0][j] = 1;
    }
    //generate A from left to right
    for(i=1; i<=M; ++i)
    {
        for(j=1; j<N; ++j)
        {
            A[i][j] = A[i][j-1];
            if(values[j-1]<=i)
                A[i][j] += A[i-values[j-1]][j-1];
        }
    }
    /*cout<<endl;
    cout<<"A' ="<<endl;
    for(i=1; i<=M; ++i)
    {
        cout<<i<<" -> ";
        for(j=1; j<=N; ++j)
            cout<<A[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;/*/
    //transform A from right to left
    for(j=N-1; j>=1; --j)
    {
        for(i=1; i<=M; ++i)
        {
            A[i][j] = 0;
            if(values[j-1]<=i)
                A[i][j] = A[i-values[j-1]][j-1];
        }
    }
    /*
    cout<<endl;
    cout<<"A ="<<endl;
    for(i=1; i<=M; ++i)
    {
        cout<<i<<" -> ";
        for(j=1; j<=N; ++j)
            cout<<A[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;*/
    //generate B from right to left
    for(i=1; i<=M; ++i)
    {
        for(j=N; j>1; --j)
        {
            B[i][j] = B[i][j+1];
            if(values[j-1]<=i)
                B[i][j] += B[i-values[j-1]][j+1];
        }
    }

    //transform B from left to right
    for(j=2; j<=N; ++j)
    {
        for(i=1; i<=M; ++i)
        {
            B[i][j] = 0;
            if(values[j-1]<=i)
                B[i][j] = B[i-values[j-1]][j+1];
        }
    }
    /*
    cout<<endl;
    cout<<"B = "<<endl;
    for(i=1; i<=M; ++i)
    {
        cout<<i<<" -> ";
        for(j=1; j<=N; ++j)
            cout<<B[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;*/
    //cummulative sum
    /*for(i=1; i<=M; ++i)
    {
        for(j=2; j<N; ++j)
            A[i][j] += A[i][j-1];
        /*for(j=N-1; j>1; --j)
            B[i][j] += B[i][j+1];
    }*/

    //calculate no. of ways
    long long ans = 0;
    int k, tmp, c;
    for(i=1; i<=M; ++i)
    {
        for(j=1; j<N; ++j)
        {
            for(k=j+1; k<=N; ++k)
            {
                c = 1;
                if(values[k-1]==values[j-1])
                    c = Comb(count2[j-1]+count1[values[j-1]]-count2[k-1]+1, count2[j-1]);
                ans += c*A[i][j]*B[i][k];
            }
        }
    }
    return ans;
}

int main()
{
    vector<int> X;
    X.push_back(1);
    X.push_back(2);
    X.push_back(5);
    X.push_back(3);
    X.push_back(4);
    X.push_back(5);
    Jewelry jw;
    cout<<jw.howMany(X);
    return 0;
}
