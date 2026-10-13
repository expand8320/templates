// https://judge.yosupo.jp/submission/338425
// upd 2025/12/19
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using ll=long long;

const int MN=2e5+13;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int N, Q;
ll A[MN];

namespace trp
{
    int rt, lp[MN], rp[MN], sz[MN], idx;
    ll val[MN], sum[MN], pr[MN]; bool lz[MN];
    void pull(int u)
    {
        sz[u]=1+sz[lp[u]]+sz[rp[u]];
        sum[u]=val[u]+sum[lp[u]]+sum[rp[u]];
    }
    void push(int u)
    {
        if (!lz[u]) return;
        swap(lp[u], rp[u]);
        lz[lp[u]]^=1; lz[rp[u]]^=1;
        lz[u]=0;
    }
    int merge(int u, int v)
    {
        if (!u || !v) return u+v;
        if (pr[u]<pr[v])
        {
            push(u);
            rp[u]=merge(rp[u], v);
            pull(u);
            return u;
        }
        else
        {
            push(v);
            lp[v]=merge(u, lp[v]);
            pull(v);
            return v;
        }
    }
    void split(int u, int k, int &t1, int &t2)
    {
        if (!u) { t1=t2=0; return; }
        push(u);
        if (sz[lp[u]]<k)
        {
            t1=u;
            split(rp[u], k-sz[lp[u]]-1, rp[u], t2);
        }
        else
        {
            t2=u;
            split(lp[u], k, t1, lp[u]);
        }
        pull(u);
    }
    void ins(int x)
    {
        int t1, t2; split(rt, x, t1, t2);
        idx++; val[idx]=sum[idx]=A[x]; pr[idx]=rng(); sz[idx]=1;
        rt=merge(merge(t1, idx), t2);
    }
    void rev(int l, int r)
    {
        int t1, t2, t3;
        split(rt, l-1, t1, t2);
        split(t2, r-l+1, t2, t3);
        lz[t2]^=1;
        rt=merge(t1, merge(t2, t3));
    }
    ll qry(int l, int r)
    {
        int t1, t2, t3;
        split(rt, l-1, t1, t2);
        split(t2, r-l+1, t2, t3);
        ll z=sum[t2];
        rt=merge(t1, merge(t2, t3));
        return z;
    }
}

int main()
{
    cin>>N>>Q;
    for (int i=1; i<=N; i++)
    {
        cin>>A[i];
        trp::ins(i);
    }
    while (Q--)
    {
        int T, L, R; cin>>T>>L>>R; L++;
        if (T==0) trp::rev(L, R);
        else cout<<trp::qry(L, R)<<endl;
    }
    return 0;
}