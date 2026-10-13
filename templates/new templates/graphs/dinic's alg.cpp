// https://www.luogu.com.cn/record/281932013
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
    int S, T, d[MN], cur[MN];
    struct edge { int v; ll w; int nxt; } E[MN]; int H[MN], I=1;
    void add(int u, int v, ll w)
    {
        E[++I]={v, w, H[u]}; H[u]=I;
        E[++I]={u, 0, H[v]}; H[v]=I;
    }
    bool bfs()
    {
        for (int i=1; i<=N; i++) d[i]=inf32;
        queue<int> q;
        d[S]=0; q.push(S);
        while (q.size())
        {
            int u=q.front(); q.pop();
            for (int i=H[u]; i; i=E[i].nxt)
            {
                auto [v, w, t]=E[i];
                if (w>0 && d[v]==inf32)
                {
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[T]!=inf32;
    }
    ll dfs(int u, ll lim)
    {
        if (u==T) return lim;
        for (int &i=cur[u]; i && lim; i=E[i].nxt)
        {
            auto [v, w, t]=E[i];
            if (w>0 && d[v]==d[u]+1)
            {
                ll k=dfs(v, min(lim, w));
                if (!k)
                {
                    d[v]=inf32;
                    continue;
                }
                E[i].w-=k; E[i^1].w+=k;
                return k;
            }
        }
        return 0;
    }
    ll dinic(int s, int t)
    {
        S=s; T=t;
        ll ans=0;
        while (bfs())
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
        int U, V; ll W; cin>>U>>V>>W;
        flow::add(U, V, W);
    }
    cout<<flow::dinic(S, T)<<endl;
    return 0;
}
