// https://www.luogu.com.cn/record/266426235
// upd 2026/3/10
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
using ll=long long;

const int MN=2e5+13;
int N, M;
vector<int> G[MN];
ll A[MN], val[MN];
ll dp[MN];
bool vis[MN];

namespace cg
{
    int scc[MN];
    vector<int> rg[MN];
    stack<int> st;
    void dfs1(int u)
    {
        vis[u]=1;
        for (int v:G[u]) if (!vis[v]) dfs1(v);
        st.push(u);
    }
    void dfs2(int u, const int r)
    {
        vis[u]=1; scc[u]=r;
        val[r]+=A[u];
        for (int v:rg[u]) if (!vis[v]) dfs2(v, r);
    }
    void init()
    {
        for (int u=1; u<=N; u++) for (int v:G[u]) rg[v].push_back(u);
        for (int i=1; i<=N; i++) if (!vis[i]) dfs1(i);
        for (int i=1; i<=N; i++) vis[i]=0;
        while (st.size())
        {
            int u=st.top(); st.pop();
            if (!vis[u]) dfs2(u, u);
        }
        for (int i=1; i<=N; i++) G[i].clear();
        for (int v=1; v<=N; v++)
        {
            for (int u:rg[v])
            {
                if (scc[u]!=scc[v])
                {
                    G[scc[u]].push_back(scc[v]);
                }
            }
        }
    }
}

void dfs3(int u)
{
    vis[u]=1;
    for (int v:G[u])
    {
        if (!vis[v]) dfs3(v);
        dp[u]=max(dp[u], dp[v]);
    }
    dp[u]+=val[u];
}

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++) cin>>A[i];
    while (M--)
    {
        int U, V; cin>>U>>V;
        G[U].push_back(V);
    }
    cg::init();
    for (int i=1; i<=N; i++) vis[i]=0;
    ll ans=0;
    for (int i=1; i<=N; i++)
    {
        if (!vis[i]) dfs3(i);
        ans=max(ans, dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}