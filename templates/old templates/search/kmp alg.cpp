// https://www.luogu.com.cn/record/266666195
// done
#include <iostream>
using namespace std;

const int MN=2e6+13;
int N, M, pi[MN];
string S, T, str;

int main()
{
    cin>>S>>T;
    N=S.size(); M=T.size();
    str=T+'#'+S;
    pi[0]=0;
    for (int i=1; i<=N+M; i++)
    {
        int j=pi[i-1];
        while (j && str[j]!=str[i]) j=pi[j-1];
        if (str[i]==str[j]) j++;
        pi[i]=j;
    }
    for (int i=M*2; i<=N+M; i++) if (pi[i]==M) cout<<i-M*2+1<<endl;
    for (int i=0; i<M; i++) cout<<pi[i]<<' '; cout<<endl;
    return 0;
}