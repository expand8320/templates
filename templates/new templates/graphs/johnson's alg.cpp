// https://www.luogu.com.cn/record/266447266
// upd 2026/3/10
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;

const int MN=3013;
const int inf32=1e9;
const ll inf64=1e18;
int N, M;
vector<pll> G[MN];
ll rd[MN], d[MN];
bool inq[MN], vis[MN]; int cnt[MN];

bool spfa(int src)
{
    for (int i=1; i<=N; i++) rd[i]=inf64;
    queue<int> q;
    rd[src]=0;
    q.push(src); inq[src]=1;
    cnt[src]=0;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        for (auto [v, w]:G[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                cnt[v]=cnt[u]+1;
                if (cnt[v]>N) return 1;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return 0;
}
void dijk(int src)
{
    for (int i=1; i<=N; i++)
    {
        d[i]=inf64;
        vis[i]=0;
    }
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({0, src});
    d[src]=0;
    while (q.size())
    {
        auto [t, u]=q.top(); q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:G[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
            }
        }
    }
}

int main()
{
    cin>>N>>M;
    while (M--)
    {
        int U, V; ll W; cin>>U>>V>>W;
        G[U].push_back({V, W});
    }
    for (int i=1; i<=N; i++) G[N+1].push_back({i, 0});
    if (spfa(N+1))
    {
        cout<<-1<<endl;
        return 0;
    }
    for (int u=1; u<=N; u++)
    {
        for (auto &[v, w]:G[u])
        {
            w+=rd[u]-rd[v];
        }
    }
    for (int u=1; u<=N; u++)
    {
        dijk(u);
        ll ans=0;
        for (ll v=1; v<=N; v++)
        {
            if (d[v]==inf64) ans+=v*inf32;
            else ans+=v*(d[v]+rd[v]-rd[u]);
        }
        cout<<ans<<endl;
    }
    return 0;
}