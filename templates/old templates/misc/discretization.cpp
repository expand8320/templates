// https://www.luogu.com.cn/record/253880245
// done
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MN=1e5+13;
int N, A[MN];

void driver()
{
    cin>>N;
    vector<int> t;
    for (int i=1; i<=N; i++)
    {
        cin>>A[i];
        t.push_back(A[i]);
    }
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int i=1; i<=N; i++)
    {
        A[i]=lower_bound(t.begin(), t.end(), A[i])-t.begin()+1;
        cout<<A[i]<<' ';
    } cout<<endl;
}
int main()
{
    int T; cin>>T;
    while (T--) driver();
    return 0;
}