// https://www.luogu.com.cn/record/266415816
// done
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;
using tl3=tuple<ll, ll, ll>;

const int MN=2e5+13, B=500;
int N, Q, A[MN];
vector<tl3> qry;
int c[MN]={0}; string ans[MN];
int cur=0;

void add(int p)
{
    c[A[p]]++;
    if (c[A[p]]==1) cur++;
}
void del(int p)
{
    c[A[p]]--;
    if (c[A[p]]==0) cur--;
}

int main()
{
    cin>>N>>Q;
    for (int i=1; i<=N; i++) cin>>A[i];
    for (int i=1; i<=Q; i++)
    {
        int l, r; cin>>l>>r;
        qry.push_back({l, r, i});
    }
    sort(qry.begin(), qry.end(), [](tl3 x, tl3 y)
    {
        auto [xl, xr, xid]=x;
        auto [yl, yr, yid]=y;
        if (int(xl/B)!=int(yl/B)) return xl<yl;
        else if ((int(xl/B))&1) return xr<yr;
        else return xr>yr;
    });
    int st=0, te=-1;
    for (auto [l, r, id]:qry)
    {
        while (st>l) add(--st);
        while (te<r) add(++te);
        while (st<l) del(st++);
        while (te>r) del(te--);
        if (cur==r-l+1) ans[id]="Yes";
        else ans[id]="No";
    }
    for (int i=1; i<=Q; i++) cout<<ans[i]<<endl;
    return 0;
}