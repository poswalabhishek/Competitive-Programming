#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=100002;
const int maxm=1000002;
const int limit=1000000000;
template<class T>
struct DijkstraHeap{
	int g[maxn],num[maxm*2],next[maxm*2],w[maxn],where[maxn],tt;
	T v[maxm*2],d[maxn];
	DijkstraHeap(){
		clear();
	}
	void clear(){
		memset(g,0,sizeof(g));
		tt=0;
	}
	void add(int a,int b,T c){
		num[++tt]=b;
		v[tt]=c;
		next[tt]=g[a];
		g[a]=tt;
	}
	void add2(int a,int b,T c){
		add(a,b,c);
		add(b,c,a);
	}
	void chg(int a,int b){
		swap(w[a],w[b]);
		where[w[a]]=a;
		where[w[b]]=b;
	}
	void up(int r){
		while(r>1&&d[w[r]]<d[w[r>>1]]){
			chg(r,r>>1);
			r>>=1;
		}
	}
	void down(int r,int l){
		int j=r+r;
		while(j<=l){
			if(j<l&&d[w[j+1]]<d[w[j]])
				j++;
			if(d[w[j]]>=d[w[r]])
				break;
			chg(r,j);
			r=j;
			j=r+r;
		}
	}
	T get(int s,int t,int n){
		int i,k,l=n+1;
		fr(i,0,n)
			d[i]=limit;
		d[s]=0;
		fr(i,0,n)
			where[w[i+1]=i]=i+1;
		up(where[s]);
		while(w[1]!=t&&l){
			k=w[1];
			chg(1,l);
			down(1,--l);
			for(i=g[k];i;i=next[i])
				if(d[k]+v[i]<d[num[i]]){
					d[num[i]]=d[k]+v[i];
					up(where[num[i]]);
				}
		}
		return d[t];
	}
};
int main(){
	return 0;
}
