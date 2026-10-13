// https://www.luogu.com.cn/record/253945495
// upd 2025/12/19
#include <iostream>
using namespace std;
using ll=long long;

const int MN=1e5+13;
int N, M;
ll A[MN];

namespace fwt
{
    ll s1[MN], s2[MN];
    void init()
    {
        for (int i=1; i<=N; i++)
        {
            s1[i]+=A[i]; s2[i]+=A[i]*i;
            if (i>1)
            {
                s1[i]-=A[i-1];
                s2[i]-=A[i-1]*i;
            }
            if (i+(i&-i)<=N)
            {
                s1[i+(i&-i)]+=s1[i];
                s2[i+(i&-i)]+=s2[i];
            }
        }
    }
    void upd(ll s[MN], int p, ll x) { for (; p<=N; p+=(p&-p)) s[p]+=x; }
    void upd(int l, int r, ll x)
    {
        upd(s1, l, x); upd(s1, r+1, -x);
        upd(s2, l, x*l); upd(s2, r+1, -x*(r+1));
    }
    ll qry(ll s[MN], int p) { ll z=0; for (; p>0; p-=(p&-p)) z+=s[p]; return z; }
    ll qry(int l, int r)
    {
        ll zr=qry(s1, r)*(r+1)-qry(s2, r);
        ll zl=qry(s1, l-1)*l-qry(s2, l-1);
        return zr-zl;
    }
}

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++) cin>>A[i];
    fwt::init();
    while (M--)
    {
        int T, L, R; cin>>T>>L>>R;
        if (T==1)
        {
            ll X; cin>>X;
            fwt::upd(L, R, X);
        }
        else cout<<fwt::qry(L, R)<<endl;
    }
    return 0;
}