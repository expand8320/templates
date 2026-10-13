// https://www.luogu.com.cn/record/266665836
// upd 2026/3/12
#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

const int MN=2e5+13;
int N, M, R;
vector<int> G[MN];
ll A[MN];
int seq[MN], pre[MN], post[MN], idx=0;

namespace fwt
{
    ll s1[MN], s2[MN];
    void upd(ll s[MN], int p, ll x) { for (; p<=N; p+=(p&-p)) s[p]+=x; }
    void upd(int l, int r, ll x)
    {
        upd(s1, l, x); upd(s1, r+1, -x);
        upd(s2, l, x*l); upd(s2, r+1, -x*(r+1));
    }
    ll qry(ll s[MN], int p)
    {
        ll z=0;
        for (; p; p-=(p&-p)) z+=s[p];
        return z;
    }
    ll qry(int l, int r)
    {
        return (qry(s1, r)*(r+1)-qry(s2, r))-(qry(s1, l-1)*l-qry(s2, l-1));
    }
}
namespace hld
{
    int dep[MN], par[MN], sz[MN];
    int hv[MN], hd[MN];
    void dfs1(int u)
    {
        sz[u]=1;
        for (int v:G[u]) if (v!=par[u])
        {
            dep[v]=dep[u]+1; par[v]=u;
            dfs1(v);
            if (!hv[u] || sz[hv[u]]<sz[v]) hv[u]=v;
            sz[u]+=sz[v];
        }
    }
    void dfs2(int u, int head)
    {
        pre[u]=++idx; seq[idx]=u;
        hd[u]=head;
        if (hv[u]) dfs2(hv[u], head);
        for (int v:G[u]) if (v!=par[u] && v!=hv[u]) dfs2(v, v);
        post[u]=idx;
    }
    void upd(int u, int v, ll x)
    {
        while (hd[u]!=hd[v])
        {
            if (dep[hd[u]]<dep[hd[v]]) swap(u, v);
            fwt::upd(pre[hd[u]], pre[u], x);
            u=par[hd[u]];
        }
        if (dep[u]>dep[v]) swap(u, v);
        fwt::upd(pre[u], pre[v], x);
    }
    ll qry(int u, int v)
    {
        ll z=0;
        while (hd[u]!=hd[v])
        {
            if (dep[hd[u]]<dep[hd[v]]) swap(u, v);
            z+=fwt::qry(pre[hd[u]], pre[u]);
            u=par[hd[u]];
        }
        if (dep[u]>dep[v]) swap(u, v);
        return z+fwt::qry(pre[u], pre[v]);
    }
    void init()
    {
        dep[R]=par[R]=0;
        dfs1(R);
        dfs2(R, R);
    }
}

int main()
{
    ll P; cin>>N>>M>>R>>P;
    for (int i=1; i<=N; i++) cin>>A[i];
    for (int i=1; i<N; i++)
    {
        int U, V; cin>>U>>V;
        G[U].push_back(V);
        G[V].push_back(U);
    }
    hld::init();
    for (int i=1; i<=N; i++) fwt::upd(pre[i], pre[i], A[i]);
    while (M--)
    {
        int T, U; cin>>T>>U;
        if (T==1)
        {
            int V; ll X; cin>>V>>X;
            hld::upd(U, V, X);
        }
        else if (T==2)
        {
            int V; cin>>V;
            cout<<hld::qry(U, V)%P<<endl;
        }
        else if (T==3)
        {
            ll X; cin>>X;
            fwt::upd(pre[U], post[U], X);
        }
        else cout<<fwt::qry(pre[U], post[U])%P<<endl;
    }
    return 0;
}