#include<iostream>
#include<string>
#include<queue>

using namespace std;
typedef long long  int ll;

bool divisible(string num, int N)
{
    int div, rem, i;
    i=0;
    int M = num.size();
    div=rem=0;
    while(i<M)
    {
        while(div<N && i<M)
        {
            div = div*10 + (num[i]-'0');
            ++i;
        }
        div = div%N;
    }
    return (div==0);
}

void RunCode()
{
    int N;
    cin>>N;
    queue<string> Q;
    Q.push("1");
    bool FINISH = false;
    string onez;
    string ans;
    while(!Q.empty() && !FINISH)
    {
        onez = Q.front();
        Q.pop();
        if(divisible(onez, N))
        {
            ans = onez;
            FINISH = true;
        }
        else
        {
            Q.push(onez+"0");
            Q.push(onez+"1");
        }
    }
    cout<<ans<<endl;
}


int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        RunCode();
    }
    return 0;
}
