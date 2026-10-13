// https://www.luogu.com.cn/record/266415243
// done
#include <iostream>
using namespace std;

const int MN=2e6+13, ML=22;
int N, K;

namespace trie
{
    int g[MN][2]={0}, idx=0;
    int sz[MN]={0};
    void ins(int x)
    {
        int u=0;
        for (int i=ML; i>=0; i--)
        {
            int b=(x>>i)&1;
            if (!g[u][b]) g[u][b]=++idx;
            u=g[u][b];
            sz[u]++;
        }
    }
    int qry(int x)
    {
        int u=0, z=0; bool f=1;
        for (int i=ML; i>=0; i--)
        {
            int b=(x>>i)&1, req=(K>>i)&1; b^=req;
            if (req==1 && g[u][!b]) z+=sz[g[u][!b]];
            if (!g[u][b]) { f=0; break; }
            u=g[u][b];
        }
        if (f) z+=sz[u];
        return z;
    }
}

int main()
{
    cin>>N>>K;
    while (N--)
    {
        int x; cin>>x;
        trie::ins(x);
    }
    int ans=0;
    for (int i=0; i<(1<<ML); i++) ans=max(ans, trie::qry(i));
    cout<<ans<<endl;
    return 0;
}