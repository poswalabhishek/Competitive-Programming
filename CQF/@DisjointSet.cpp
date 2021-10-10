#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=1000002;
struct DisjointSet{
	int f[maxn];
	DisjointSet(){
		clear();
	}
	void clear(){
		memset(f,255,sizeof(f));
	}
	void connect(int a,int b){
		int fa=find(a),fb=find(b);
		if(fa!=fb)
			f[fa]=fb;
	}
	bool same(int a,int b){
		return find(a)==find(b);
	}
	int find(int r){
		if(f[r]<0)
			return r;
		return f[r]=find(f[r]);
	}
};
int main(){
}
