// https://judge.yosupo.jp/submission/338406
// don't understand lol
#include <iostream>
#include <set>
using namespace std;
using ll=long long;

const ll inf64=1e18;
int N, Q;

struct line
{
    mutable ll a, b, p;
    ll operator()(ll x) { return a*x+b; }
    bool operator<(line x) const { return a<x.a; }
    bool operator<(ll x) const { return p<x; }
};
namespace cht
{
    multiset<line, less<>> st;
    ll div(ll x, ll y) { return x/y-((x^y)<0 && x%y); }
    bool sect(multiset<line, less<>>::iterator x, multiset<line, less<>>::iterator y)
    {
        if (y==st.end()) return x->p=inf64,0;
        if (x->a==y->a) x->p=(x->b)>(y->b)?inf64:-inf64;
        else x->p=div((y->b)-(x->b), (x->a)-(y->a));
        return (x->p)>=(y->p);
    }
    void ins(line l)
    {
        auto z=st.insert(l), y=z++, x=y;
        while (sect(y, z)) z=st.erase(z);
        if (x!=st.begin() && sect(--x, y)) sect(x, y=st.erase(y));
        while ((y=x)!=st.begin() && ((--x)->p)>=(y->p)) sect(x, st.erase(y));
    }
    ll qry(ll x)
    {
        auto l=*st.lower_bound(x);
        return ll(l(x));
    }
}

int main()
{
    cin>>N>>Q;
    while (N--)
    {
        ll A, B; cin>>A>>B;
        cht::ins({-A, -B, 0});
    }
    while (Q--)
    {
        int T; cin>>T;
        if (T==0)
        {
            ll A, B; cin>>A>>B;
            cht::ins({-A, -B, 0});
        }
        else
        {
            ll X; cin>>X;
            cout<<-cht::qry(X)<<endl;
        }
    }
    return 0;
}