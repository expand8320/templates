#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <cmath>
#define endl '\n'
using namespace std;
using pdd=pair<double, double>;
using pii=pair<int, int>;

mt19937 rngint(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> rngd(0.0l, 1.0l);
const int MN=3e4+13;
string T;
int N, M;
pdd A[MN]; pii cap[MN];
double MX;

int cnt[MN], optarg[MN]; double optdist[MN];
pii cpy[MN];
vector<pdd> cur, ans;
int cur_cost, ans_cost;
int changed[MN], old_optarg[MN]; double old_optdist[MN]; int sz;

inline double dist(const pdd &x, const pdd &y)
{
    return (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second);
}
int get(const vector<pdd> &vec)
{
    for (int i=1; i<=M; i++) cnt[i]=0;
    for (int i=1; i<=N; i++)
    {
        optarg[i]=1; optdist[i]=dist(A[i], vec[1]);
        for (int j=2; j<=M; j++)
        {
            double val=dist(A[i], vec[j]);
            if (optdist[i]>val)
            {
                optdist[i]=val;
                optarg[i]=j;
            }
        }
        cnt[optarg[i]]++;
    }
    for (int i=1; i<=M; i++) cpy[i]={cnt[i], i};
    sort(cpy+1, cpy+1+M);
    int z=0;
    for (int i=1; i<=M; i++) z+=min(cap[i].first, cpy[i].first);
    return z;
}
int rnd(const int &strong)
{
    for (int iter=0; iter<100; iter++)
    {
        int id=rngint()%N+1;
        if (optarg[id]==strong) return id;
    }
    return rngint()%N+1;
}
int far(const int &strong)
{
    int arg=0; double opt=-1;
    for (int iter=0; iter<100; iter++)
    {
        int id=rngint()%N+1;
        if (optarg[id]!=strong) continue;
        double val=dist(A[id], cur[strong]);
        if (opt<val)
        {
            opt=val;
            arg=id;
        }
    }
    if (arg) return arg;
    else return rngint()%N+1;
}
int under()
{
    int arg=cpy[1].second, opt=cap[1].first-cpy[1].first;
    int k=min(M, 30);
    for (int iter=0; iter<k; iter++)
    {
        int pos=rngint()%k+1;
        int val=cap[pos].first-cpy[pos].first;
        if (opt<val)
        {
            opt=val;
            arg=cpy[pos].second;
        }
    }
    return arg;
}
int over()
{
    int arg=cpy[M].second, opt=cpy[M].first-cap[M].first;
    int k=min(M, 30);
    for (int iter=0; iter<k; iter++)
    {
        int pos=M-rngint()%k;
        int val=cpy[pos].first-cap[pos].first;
        if (opt<val)
        {
            opt=val;
            arg=cpy[pos].second;
        }
    }
    return arg;
}
void print()
{
    pair<int, pdd> tmp[MN];
    for (int i=1; i<=M; i++) tmp[i]={0, ans[i]};
    for (int i=1; i<=N; i++)
    {
        int arg=1; double opt=dist(A[i], ans[1]);
        for (int j=2; j<=M; j++)
        {
            double val=dist(A[i], ans[j]);
            if (opt>val)
            {
                opt=val;
                arg=j;
            }
        }
        tmp[arg].first++;
    }
    sort(tmp+1, tmp+1+M);
    int z=0;
    vector<pdd> vec(M+1);
    for (int i=1; i<=M; i++)
    {
        z+=min(cap[i].first, tmp[i].first);
        vec[cap[i].second]=tmp[i].second;
    }
    assert(z==ans_cost);
    
    string out=T+'/'+to_string(ans_cost)+'_'+to_string(rngint())+".txt";
    ofstream fout(out); assert(fout);
    fout<<M<<endl;
    for (int i=1; i<=M; i++)
    {
        fout<<fixed<<setprecision(8);
        fout<<vec[i].first<<' '<<vec[i].second<<endl;
    }
    cerr<<ans_cost<<endl;
}

void driver(ifstream &fin)
{
    cerr<<"AT "<<T<<endl;
    fin>>N>>M;
    for (int i=1; i<=N; i++) fin>>A[i].first>>A[i].second;
    for (int i=1; i<=M; i++)
    {
        fin>>cap[i].first;
        cap[i].second=i;
    }
    sort(cap+1, cap+1+M);
    
    cur.resize(M+1);
    for (int i=1; i<=M; i++)
    {
        if (rngd(rngint)<0.5) cur[i]={rngd(rngint)*MX, rngd(rngint)*MX};
        else cur[i]=A[rngint()%N+1];
    }
    cur_cost=get(cur);
    ans=cur;
    ans_cost=cur_cost;
    
    int restarts=20;
    while (restarts--)
    {
        for (int i=1; i<=M; i++)
        {
            if (rngd(rngint)<0.8) cur[i]=ans[i];
            else cur[i]={rngd(rngint)*MX, rngd(rngint)*MX};
        }
        cur_cost=get(cur);
        if (ans_cost<cur_cost)
        {
            ans=cur;
            ans_cost=cur_cost;
        }
        
        auto t0=chrono::steady_clock::now();
        auto elap=[&]()
        {
            auto t=chrono::steady_clock::now();
            return chrono::duration<double>(t-t0).count();
        };
        
        const double tl=300;
        const double T0=10, Tf=0.0001;
        double T=T0;
        for (int iter=0; ; iter++)
        {
            if (ans_cost==N)
            {
                cerr<<"FINAL: "<<ans_cost<<endl;
                print();
                return;
            }
            
            if (!(iter&1023))
            {
                double t=elap();
                if (t>tl) break;
                T=T0*pow(Tf/T0, t/tl);
            }
            if (!(iter&((1<<15)-1))) cerr<<ans_cost<<endl;
            
            int pos; pdd old;
            if (M>1 && rngd(rngint)<0.25)
            {
                int k=min(M, 10);
                int st=under(), te=over();
                if (st==te)
                {
                    te=cpy[M].second;
                    if (st==te) st=cpy[1].second;
                }
                pos=st; old=cur[pos];
                int id;
                if (rngint()&1) id=far(te);
                else id=rnd(te);
                double step=MX*sqrt(T/T0)/5;
                cur[pos].first=A[id].first+(rngd(rngint)*2-1)*step;
                cur[pos].second=A[id].second+(rngd(rngint)*2-1)*step;
                cur[pos].first=max(cur[pos].first, 0.0);
                cur[pos].first=min(cur[pos].first, MX);
                cur[pos].second=max(cur[pos].second, 0.0);
                cur[pos].second=min(cur[pos].second, MX);
            }
            else
            {
                if (rngd(rngint)<0.1)
                {
                    if (rngd(rngint)<0.01) pos=over();
                    else pos=under();
                }
                else pos=rngint()%M+1;
                
                old=cur[pos];
                if (rngd(rngint)<T/500)
                {
                    cur[pos].first=rngd(rngint)*MX;
                    cur[pos].second=rngd(rngint)*MX;
                }
                else if (rngd(rngint)<T/50) cur[pos]=A[rngint()%N+1];
                else
                {
                    double step=MX*sqrt(T/T0);
                    cur[pos].first+=(rngd(rngint)*2-1)*step;
                    cur[pos].second+=(rngd(rngint)*2-1)*step;
                    cur[pos].first=max(cur[pos].first, 0.0);
                    cur[pos].first=min(cur[pos].first, MX);
                    cur[pos].second=max(cur[pos].second, 0.0);
                    cur[pos].second=min(cur[pos].second, MX);
                }
            }
            
            sz=0;
            for (int i=1; i<=N; i++)
            {
                if (optarg[i]!=pos)
                {
                    double val=dist(A[i], cur[pos]);
                    if (optdist[i]>val || (optdist[i]==val && pos<optarg[i]))
                    {
                        sz++;
                        changed[sz]=i;
                        old_optarg[sz]=optarg[i];
                        old_optdist[sz]=optdist[i];
                        
                        optdist[i]=val;
                        cnt[optarg[i]]--;
                        optarg[i]=pos;
                        cnt[optarg[i]]++;
                    }
                }
                else
                {
                    sz++;
                    changed[sz]=i;
                    old_optarg[sz]=optarg[i];
                    old_optdist[sz]=optdist[i];
                    
                    cnt[optarg[i]]--;
                    optarg[i]=1; optdist[i]=dist(A[i], cur[1]);
                    for (int j=2; j<=M; j++)
                    {
                        double val=dist(A[i], cur[j]);
                        if (optdist[i]>val)
                        {
                            optdist[i]=val;
                            optarg[i]=j;
                        }
                    }
                    cnt[optarg[i]]++;
                }
            }
            for (int i=1; i<=M; i++) cpy[i]={cnt[i], i};
            sort(cpy+1, cpy+1+M);
            int cost=0;
            for (int i=1; i<=M; i++) cost+=min(cap[i].first, cpy[i].first);
            
            if (cur_cost<cost)
            {
                cur_cost=cost;
                if (ans_cost<cost)
                {
                    ans=cur;
                    ans_cost=cost;
                }
            }
            else
            {
                double x=double(cost-cur_cost)/T;
                if (x>-40.0 && rngd(rngint)<exp(x)) cur_cost=cost;
                else
                {
                    cur[pos]=old;
                    for (int i=1; i<=sz; i++)
                    {
                        cnt[optarg[changed[i]]]--;
                        optarg[changed[i]]=old_optarg[i];
                        optdist[changed[i]]=old_optdist[i];
                        cnt[optarg[changed[i]]]++;
                    }
                }
                for (int i=1; i<=M; i++) cpy[i]={cnt[i], i};
                sort(cpy+1, cpy+1+M);
            }
        }
        print();
    }
    cerr<<"FINAL: "<<ans_cost<<endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<string> vec={"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
    for (string t:vec)
    {
        T=t;
        string in="input/"+T+".in";
        ifstream fin(in); assert(fin);
        if (T=="11") MX=10;
        else if (T=="1" || T=="2") MX=30;
        else if (T=="7" || T=="8") MX=50;
        else if (T=="3" || T=="4") MX=300;
        else MX=1000;
        driver(fin);
    }
    return 0;
}
