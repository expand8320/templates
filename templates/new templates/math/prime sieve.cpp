// https://codebreaker.xyz/submission/857174
// upd 2026/3/12
#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

const int MN=1e6+13;
int lp[MN];
vector<int> p;

void init()
{
    for (int i=2; i<MN; i++)
    {
        if (!lp[i])
        {
            lp[i]=i;
            p.push_back(i);
        }
        for (int j=0; i*p[j]<MN; j++)
        {
            lp[i*p[j]]=p[j];
            if (p[j]==lp[i]) break;
        }
    }
}

int main()
{
    init();
    int N; cin>>N;
    cout<<p[N-1]<<endl;
    return 0;
}