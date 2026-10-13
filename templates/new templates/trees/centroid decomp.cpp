// https://codeforces.com/contest/342/submission/366319690
// upd 2026/3/12
#include <iostream>
#include <vector>
using namespace std;

const int MN=1e5+13, ML=22;
const int inf32=1e9;
int N, M;
vector<int> G[MN];
int ctp[MN], dp[MN];

namespace lca
{
    int st[MN<<1][ML], lg[MN<<1];
    int pre[MN], dep[MN], idx=0;
    int f(int u, int v) { return dep[u]<dep[v]?u:v; }
    void dfs(int u, int p)
    {
        pre[u]=++idx; st[idx][0]=u;
        for (int v:G[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
            st[++idx][0]=u;
        }
    }
    void init()
    {
        dep[1]=0; dfs(1, 0);
        for (int i=2; i<=idx; i++) lg[i]=lg[i>>1]+1;
        for (int j=1; (1<<j)<=idx; j++)
        {
            for (int i=1; i+(1<<j)-1<=idx; i++)
            {
                st[i][j]=f(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int dist(int u, int v)
    {
        int l=pre[u], r=pre[v];
        if (l>r) swap(l, r);
        int t=lg[r-l+1];
        return dep[u]+dep[v]-dep[f(st[l][t], st[r-(1<<t)+1][t])]*2;
    }
}
namespace cd
{
    int sz[MN];
    bool vis[MN];
    void dfs1(int u, int p)
    {
        sz[u]=1;
        for (int v:G[u]) if (v!=p && !vis[v])
        {
            dfs1(v, u);
            sz[u]+=sz[v];
        }
    }
    int dfs2(int u, int p, const int tot)
    {
        for (int v:G[u]) if (v!=p && !vis[v] && sz[v]>tot/2) return dfs2(v, u, tot);
        return u;
    }
    void init(int u, int p)
    {
        dfs1(u, 0);
        int cent=dfs2(u, 0, sz[u]);
        vis[cent]=1; ctp[cent]=p;
        for (int v:G[cent]) if (!vis[v]) init(v, cent);
    }
}
void upd(int u)
{
    int v=u;
    while (ctp[v])
    {
        v=ctp[v];
        dp[v]=min(dp[v], lca::dist(u, v));
    }
}

int main()
{
    cin>>N>>M;
    for (int i=1; i<N; i++)
    {
        int U, V; cin>>U>>V;
        G[U].push_back(V);
        G[V].push_back(U);
    }
    lca::init();
    cd::init(1, 0);
    for (int i=1; i<=N; i++) dp[i]=inf32;
    dp[1]=0; upd(1);
    while (M--)
    {
        int T, X; cin>>T>>X;
        if (T==1) { dp[X]=0; upd(X); }
        else
        {
            int ans=dp[X], u=X;
            while (ctp[u])
            {
                u=ctp[u];
                ans=min(ans, dp[u]+lca::dist(u, X));
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}