// https://www.luogu.com.cn/record/266437919
// upd 2026/3/10
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;

const int MN=2e5+13;
const ll inf64=1e18;
int N, M, K;
vector<pll> G[MN], rg[MN];
ll rd[MN], ans[MN]; int cnt=0;
bool vis[MN];

void dijk()
{
    for (int i=1; i<=N; i++) rd[i]=inf64;
    priority_queue<pll, vector<pll>, greater<pll>> q;
    rd[1]=0;
    q.push({0, 1});
    while (q.size())
    {
        auto [t, u]=q.top(); q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:rg[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                q.push({rd[v], v});
            }
        }
    }
}
void astar()
{
    priority_queue<pll, vector<pll>, greater<pll>> q;
    q.push({rd[N], N});
    while (q.size())
    {
        auto [d, u]=q.top(); q.pop();
        if (u==1)
        {
            ans[++cnt]=d;
            if (cnt==K) return;
            continue;
        }
        d-=rd[u];
        for (auto [v, w]:G[u]) q.push({d+w+rd[v], v});
    }
}

int main()
{
    cin>>N>>M>>K;
    while (M--)
    {
        int U, V; ll W; cin>>U>>V>>W;
        G[U].push_back({V, W});
        rg[V].push_back({U, W});
    }
    dijk();
    astar();
    for (int i=1; i<=K; i++)
    {
        if (i<=cnt) cout<<ans[i]<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}