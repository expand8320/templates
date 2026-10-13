// https://judge.yosupo.jp/submission/338403
// upd 2025/12/19
#include <iostream>
using namespace std;
using ll=long long;

const int MN=5e5+13;
int N, Q;
ll A[MN];

namespace seg
{
    ll s[MN<<1];
    void init()
    {
        for (int i=0; i<N; i++) s[i+N]=A[i+1];
        for (int i=N-1; i>0; i--) s[i]=s[i*2]+s[i*2+1];
    }
    void upd(int p, ll x) { for (s[p+=N-1]+=x; p>1; p>>=1) s[p>>1]=s[p]+s[p^1]; }
    ll qry(int l, int r)
    {
        ll z=0;
        for (l+=N-1, r+=N; l<r; l>>=1, r>>=1)
        {
            if (l&1) z+=s[l++];
            if (r&1) z+=s[--r];
        }
        return z;
    }
}

int main()
{
    cin>>N>>Q;
    for (int i=1; i<=N; i++) cin>>A[i];
    seg::init();
    while (Q--)
    {
        int T; cin>>T;
        if (T==0)
        {
            int P; ll X; cin>>P>>X; P++;
            seg::upd(P, X);
        }
        else
        {
            int L, R; cin>>L>>R; L++;
            cout<<seg::qry(L, R)<<endl;
        }
    }
    return 0;
}