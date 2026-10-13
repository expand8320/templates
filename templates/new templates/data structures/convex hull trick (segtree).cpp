// https://judge.yosupo.jp/submission/338405
// upd 2025/12/19
#include <iostream>
using namespace std;
using ll=long long;

const int MN=2e5+13;
const int inf32=1e9;
const ll inf64=1e18;
int N, Q;
struct line
{
    ll a=0, b=inf64;
    ll operator()(ll x) { return a*x+b; }
    bool operator==(line x) { return a==x.a && b==x.b; }
};

namespace seg
{
    const ll eps=0;
    ll st[MN<<2], te[MN<<2], mid[MN<<2];
    int lp[MN<<2], rp[MN<<2], idx;
    line mn[MN<<2];
    int build(ll l, ll r)
    {
        int u=++idx;
        st[u]=l; te[u]=r; mid[u]=(st[u]+te[u])>>1;
        return u;
    }
    void build(int u)
    {
        if (!lp[u]) lp[u]=build(st[u], mid[u]);
        if (!rp[u]) rp[u]=build(mid[u]+1, te[u]);
    }
    void ins(int u, line x)
    {
        bool bst=x(st[u])<mn[u](st[u]);
        bool bm=x(mid[u])<mn[u](mid[u]);
        bool bte=x(te[u])<mn[u](te[u]);
        if (bm) swap(x, mn[u]);
        if (te[u]-st[u]<=eps || x==mn[u] || bst==bte) return;
        build(u);
        if (bst!=bm) ins(lp[u], x);
        else ins(rp[u], x);
    }
    ll qry(int u, ll x)
    {
        if (st[u]==te[u] || !lp[u]) return mn[u](x);
        build(u);
        if (x<=mid[u]) return min(mn[u](x), qry(lp[u], x));
        else return min(mn[u](x), qry(rp[u], x));
    }
}

int main()
{
    cin>>N>>Q;
    seg::build(-inf32, inf32);
    while (N--)
    {
        ll A, B; cin>>A>>B;
        seg::ins(1, {A, B});
    }
    while (Q--)
    {
        int T; cin>>T;
        if (T==0)
        {
            ll A, B; cin>>A>>B;
            seg::ins(1, {A, B});
        }
        else
        {
            ll X; cin>>X;
            cout<<seg::qry(1, X)<<endl;
        }
    }
    return 0;
}