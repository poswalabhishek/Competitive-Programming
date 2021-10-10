#include<iostream>
#include<cmath>
#define fr(i,a,b) for(i=a;i<=b;i++)
#define block(n) int(log(n)/log(2)/2+1)
using namespace std;
const int maxk=20;
const int maxn=1<<maxk;
struct RMQ{
	int m,d,i,j,k,ind,root,fa[maxn],left[maxn],right[maxn],list[maxn*2+1],where[maxn],depth[maxn],rmq[maxn/maxk+1][maxk],mi[1<<(maxk/2+1)][maxk][maxk];
	void dfs(int r,int deep){
		depth[ind]=deep;
		where[r]=ind;
		list[where[r]=ind++]=r;
		if(left[r]!=-1){
			dfs(left[r],deep+1);
			depth[ind]=deep;
			list[ind++]=r;
		}
		if(right[r]!=-1){
			dfs(right[r],deep+1);
			depth[ind]=deep;
			list[ind++]=r;
		}
	}
	int better(int a,int b){
		return depth[a]<depth[b]?a:b;
	}
	template<class T>
	void build(T *x,int n){
		memset(left,255,n*4);
		memset(right,255,n*4);
		root=0;
		fr(i,1,n-1){
			if(x[i]<=x[root]){
				left[i]=root;
				fa[root]=i;
				root=i;
				continue;
			}
			for(j=i-1;x[j]>x[i];j=fa[j]);
			left[i]=right[j];
			right[j]=i;
		}
		ind=0;
		dfs(root,0);
		d=int(log(ind)/log(2)/2+1);
		fr(i,0,(1<<(d-1))-1){
			list[0]=0;
			fr(j,1,d-1)
				if((i>>(j-1))&1)
					list[i]=list[i-1]+1;
				else
					list[i]=list[i-1]-1;
			fr(j,0,d-1){
				mi[i][j][j]=j;
				fr(k,j+1,d-1)
					mi[i][j][k]=list[k]<list[mi[i][j][k-1]]?k:mi[i][j][k-1];
			}
		}
		m=(ind-1)/d;
		fr(i,0,m)
			rmq[i][0]=i*d;
		fr(i,0,ind-1)
			rmq[i/d][0]=depth[i]<depth[rmq[i/d][0]]?i:rmq[i/d][0];
		for(i=1;(1<<i)<=m;i++)
			fr(j,0,m-(1<<i)+1)
				rmq[j][i]=depth[rmq[j][i-1]]<depth[rmq[j+(1<<(i-1))][i-1]]?rmq[j][i-1]:rmq[j+(1<<(i-1))][i-1];
		fr(i,0,m-1){
			ty[i]=0;
			fr(j,0,d-2)
				ty[i]=ty[i]*2+(depth[i*d+j]<depth[i*d+j+1]);
		}			
	}
	int ask(int a,int b){

	}
	int get(int a,int b){
		a=where[a];
		b=where[b];
		if(a>b)
			swap(a,b);
		int ans,wa=a/d,wb=b/d;
		if(wa==wb)
			return list[wa*d+mi[ty[wa]][a%d][b%d]];
		ans=better(wa*d+mi[ty[wa]][a%d][d-1],wb*d+mi[ty[wb]][0][b%d]);
		if(wa+1==wb)
			return list[ans];
		return list[better(ans,ask(wa+1,wb-1))];
	}
};
int main(){
	std::cout<<"F";
}