// https://codebreaker.xyz/submission/855953
// updated 2026/3/10
#include <iostream>
#include <queue>
using namespace std;
using ll=long long;
using ld=long double;

const ll inf64=1e18;
int N;

namespace cht
{
    struct line
    {
        ll A=0, B=-inf64;
        ll operator()(ll x) { return A*x+B; }
    };
    deque<line> q;
    ld sect(line x, line y)
    {
        if (x.A==y.A) return -inf64;
        else return ld(x.B-y.B)/ld(y.A-x.A);
    }
    void ins(line x)
    {
        while (q.size()>=2 && sect(x, q[q.size()-2])>=sect(x, q[q.size()-1])) q.pop_back();
        q.push_back(x);
    }
    ll qry(ll x)
    {
        if (q.size()==1 || sect(q[0], q[1])>ld(x)) return q[0](x);
        int l=1, r=q.size();
        while (l+1<r)
        {
            int mid=(l+r)>>1;
            if (sect(q[mid-1], q[mid])<=ld(x)) l=mid;
            else r=mid;
        }
        return q[l](x);
    }
}

int main()
{
    cin>>N;
    while (N--)
    {
        int T; cin>>T;
        if (T==1)
        {
            ll A, B; cin>>A>>B;
            cht::ins({A, B});
        }
        else
        {
            ll X; cin>>X;
            cout<<cht::qry(X)<<endl;
        }
    }
}