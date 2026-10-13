// https://judge.yosupo.jp/submission/358630
// done
#include <iostream>
using namespace std;

const int MN=5e5+13, ML=22;
int N, Q, A[MN];

namespace st
{
    int st[MN][ML], lg[MN];
    void init()
    {
        for (int i=2; i<=N; i++) lg[i]=lg[i>>1]+1;
        for (int i=1; i<=N; i++) st[i][0]=A[i];
        for (int j=1; (1<<j)<=N; j++)
        {
            for (int i=1; i+(1<<j)-1<=N; i++)
            {
                st[i][j]=min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int qry(int L, int R)
    {
        int i=lg[R-L+1];
        return min(st[L][i], st[R-(1<<i)+1][i]);
    }
}

int main()
{
    cin>>N>>Q;
    for (int i=1; i<=N; i++) cin>>A[i];
    st::init();
    while (Q--)
    {
        int L, R; cin>>L>>R; L++;
        cout<<st::qry(L, R)<<endl;
    }
    return 0;
}