#include <bits/stdc++.h>
using namespace std;
#define ll long long
random_device rd;
mt19937 gen(rd());
int C[10] = {0,0,0,1,1,1,2,2,1,0};
long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}
double RAND(normal_distribution<> normalDist)
{
    return normalDist(gen);
}
double Randin(double l,double r)
{
    uniform_real_distribution<> uniformDist(l, r);
    return uniformDist(gen);
}
class agent
{
public:
   int step=0;
   double ValueEstimate[7][10][4]={0};

   double alpha;
   double epsilon;
   agent(double a,double b) : alpha(a),epsilon(b) {}
   int action(int u,int v)
   {
      double E = Randin(0,1);
      int a = 0;
      if(E<=epsilon)  a = Rand(0,3);
      else
      {
          for(int i=0;i<4;i++) if(ValueEstimate[u][v][i]>ValueEstimate[u][v][a]) a = i;
      }
     return a;
   }

};
void update(int u,int v,int a,int *U,int *V)
{
   int Z=*V;
   if(a==0) (*U)--;
   if(a==1) (*V)++;
   if(a==2) (*U)++;
   if(a==3) (*V)--;
   (*V)=max(*V,0); *V=min(*V,9);
   (*U) += C[Z];
   (*U)=max(*U,0); *U=min(*U,6);
}
int main()
{
    freopen("a.out","w",stdout);
    ll episode = 300;
    agent A(0.8,0.1);
    for(ll I=1;I<=episode;I++)
    {
        ll u = 3;
        ll v = 0;
        do
        {
          int a = A.action(u,v);
          int R = -1;
          int U=u,V=v;
          update(u,v,a,&U,&V);
          if(U==3&&V==7) R=0;
          double MAX = -1e13;
          for(int i=0;i<4;i++) MAX = max(MAX,A.ValueEstimate[U][V][i]);
          A.ValueEstimate[u][v][a] += A.alpha*(R + MAX - A.ValueEstimate[u][v][a]);
          A.step++;
          A.epsilon = 1.0 / (log(A.step)+100000);
          u=U;
          v=V;
        } while(u!=3||v!=7);
        cout<<A.step<<" ";
        A.step=0;
    }
    return 0;
}
