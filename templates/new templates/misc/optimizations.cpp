// upd 2025/12/19
#include <iostream>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
//#pragma GCC optimize("Ofast,fast-math")
using namespace std;
using ll=long long;

#include <cassert>
const int _bsz=1<<22;
inline namespace fi {
char _bf[_bsz]; int _p, _l;
char rd()
{
	if (_p==_l)
	{
		_p=0; _l=int(fread(_bf, 1, _bsz, stdin));
		if (!_l) return EOF;
	}
	return _bf[_p++];
}
template<typename T> void rd(T &x)
{
	x=0; T s=1; char c;
	while (!isdigit(c=rd())) if (c=='-') s*=-1;
	x=T(c-'0');
	while (isdigit(c=rd())) x=x*10+T(c-'0');
	x*=s;
}}
void rd() {}
template<typename T1, typename... T2> void rd(T1 &x, T2&... y) { rd(x), rd(y...); }
inline namespace fo {
char _bf[_bsz]; int _p;
void flout() { fwrite(_bf, 1, _p, stdout); _p=0; }
void wr(char c) { if (_p==_bsz) flout(); _bf[_p++]=c; }
template<typename T> void wr(T x)
{
	static char tbf[100];
	if (x<0) { wr('-'); x*=-1; }
	int l=0;
	for (; x>=10; x/=10) tbf[l++]=char('0'+(x%10));
	wr(char('0'+x));
	while (l) wr(tbf[--l]);
}
void _init() { assert(atexit(flout)==0); }}
void wr() {}
template<typename T1, typename... T2> void wr(T1 x, T2... y) { wr(x), wr(y...); }

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
	return 0;
}