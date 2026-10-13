// https://www.luogu.com.cn/record/266434009
// done
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pii=pair<int, int>;

const int MV=3e5+13;
const int inf32=1e9;
int N, M;
vector<pii> g[MV];
int d[MV];

int get(int x, int y) { return x*(M+1)+y; }
void add(int u, int v, int w)
{
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}
void bfs()
{
    deque<int> q;
    for (int i=0; i<=get(N, M); i++) d[i]=inf32;
    d[0]=0;
    q.push_back(0);
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (auto [v, w]:g[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (w) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}

int main()
{
    cin>>N>>M;
    for (int i=0; i<N; i++)
    {
        char C;
        for (int j=0; j<M; j++)
        {
            cin>>C;
            add(get(i, j), get(i+1, j+1), (C=='/'));
            add(get(i+1, j), get(i, j+1), (C!='/'));
        }
    }
    bfs();
    if (d[get(N, M)]==inf32) cout<<"NO SOLUTION"<<endl;
    else cout<<d[get(N, M)]<<endl;
    return 0;
}