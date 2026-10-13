// https://www.luogu.com.cn/record/266429345
// upd 2026/3/10
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;

const int MN=1e5+13;
const ll inf64=1e18;
int N, M, S;
vector<pll> G[MN];
ll d[MN];
bool inq[MN];

void spfa()
{
    for (int i=1; i<=N; i++) d[i]=inf64;
    queue<int> q;
    d[S]=0;
    q.push(S);
    inq[S]=1;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        for (auto [v, w]:G[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
}

int main()
{
    cin>>N>>M>>S;
    while (M--)
    {
        int U, V; ll W; cin>>U>>V>>W;
        G[U].push_back({V, W});
    }
    spfa();
    for (int i=1; i<=N; i++)
    {
        if (d[i]==inf64) cout<<(1ll<<31)-1<<' ';
        else cout<<d[i]<<' ';
    } cout<<endl;
    return 0;
}