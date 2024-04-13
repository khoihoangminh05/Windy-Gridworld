#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ii pair<ll,ll>
#define f first
#define s second
ll n,m,i,j,d[7][10],a[7][10];
ii f[7][10];
bool b[7][10];
ll C[10] = {0,0,0,1,1,1,2,2,1,0};
queue<ii> q;
void up(ll a,ll *U,ll *V)
{
   ll Z=*V;
   if(a==0) (*U)--;
   if(a==1) (*V)++;
   if(a==2) (*U)++;
   if(a==3) (*V)--;
   (*V)=max(*V,0ll); *V=min(*V,9ll);
   (*U) += C[Z];
   (*U)=max(*U,0ll); *U=min(*U,6ll);
}
void in(ll u,ll v)
{
    b[u][v]=1;
    if(d[u][v]==0) {cout<<u<<" "<<v<<'\n';return;}
    in(f[u][v].f,f[u][v].s);
    cout<<u<<" "<<v<<'\n';
}
int main()
{
    memset(d,-1,sizeof(d));
    q.push({3,0});d[3][0]=0;a[3][0]=1;
    while(!q.empty())
    {
        ll u = q.front().f;
        ll v = q.front().s;
        q.pop();
        ll U,V;

        for(int i=0;i<4;i++)
        {
            U=u;V=v;
            up(i,&U,&V);
            if(d[U][V]==-1)
            {
                d[U][V]=d[u][v]+1;
                a[U][V]=a[u][v];
                f[U][V]={u,v};
                q.push({U,V});
            } else
            if(d[U][V] == d[u][v]+1) a[U][V] +=a[u][v];
        }
    }
    cout<<"Do dai duong di toi uu: "<<d[3][7]<<'\n';
    cout<<"So duong di toi uu:     "<<a[3][7]<<'\n';
    in(3,7);
    cout<<"--------------------\n";
    for(int i=6;i>=0;i--)
    {
     for(int j=0;j<=9;j++)
     {
        if(i==3&&j==0) cout<<'S'; else
        if(i==3&&j==7) cout<<'G'; else
        {
            cout<<((b[i][j])? '*':'.');
        }

     } cout<<'\n';
    }

    return 0;
}
