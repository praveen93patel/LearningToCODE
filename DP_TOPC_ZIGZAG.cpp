#include<iostream>
#include<vector>
using namespace std;

class ZigZag
{
    int N;
public:
    int longestZigZag(vector<int> A);
};

int ZigZag::longestZigZag(vector<int> A)
{
    N = A.size();
    vector<vector<int> > Z(2, vector<int>(N, 1));
    for(int i=1; i<N; ++i)
    {
        for(int j=0; j<i; ++j)
        {
            if(A[i]>A[j])
                Z[0][i] = max(Z[0][i], Z[1][j]+1);
            else if(A[i]<A[j])
                Z[1][i] = max(Z[1][i], Z[0][j]+1);
        }
    }
    int ans = 0;
    for(int i=0; i<N; ++i)
        ans = max(ans, max(Z[0][i], Z[1][i]));
    return ans;
}

