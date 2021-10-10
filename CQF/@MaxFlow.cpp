#include<iostream>
using namespace std;
const int maxn=100002;
const int maxm=1000002;
const int mm=maxm*2+1;
const int limit=1000000000;
const double zero=1e-8;
template<class T>
struct MaxFlow{
	int buf3[mm],buf4[mm],g[maxn],la[maxn],*num,*next,tt;
	T buf1[mm],buf2[mm],*x,*y,rec,sum,u[maxn];
	MaxFlow():x(buf1+maxm),y(buf2+maxm),num(buf3+maxm),next(buf4+maxm){
		clear();
	}
	void clear(){
		memset(g,tt=0,sizeof(g));
	}
	void add(int a,int b,T c){
		next[++tt]=g[a];
		next[-tt]=g[b];
		num[g[a]=tt]=b;
		num[g[b]=-tt]=a;
		x[tt]=c;
		x[-tt]=0;//x[-tt]=-c if undirected
	}
	bool dfs(int r,int t,T mi){
		if(r==t){
			rec=mi;
			return true;
		}
		u[r]=sum;
		int i=la[r];
		do{
			if(x[i]-y[i]>zero&&u[num[i]]!=sum&&dfs(num[i],t,min(mi,x[i]-y[i]))){
				y[-i]=-(y[la[r]=i]+=rec);
				return true;
			}
			i=(next[i]?next[i]:g[r]);
		}while(i!=la[r]);
		return false;
	}
	T get(int s,int t){
		memset(u,255,sizeof(u));
		memmove(la,g,sizeof(g));
		memset(y-tt,0,(tt*2+1)*sizeof(T));
		sum=0;
		while(dfs(s,t,limit))
			sum+=rec;
		return sum;
	}
};
MaxFlow<int> g;
int main(){

}
