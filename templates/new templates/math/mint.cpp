// https://atcoder.jp/contests/abc256/submissions/74021221
// upd 2026/3/12
#include <iostream>
using namespace std;
using ll=long long;

const int MN=2e5+13;
const ll mod=(119<<23)+1;
int N, M;

struct mint
{
    ll v;
    mint() { v=0; }
    mint(ll V) { v=(V%mod+mod)%mod; }
} A[MN];
mint operator+(mint x, mint y) { return mint(((x.v+y.v)%mod+mod)%mod); }
mint operator-(mint x, mint y) { return x+mint(-y.v); }
mint operator*(mint x, mint y) { return mint(((x.v*y.v)%mod+mod)%mod); }
mint &operator+=(mint &x, mint y) { x=x+y; return x; }
mint &operator-=(mint &x, mint y) { x=x-y; return x; }
mint &operator*=(mint &x, mint y) { x=x*y; return x; }
mint pow(mint x, ll y)
{
    mint z=1;
    while (y)
    {
        if (y&1) z*=x;
        x*=x; y/=2;
    }
    return z;
}
mint operator/(mint x, mint y) { return x*pow(y, mod-2); }
mint &operator/=(mint &x, mint y) { x=x/y; return x; }

struct fwt
{
    mint s[MN];
    fwt() {}
    void upd(int p, mint x) { for (; p<=N; p+=(p&-p)) s[p]+=x; }
    mint qry(int p)
    {
        mint z=0;
        for (; p; p-=(p&-p)) z+=s[p];
        return z;
    }
    mint qry(int l, int r) { return qry(r)-qry(l-1); }
} *x0, *x1, *x2;

int main()
{
    x0=new fwt(); x1=new fwt(); x2=new fwt();
    cin>>N>>M;
    for (int i=1; i<=N; i++)
    {
        cin>>A[i].v;
        x0->upd(i, A[i]);
        x1->upd(i, A[i]*i);
        x2->upd(i, A[i]*i*i);
    }
    while (M--)
    {
        int T; cin>>T;
        if (T==1)
        {
            int P; mint X; cin>>P>>X.v;
            X-=A[P];
            x0->upd(P, X);
            x1->upd(P, X*P);
            x2->upd(P, X*P*P);
            A[P]+=X;
        }
        else
        {
            mint P; cin>>P.v;
            mint cons=(P*P+P*3+2)*x0->qry(P.v);
            mint line=(P*2+3)*x1->qry(P.v);
            mint quad=x2->qry(P.v);
            mint ans=(cons-line+quad)/2;
            cout<<ans.v<<endl;
        }
    }
    return 0;
}