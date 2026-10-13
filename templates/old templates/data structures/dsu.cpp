// https://judge.yosupo.jp/submission/338396
// done
#include <iostream>
using namespace std;

const int MN=2e5+13;
int N, M;
int dsu[MN];

int find(int x)
{
    if (dsu[x]==x) return x;
    else return dsu[x]=find(dsu[x]);
}
bool unite(int x, int y)
{
    x=find(x); y=find(y);
    if (x==y) return 0;
    dsu[y]=x;
    return 1;
}

int main()
{
    cin>>N>>M;
    for (int i=1; i<=N; i++) dsu[i]=i;
    while (M--)
    {
        int T, U, V; cin>>T>>U>>V; U++; V++;
        if (T==0) unite(U, V);
        else cout<<(find(U)==find(V))<<endl;
    }
    return 0;
}