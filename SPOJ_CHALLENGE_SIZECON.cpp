#include<iostream>
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T, N, sum = 0;
    cin>>T;
    while(T--)
    {
        cin>>N;
        if(N>0)
            sum += N;
    }
    cout<<sum<<"\n";
    return 0;
}
