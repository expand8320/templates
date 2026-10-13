// https://codeforces.com/contest/1970/submission/366322754
// done
#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

const int MN=2e5+13;
const ll mod=1e9+7;
int N, M;
ll S[MN], L[MN];

struct mat
{
    int n, m;
    vector<vector<ll>> a;
    mat(int N, int M) { n=N; m=M; a.resize(n, vector<ll>(m, 0)); }
    vector<ll>& operator[](int x) { return a[x]; }
};
mat operator*(mat &x, mat &y)
{
    mat z(x.n, y.m);
    for (int i=0; i<x.n; i++)
    {
        for (int j=0; j<y.m; j++)
        {
            for (int k=0; k<x.m; k++)
            {
                z[i][j]+=x[i][k]*y[k][j];
                z[i][j]%=mod;
            }
        }
    }
    return z;
}
mat &operator*=(mat &x, mat y) { x=x*y; return x; }
mat pow(mat &x, int y)
{
    mat z(x.n, x.m);
    for (int i=0; i<x.n; i++) z[i][i]=1;
    while (y)
    {
        if (y&1) z*=x;
        x*=x; y>>=1;
    }
    return z;
}

int main()
{
    cin>>N>>M;
    for (int i=0; i<N; i++) cin>>S[i];
    for (int i=0; i<N; i++)
    {
        cin>>L[i];
        S[i]+=L[i];
    }
    mat dp(1, N), b(N, 2), c(2, N);
    for (int j=0; j<N; j++)
    {
        if (j==0) dp[0][j]=1;
        else dp[0][j]=0;
    }
    for (int i=0; i<N; i++)
    {
        b[i][0]=S[i];
        b[i][1]=L[i];
    }
    for (int j=0; j<N; j++)
    {
        c[0][j]=S[j];
        c[1][j]=mod-L[j];
    }
    mat a=c*b;
    a=pow(a, M-1);
    dp*=b; dp*=a; dp*=c;
    ll ans=0;
    for (int j=0; j<N; j++) ans=(ans+dp[0][j])%mod;
    cout<<ans<<endl;
    return 0;
}