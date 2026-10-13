// https://judge.yosupo.jp/submission/338400
// done
#include <iostream>
using namespace std;
using ll=long long;

const int MN=5e5+13;
int N, Q;
ll A[MN];

namespace fwt
{
    ll s[MN];
    void init()
    {
        for (int i=1; i<=N; i++)
        {
            s[i]+=A[i];
            if (i+(i&-i)<=N) s[i+(i&-i)]+=s[i];
        }
    }
    void upd(int p, ll x) { for (; p<=N; p+=(p&-p)) s[p]+=x; }
    ll qry(int p) { ll z=0; for (; p>0; p-=(p&-p)) z+=s[p]; return z; }
    ll qry(int l, int r) { return qry(r)-qry(l-1); }
}

int main()
{
    cin>>N>>Q;
    for (int i=1; i<=N; i++) cin>>A[i];
    fwt::init();
    while (Q--)
    {
        int T; cin>>T;
        if (T==0)
        {
            int P; ll X; cin>>P>>X; P++;
            fwt::upd(P, X);
        }
        else
        {
            int L, R; cin>>L>>R; L++;
            cout<<fwt::qry(L, R)<<endl;
        }
    }
    return 0;
}