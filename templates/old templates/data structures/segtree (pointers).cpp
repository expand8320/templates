// https://www.luogu.com.cn/record/253947151
// done
#include <iostream>
using namespace std;
using ll=long long;

const int MN=1e5+13;
int N, M;
ll A[MN];

struct SEG
{
    int st, te, mid;
    ll sum, lz;
    SEG *lp, *rp;
    SEG(int l, int r)
    {
        st=l; te=r; mid=(st+te)>>1;
        lz=0;
        if (st==te) sum=A[st];
        else
        {
            lp=new SEG(st, mid);
            rp=new SEG(mid+1, te);
            sum=lp->sum+rp->sum;
        }
    }
    void prop()
    {
        if (lz==0) return;
        lp->sum+=lz*(mid-st+1);
        lp->lz+=lz;
        rp->sum+=lz*(te-mid);
        rp->lz+=lz;
        lz=0;
    }
    void upd(int l, int r, ll x)
    {
        if (st==l && te==r)
        {
            sum+=x*(te-st+1);
            lz+=x;
            return;
        }
        prop();
        if (l<=mid) lp->upd(l, min(r, mid), x);
        if (r>mid) rp->upd(max(mid+1, l), r, x);
        sum=lp->sum+rp->sum;
    }
    ll qry(int l, int r)
    {
        if (st==l && te==r) return sum;
        prop();
        ll z=0;
        if (l<=mid) z+=lp->qry(l, min(r, mid));
        if (r>mid) z+=rp->qry(max(mid+1, l), r);
        return z;
    }
} *seg;

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++) cin>>A[i];
    seg=new SEG(1, N);
    while (M--)
    {
        int T, L, R; cin>>T>>L>>R;
        if (T==1)
        {
            ll X; cin>>X;
            seg->upd(L, R, X);
        }
        else cout<<seg->qry(L, R)<<endl;
    }
    return 0;
}