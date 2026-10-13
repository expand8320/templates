// https://www.luogu.com.cn/record/253945297
// done
#include <iostream>
using namespace std;
using ll=long long;

const int MN=1e5+13;
int N, M;
ll A[MN];

namespace seg
{
    int st[MN<<2], te[MN<<2], mid[MN<<2];
    ll sum[MN<<2], lz[MN<<2];
    void build(int u, int l, int r)
    {
        st[u]=l; te[u]=r; mid[u]=(st[u]+te[u])>>1;
        lz[u]=0;
        if (st[u]==te[u]) sum[u]=A[st[u]];
        else
        {
            build(u*2, st[u], mid[u]);
            build(u*2+1, mid[u]+1, te[u]);
            sum[u]=sum[u*2]+sum[u*2+1];
        }
    }
    void prop(int u)
    {
        if (!lz[u]) return;
        sum[u*2]+=lz[u]*(mid[u]-st[u]+1);
        lz[u*2]+=lz[u];
        sum[u*2+1]+=lz[u]*(te[u]-mid[u]);
        lz[u*2+1]+=lz[u];
        lz[u]=0;
    }
    void upd(int u, int l, int r, ll x)
    {
        if (st[u]==l && te[u]==r)
        {
            sum[u]+=x*(te[u]-st[u]+1);
            lz[u]+=x;
            return;
        }
        prop(u);
        if (l<=mid[u]) upd(u*2, l, min(r, mid[u]), x);
        if (r>mid[u]) upd(u*2+1, max(mid[u]+1, l), r, x);
        sum[u]=sum[u*2]+sum[u*2+1];
    }
    ll qry(int u, int l, int r)
    {
        if (st[u]==l && te[u]==r) return sum[u];
        prop(u);
        ll z=0;
        if (l<=mid[u]) z+=qry(u*2, l, min(r, mid[u]));
        if (r>mid[u]) z+=qry(u*2+1, max(mid[u]+1, l), r);
        return z;
    }
}

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++) cin>>A[i];
    seg::build(1, 1, N);
    while (M--)
    {
        int T, L, R; cin>>T>>L>>R;
        if (T==1)
        {
            ll X; cin>>X;
            seg::upd(1, L, R, X);
        }
        else cout<<seg::qry(1, L, R)<<endl;
    }
    return 0;
}