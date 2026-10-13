// https://cses.fi/problemset/result/17848684/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MN=5e5+13, ML=22;
int N, M, Q;
vector<int> G[MN], bct[MN];
int pre[MN], low[MN], idx, cnt;
stack<int> st;

void dfs(int u)
{
    pre[u]=low[u]=++idx;
    st.push(u);
    for (int v:G[u])
    {
        if (!pre[v])
        {
            dfs(v);
            low[u]=min(low[u], low[v]);
            if (low[v]==pre[u])
            {
                cnt++;
                while (st.size())
                {
                    int x=st.top(); st.pop();
                    bct[x].push_back(N+cnt);
                    bct[N+cnt].push_back(x);
                    if (x==v) break;
                }
                bct[u].push_back(N+cnt);
                bct[N+cnt].push_back(u);
            }
        }
        else low[u]=min(low[u], pre[v]);
    }
}
namespace lca
{
    int st[MN][ML], lg[MN], dep[MN];
    int pre[MN], post[MN], idx;
    int f(int u, int v)
    {
        if (dep[u]<dep[v]) return u;
        else return v;
    }
    void dfs(int u, int p)
    {
        st[++idx][0]=u; pre[u]=idx;
        for (int v:bct[u])
        {
            if (v!=p)
            {
                dep[v]=dep[u]+1;
                dfs(v, u);
                st[++idx][0]=u;
            }
        }
        post[u]=idx;
    }
    void init()
    {
        dfs(1, 0);
        for (int i=2; i<=idx; i++) lg[i]=lg[i>>1]+1;
        for (int j=1; j<ML; j++)
        {
            for (int i=1; i+(1<<j)-1<=idx; i++)
            {
                st[i][j]=f(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int qry(int u, int v)
    {
        int l=pre[u], r=pre[v];
        if (l>r) swap(l, r);
        int i=lg[r-l+1];
        return f(st[l][i], st[r-(1<<i)+1][i]);
    }
    int check(int u, int v)
    {
        return pre[u]<=pre[v] && pre[v]<=post[u];
    }
}

int main()
{
    cin>>N>>M>>Q;
    while (M--)
    {
        int U, V; cin>>U>>V;
        G[U].push_back(V);
        G[V].push_back(U);
    }
    dfs(1);
    lca::init();
    while (Q--)
    {
        int A, B, C; cin>>A>>B>>C;
        int l=lca::qry(A, B);
        if (!lca::check(l, C)) cout<<"YES"<<endl;
        else if (lca::check(C, A) || lca::check(C, B)) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}
