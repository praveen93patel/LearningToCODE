#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

typedef long long int lli;

int Tree[30003];

class YODANESS
{
    int MAX_N;
    int countLvl;
    void init();
    void update(int idx, int val);
    int read(int idx);
public:
    lli yodanessLevel();
};

void YODANESS::init()
{
    for(int i=0; i<=MAX_N; ++i)
        Tree[i] = 0;
}

void YODANESS::update(int idx, int val)
{
    while(idx <= MAX_N)
    {
        Tree[idx] += val;
        idx += (idx & (-idx));
    }
}

int YODANESS::read(int idx)
{
    int ans = 0;
    while(idx>0)
    {
        ans += Tree[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

lli YODANESS::yodanessLevel()
{
    countLvl = 0;
    cin>>MAX_N;
    unordered_map<string, int> MyMap;
    string str;
    for(int i=1; i<=MAX_N; ++i)
    {
        cin>>str;
        MyMap[str] = i;
    }
    int idx;
    vector<int> A(MAX_N);
    for(int i=0; i< MAX_N; ++i)
    {
        cin>>str;
        idx = MyMap[str];
        A[i] = idx;
    }
    for(int i=MAX_N-1; i>=0; --i)
    {
        countLvl += read(A[i]-1);
        update(A[i], 1);
    }
    return countLvl;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        YODANESS yoda;
        lli ans = yoda.yodanessLevel();
        cout<<ans<<endl;
    }
    return 0;
}
