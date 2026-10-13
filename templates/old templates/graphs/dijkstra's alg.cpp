// https://judge.yosupo.jp/submission/338436
// done
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;

const int MN=5e5+13;
const ll inf64=1e18;
int N, M, S, T;
vector<pll> G[MN];
bool vis[MN];
ll d[MN]; int prv[MN];

void dijk()
{
    for (int i=1; i<=N; i++) d[i]=inf64;
    priority_queue<pll, vector<pll>, greater<pll>> q;
    d[S]=0;
    q.push({0, S});
    while (q.size())
    {
        auto [t, u]=q.top(); q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:G[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
                prv[v]=u;
            }
        }
    }
}

int main()
{
    cin>>N>>M>>S>>T; S++; T++;
    while (M--)
    {
        int U, V; ll W; cin>>U>>V>>W; U++; V++;
        G[U].push_back({V, W});
    }
    dijk();
    if (d[T]==inf64) { cout<<-1<<endl; return 0; }
    cout<<d[T]<<' ';
    vector<int> vec;
    while (T!=S)
    {
        vec.push_back(T);
        T=prv[T];
    }
    reverse(vec.begin(), vec.end());
    cout<<vec.size()<<endl;
    for (int i:vec) cout<<prv[i]-1<<' '<<i-1<<endl;
    return 0;
}