#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

typedef long long ll;

ll N;

ll shiftKMP(string &A, string &B)
{
    ll i, j, max_ind, len, max_len;
    max_ind = 0;
    len = max_len = 0;
    ll lps[N+1];
    lps[0]=0;
    i=1;
    while(i<=N)
    {
        if(B[i-1] == A[len])
        {
            ++len;
            lps[i] = len;
            if(len>max_len)
            {
                max_len = len;
                max_ind = i;
            }
            ++i;
        }
        else
        {
            if(len > 0)
                len = lps[len-1];
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }
    return (max_ind - max_len);
}

void RunCode()
{
    cin>>N;
    string A, B;
    cin>>A;
    cin>>B;
    cout<<shiftKMP(A, B)<<endl;
}

int main()
{
    RunCode();
    return 0;
}
