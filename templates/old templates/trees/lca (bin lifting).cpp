// https://judge.yosupo.jp/submission/338407
// done
#include <iostream>
#include <vector>
using namespace std;

const int MN=5e5+13, ML=22;
int N, Q;
vector<int> G[MN];

namespace lca
{
    int pre[MN], post[MN], idx;
    int anc[MN][ML], dep[MN];
    void dfs(int u, int p)
    {
        pre[u]=++idx; anc[u][0]=p;
        for (int i=1; i<ML; i++) anc[u][i]=anc[anc[u][i-1]][i-1];
        for (int v:G[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
        }
        post[u]=idx;
    }
    bool check(int u, int v) { return pre[u]<=pre[v] && pre[v]<=post[u]; }
    int qry(int u, int v)
    {
        if (dep[u]>dep[v]) swap(u, v);
        if (check(u, v)) return u;
        for (int i=ML-1; i>=0; i--) if (anc[u][i] && !check(anc[u][i], v)) u=anc[u][i];
        return anc[u][0];
    }
}

int main()
{
    cin>>N>>Q;
    for (int i=2; i<=N; i++)
    {
        int P; cin>>P; P++;
        G[P].push_back(i);
        G[i].push_back(P);
    }
    lca::dfs(1, 0);
    while (Q--)
    {
        int U, V; cin>>U>>V; U++; V++;
        cout<<lca::qry(U, V)-1<<endl;
    }
    return 0;
}