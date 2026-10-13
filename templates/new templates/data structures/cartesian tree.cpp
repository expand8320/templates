// https://judge.yosupo.jp/submission/338394
// upd 2025/12/19
#include <iostream>
#include <stack>
using namespace std;

const int MN=1e6+13;
int N, A[MN];
int lp[MN], rp[MN];
int par[MN];

int main()
{
    cin>>N;
    for (int i=1; i<=N; i++) cin>>A[i];
    stack<int> st;
    for (int i=1; i<=N; i++)
    {
        while (st.size() && A[st.top()]>A[i])
        {
            lp[i]=st.top();
            st.pop();
        }
        if (st.size()) rp[st.top()]=i;
        st.push(i);
    }
    int rt;
    while (st.size()>1) st.pop();
    rt=st.top(); st.pop();
    for (int i=1; i<=N; i++)
    {
        if (lp[i]) par[lp[i]]=i;
        if (rp[i]) par[rp[i]]=i;
    }
    par[rt]=rt;
    for (int i=1; i<=N; i++) cout<<par[i]-1<<' '; cout<<endl;
    return 0;
}