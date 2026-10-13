// https://www.luogu.com.cn/record/281934174
// upd 2026/06/14
#include <iostream>
#include <queue>
using namespace std;
using ll=long long;

const int MN=1e5+13;
const int inf32=1e9;
const ll inf64=1e18;
int N, M;

namespace flow
{
    int S, T, cur[MN];
    ll cost, d[MN];
    bool inq[MN], vis[MN];
    struct edge { int v; ll w, c; int nxt; } E[MN]; int H[MN], I=1;
    void add(int u, int v, ll w, ll c)
    {
        E[++I]={v, w, c, H[u]}; H[u]=I;
        E[++I]={u, 0, -c, H[v]}; H[v]=I;
    }
    bool spfa()
    {
        for (int i=1; i<=N; i++)
        {
            d[i]=inf64;
            inq[i]=0;
        }
        queue<int> q;
        d[S]=0; q.push(S);
        inq[S]=1;
        while (q.size())
        {
            int u=q.front(); q.pop();
            inq[u]=0;
            for (int i=H[u]; i; i=E[i].nxt)
            {
                auto [v, w, c, t]=E[i];
                if (w>0 && d[v]>d[u]+c)
                {
                    d[v]=d[u]+c;
                    if (!inq[v])
                    {
                        q.push(v);
                        inq[v]=1;
                    }
                }
            }
        }
        return d[T]!=inf64;
    }
    ll dfs(int u, ll lim)
    {
        if (u==T) return lim;
        vis[u]=1;
        for (int &i=cur[u]; i && lim; i=E[i].nxt)
        {
            auto [v, w, c, t]=E[i];
            if (!vis[v] && w>0 && d[v]==d[u]+c)
            {
                ll k=dfs(v, min(lim, w));
                if (!k) continue;
                E[i].w-=k; E[i^1].w+=k;
                cost+=k*c;
                vis[u]=0;
                return k;
            }
        }
        vis[u]=0;
        return 0;
    }
    ll dinic(int s, int t)
    {
        S=s; T=t;
        ll ans=0;
        while (spfa())
        {
            for (int i=1; i<=N; i++) cur[i]=H[i];
            while (ll z=dfs(S, inf64)) ans+=z;
        }
        return ans;
    }
}

int main()
{
    int S, T; cin>>N>>M>>S>>T;
    while (M--)
    {
        int U, V; ll W, C; cin>>U>>V>>W>>C;
        flow::add(U, V, W, C);
    }
    cout<<flow::dinic(S, T)<<' '<<flow::cost<<endl;
    return 0;
}
