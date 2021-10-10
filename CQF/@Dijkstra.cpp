#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=100002;
const int maxm=1000002;
const int limit=1000000000;
template<class T>
struct DijkstraHeap{
	int g[maxn],num[maxm*2],next[maxm*2],tt;
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
	T get(
};
int main(){
	return 0;
}
