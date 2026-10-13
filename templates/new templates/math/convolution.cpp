// https://judge.yosupo.jp/submission/338433
// upd 2025/12/19
#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

const int MN=2e6+13;
const ll mod=(119<<23)+1;
int N, M;
ll A[MN], B[MN];

ll pow(ll x, ll y)
{
    x%=mod;
    ll z=1;
    while (y>0)
    {
        if (y&1) z=(z*x)%mod;
        x=(x*x)%mod; y>>=1;
    }
    return z;
}
namespace ntt
{
    const ll g=3, ginv=(mod+1)/g;
    int lim, l, r[MN];
    vector<ll> a, b;
    void ntt(vector<ll> &z, int t)
    {
        for (int i=0; i<lim; i++) if (i<r[i]) swap(z[i], z[r[i]]);
        for (int mid=1; mid<lim; mid<<=1)
        {
            ll wn=pow((t==1?g:ginv), (mod-1)/(mid<<1));
            for (int i=0; i<lim; i+=(mid<<1))
            {
                ll w=1;
                for (int j=0; j<mid; j++, w=(w*wn)%mod)
                {
                    ll x=z[i+j], y=(w*z[i+mid+j])%mod;
                    z[i+j]=(x+y)%mod;
                    z[i+mid+j]=((x-y)%mod+mod)%mod;
                }
            }
        }
    }
    vector<ll> qry(int deg, ll A[MN], ll B[MN])
    {
        lim=1; l=0;
        while (lim<=deg) { lim<<=1; l++; }
        for (int i=0; i<lim; i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        a.resize(lim); b.resize(lim);
        for (int i=0; i<lim; i++)
        {
            a[i]=A[i];
            b[i]=B[i];
        }
        ntt::ntt(a, 1); ntt::ntt(b, 1);
        for (int i=0; i<lim; i++) a[i]=(a[i]*b[i])%mod;
        ntt::ntt(a, -1);
        ll inv=pow(lim, mod-2);
        vector<ll> z(deg+1);
        for (int i=0; i<=deg; i++) z[i]=(a[i]*inv)%mod;
        return z;
    }
}

int main()
{
    cin>>N>>M; N--; M--;
    for (int i=0; i<=N; i++) cin>>A[i];
    for (int i=0; i<=M; i++) cin>>B[i];
    vector<ll> z=ntt::qry(N+M, A, B);
    for (ll i:z) cout<<i<<' '; cout<<endl;
    return 0;
}