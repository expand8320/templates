// https://judge.yosupo.jp/submission/338418
// done
#include <iostream>
#include <vector>
using namespace std;

const int MN=5e5+13, ML=22;
int N, Q;
vector<int> G[MN];

namespace lca
{
    int st[MN<<1][ML], lg[MN<<1];
    int pre[MN], dep[MN], idx;
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
        dfs(1, 0);
        for (int i=2; i<=idx; i++) lg[i]=lg[i>>1]+1;
        for (int j=1; (1<<j)<=idx; j++)
        {
            for (int i=1; i+(1<<j)-1<=idx; i++)
            {
                st[i][j]=f(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int qry(int u, int v)
    {
        int l=pre[u], r=pre[v];
        if (l>r) swap(l, r);
        int t=lg[r-l+1];
        return f(st[l][t], st[r-(1<<t)+1][t]);
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
    lca::init();
    while (Q--)
    {
        int U, V; cin>>U>>V; U++; V++;
        cout<<lca::qry(U, V)-1<<endl;
    }
    return 0;
}