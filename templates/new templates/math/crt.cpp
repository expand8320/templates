// https://www.luogu.com.cn/record/266668943
// upd 2026/3/12
#include <iostream>
using namespace std;
using ll=long long;
using bll=__int128;

void exgcd(bll a, bll b, bll &x, bll &y)
{
    if (!b) { x=1; y=0; return; }
    exgcd(b, a%b, x, y); ll t=x;
    x=y; y=t-ll(a/b)*y;
}

int main()
{
    int T; cin>>T;
    bll ans=0, p=1;
    while (T--)
    {
        bll M, R; ll tM, tR; cin>>tM>>tR; M=tM; R=tR;
        bll X, Y; exgcd(p, M, X, Y);
        ans+=(R-ans)*X*p;
        p*=M;
        ans=(ans%p+p)%p;
    }
    cout<<ll(ans)<<endl;
    return 0;
}