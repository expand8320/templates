// upd 2025/12/19
#include <iostream>
//#define getchar() getchar_unlocked()
using namespace std;
using ll=long long;
using bll=__int128;

inline void rd(bll &x)
{
	x=0; bll f=1; char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	x*=f;
}
inline void wr(bll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9) wr(x/10);
	putchar(x%10+'0');
}

int main()
{
    int t; cin>>t;
    while (t--)
    {
		bll x; rd(x); wr(x);
        cout<<endl;
    }
    return 0;
}