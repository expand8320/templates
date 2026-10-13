// https://judge.yosupo.jp/submission/338402
// done
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MN=2e5+13;
int N, Q, A[MN];
int m, rev[MN], rt[MN];

namespace seg
{
    int st[MN<<5], te[MN<<5], mid[MN<<5];
    int lp[MN<<5], rp[MN<<5], idx=0;
    int s[MN<<5];
    int build(int l, int r)
    {
        int u=++idx;
        st[u]=l; te[u]=r; mid[u]=(st[u]+te[u])/2;
        s[u]=0;
        if (st[u]==te[u]);
        else
        {
            lp[u]=build(st[u], mid[u]);
            rp[u]=build(mid[u]+1, te[u]);
        }
        return u;
    }
    int clone(int o)
    {
        int u=++idx;
        st[u]=st[o]; te[u]=te[o]; mid[u]=mid[o];
        lp[u]=lp[o]; rp[u]=rp[o]; s[u]=s[o];
        return u;
    }
    int upd(int o, int p)
    {
        int u=clone(o); s[u]++;
        if (st[u]==te[u]);
        else if (p<=mid[u]) lp[u]=upd(lp[u], p);
        else rp[u]=upd(rp[u], p);
        return u;
    }
    int qry(int u, int v, int k)
    {
        if (st[u]==te[u]) return st[u];
        if (s[lp[v]]-s[lp[u]]>=k) return qry(lp[u], lp[v], k);
        else return qry(rp[u], rp[v], k-(s[lp[v]]-s[lp[u]]));
    }
}

int main()
{
    cin>>N>>Q;
    vector<int> t;
    for (int i=1; i<=N; i++)
    {
        cin>>A[i];
        t.push_back(A[i]);
    }
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int i=1; i<=N; i++)
    {
        int v=lower_bound(t.begin(), t.end(), A[i])-t.begin()+1;
        rev[v]=A[i];
        A[i]=v;
    }
    m=t.size();
    
    rt[0]=seg::build(1, m);
    for (int i=1; i<=N; i++) rt[i]=seg::upd(rt[i-1], A[i]);
    while (Q--)
    {
        int L, R, K; cin>>L>>R>>K; L++; K++;
        cout<<rev[seg::qry(rt[L-1], rt[R], K)]<<endl;
    }
    return 0;
}