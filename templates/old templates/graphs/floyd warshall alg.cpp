// https://www.luogu.com.cn/record/266440445
// done
#include <iostream>
using namespace std;
using ll=long long;

const int MN=513;
const ll inf64=1e18;
int N, M;
ll d[MN][MN];

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=N; j++) d[i][j]=inf64;
        d[i][i]=0;
    }
    while (M--)
    {
        int U, V; ll W; cin>>U>>V>>W;
        d[U][V]=min(d[U][V], W);
        d[V][U]=min(d[V][U], W);
    }
    for (int i=1; i<=N; i++)
    {
        for (int u=1; u<=N; u++)
        {
            for (int v=1; v<=N; v++)
            {
                d[u][v]=min(d[u][v], d[u][i]+d[i][v]);
            }
        }
    }
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=N; j++) cout<<d[i][j]<<' ';
        cout<<endl;
    }
}