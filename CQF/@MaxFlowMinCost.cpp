#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
#define nxt(r) (r==n?0:r+1)
using namespace std;
const int maxn=100002;
const int maxm=1000002;
const int mm=maxm*2+1;
const int limit=1000000000;
const double zero=1e-8;
template<class T1,class T2>
struct MaxFlowMinCost{
	int buf3[mm],buf4[mm],g[maxn],*num,*next,tt,queue[maxn],f[maxn],i,j,k,p,q;
	T1 buf1[mm],buf2[mm],*x,*y;
	T2 buf5[mm],*v,d[maxn];
	bool u[maxn];
	MaxFlowMinCost():x(buf1+maxm),y(buf2+maxm),num(buf3+maxm),next(buf4+maxm),v(buf5+maxm){
		clear();
	}
	void clear(){
		memset(g,tt=0,sizeof(g));
	}
	void add(int a,int b,T1 c,T2 d){
		next[++tt]=g[a];
		next[-tt]=g[b];
		num[g[a]=tt]=b;
		num[g[b]=-tt]=a;
		v[-tt]=-(v[tt]=d);
		x[tt]=c;
		x[-tt]=0;
	}
	void get(int s,int t,int n,T1 &maxflow,T2 &mincost){
		maxflow=mincost=0;
		memset(y-tt,0,(tt*2+1)*sizeof(T1));
		do{
			fr(i,0,n)
				d[i]=limit;
			memset(u,d[s]=0,n+1);
			for(u[queue[p=q=0]=s]=true;nxt(q)!=p;p=nxt(p)){
				u[j=queue[p]]=false;
				for(i=g[j];i;i=next[i])
					if(x[i]-y[i]>zero&&d[k=num[i]]>d[j]+v[i]){
						d[k]=d[j]+v[f[k]=i];
						if(!u[k])
							u[queue[q=nxt(q)]=k]=true;
					}
			}
			if(d[t]<limit){
				T1 mi=limit;
				for(i=t;i!=s;i=num[-f[i]])
					mi=min(mi,x[f[i]]-y[f[i]]);
				for(i=t;i!=s;i=num[-f[i]])
					y[-f[i]]=-(y[f[i]]+=mi);
				mincost+=mi*d[t];
				maxflow+=mi;
			}
		}while(d[t]<limit);
	}
};

int main(){
}
