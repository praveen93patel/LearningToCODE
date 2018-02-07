#include<iostream>
#include<vector>

using namespace std;

class BadNeighbors
{
public:
    int maxDonations(vector<int> A);
};

int BadNeighbors::maxDonations(vector<int> A)
{
    int N = A.size();
    vector<vector<int> > D(2, vector<int>(N));
    D[0][0] = A[0];
    D[1][0] = 0;
    for(int i=1; i<N; ++i)
    {
        D[0][i] = D[1][i] = 0;
        for(int j=0; j<i-1; ++j)
        {
            D[0][i] = max(D[0][i], D[0][j]+A[i]);
            D[1][i] = max(D[1][i], D[1][j]+A[i]);
        }
    }
    return max(D[0][N-2], D[1][N-1]);
}
