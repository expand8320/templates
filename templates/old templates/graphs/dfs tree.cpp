// https://www.luogu.com.cn/record/266439697
// done
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MN=2e5+13;
int N, M;
vector<int> G[MN];
int pre[MN], mn[MN], idx=0;
bool vis[MN];
set<int> ans;

void dfs(int u, int p)
{
    vis[u]=1;
    pre[u]=mn[u]=++idx;
    int cnt=0;
    for (int v:G[u]) if (v!=p)
    {
        if (!vis[v])
        {
            dfs(v, u);
            mn[u]=min(mn[u], mn[v]);
            if (p && mn[v]>=pre[u]) ans.insert(u);
            cnt++;
        }
        else mn[u]=min(mn[u], pre[v]);
    }
    if (!p && cnt>=2) ans.insert(u);
}

int main()
{
    cin>>N>>M;
    while (M--)
    {
        int U, V; cin>>U>>V;
        G[U].push_back(V);
        G[V].push_back(U);
    }
    for (int i=1; i<=N; i++) if (!vis[i]) dfs(i, 0);
    cout<<ans.size()<<endl;
    for (int i:ans) cout<<i<<' '; cout<<endl;
    return 0;
}