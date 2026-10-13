// upd 2025/12/19
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <climits>
using namespace std;
using ll=long long;

const int mod=1e7+13;

namespace ch
{
    ll ch[mod], FR;
    void init()
    {
        for (int i=0; i<mod; i++) ch[i]=LONG_LONG_MAX;
        FR=chrono::steady_clock::now().time_since_epoch().count();
    }
    static ll r(ll x)
    {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
    int h(ll x)
    {
        ll p=r(x+FR)%mod;
        while (ch[p]!=LONG_LONG_MAX)
        {
            if (ch[p]==x) return p;
            p=(p+1)%mod;
        }
        ch[p]=x;
        return p;
    }
}
struct ch1
{
    size_t operator()(ll x) const
    {
        static const ll FR=chrono::steady_clock::now().time_since_epoch().count();
        x^=FR;
        return x^(x>>16);
    }
};
struct ch2
{
    static ll r(ll x)
    {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator()(ll x) const
    {
        static const ll FR=chrono::steady_clock::now().time_since_epoch().count();
        return r(x+FR);
    }
};

int main() {}