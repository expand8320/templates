// https://www.luogu.com.cn/record/266667110
// done
#include <iostream>
#include <queue>
#include <map>
using namespace std;

const int dx[]={-1, 0, 0, 1};
const int dy[]={0, -1, 1, 0};
string S, T="123804765";
map<string, int> vis, d;
char a[4][4];

int bfs()
{
    if (S==T) return 0;
    queue<string> q;
    d[S]=d[T]=0;
    q.push(S); q.push(T);
    vis[S]=1; vis[T]=2;
    while (q.size())
    {
        string u=q.front(); q.pop();
        int x, y;
        for (int i=0; i<9; i++)
        {
            a[i/3][i%3]=u[i];
            if (u[i]=='0')
            {
                x=i/3;
                y=i%3;
            }
        }
        for (int i=0; i<4; i++)
        {
            int tx=x+dx[i], ty=y+dy[i];
            if (0>tx || tx>=3 || 0>ty || ty>=3) continue;
            swap(a[x][y], a[tx][ty]);
            string v;
            for (int i=0; i<9; i++) v+=a[i/3][i%3];
            if (vis[v]==vis[u])
            {
                swap(a[x][y], a[tx][ty]);
                continue;
            }
            else if (vis[u]+vis[v]==3) return d[u]+d[v]+1;
            d[v]=d[u]+1;
            q.push(v);
            vis[v]=vis[u];
            swap(a[x][y], a[tx][ty]);
        }
    }
    return -1;
}

int main()
{
    cin>>S;
    cout<<bfs()<<endl;
    return 0;
}