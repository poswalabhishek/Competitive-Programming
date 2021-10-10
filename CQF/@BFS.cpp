#include<iostream>
const int maxn=100002;
const int maxm=1000002;
struct BFS{
	int queue[maxn],g[maxn],num[maxm*2],next[maxm*2],depth[maxn],tt;
	void clear(){
		tt=0;
	}
	void add(int a,int b){
		num[++tt]=b;
		next[tt]=g[a];
		g[a]=tt;
		num[++tt]=a;
		next[tt]=g[b];
		g[b]=tt;
	}
	int get(int s,int t,int n){
		int i,p,q;
		memset(depth,255,sizeof(depth));
		for(depth[queue[p=q=0]=s]=0;p<=q&&depth[t]==-1;p++)
			for(i=g[queue[p]];i;i=next[i])
				if(depth[num[i]]==-1)
					depth[queue[++q]=num[i]]=depth[queue[p]]+1;
		return depth[t];
	}
};
int main(){
}
