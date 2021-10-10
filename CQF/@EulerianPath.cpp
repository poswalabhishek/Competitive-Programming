#include<iostream>
#include<vector>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=100002;
const int maxm=1000002;
const int mm=maxm*2+1;
struct EulerianPath1{
	int a,b,next[maxm],num[maxm],g[maxn],tt,in[maxn],out[maxn];
	bool used[mm],u[maxn];
	vector<int> ans;
	EulerianPath1(){
		clear();
	}
	void clear(){
		memset(g,tt=0,sizeof(g));
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
	}
	void add(int a,int b){
		out[a]++;
		in[b]++;
		num[++tt]=b;
		next[tt]=g[a];
		g[a]=tt;
	}
	void dfs(int r){
		u[r]=true;
		for(int i=g[r];i;i=next[i]){
			if(used[abs(i)])
				continue;
			used[abs(i)]=true;
			dfs(num[i]);
		}
		ans.push_back(r);
	}
	vector<int> get(int a,int b){
		int i,st,tot=0;
		fr(st,a,b)
			if(in[i]+out[i])
				break;
		ans.clear();
		fr(i,a,b){
			tot+=abs(in[i]-out[i]);
			if(out[i]>in[i])
				st=i;
			if(tot>2)
				return ans;
		}
		memset(u,0,sizeof(u));
		memset(used,0,sizeof(used));
		dfs(st);
		fr(i,a,b)
			if(!u[i])
				ans.clear();
		return ans;
	}
};
struct EulerianPath2{
	int a,b,buf0[mm],buf1[mm],*next,*num,g[maxn],tt,dv[maxn];
	bool used[mm],u[maxn];
	vector<int> ans;
	EulerianPath2():next(buf0+maxm),num(buf1+maxm){
		clear();
	}
	void clear(){
		memset(g,tt=0,sizeof(g));
		memset(dv,0,sizeof(dv));
	}
	void add(int a,int b){
		dv[a]++;
		dv[b]++;
		num[++tt]=b;
		next[tt]=g[a];
		g[a]=tt;
		num[-tt]=a;
		next[-tt]=g[b];
		g[b]=-tt;
	}
	void dfs(int r){
		u[r]=true;
		for(int i=g[r];i;i=next[i]){
			if(used[abs(i)])
				continue;
			used[abs(i)]=true;
			dfs(num[i]);
		}
		ans.push_back(r);
	}
	vector<int> get(int a,int b){
		int i,st=a,tot=0;
		ans.clear();
		fr(i,a,b){
			tot+=dv[i]&1;
			if(dv[i])
				st=i;
			if(tot>2)
				return ans;
		}
		memset(u,0,sizeof(u));
		memset(used,0,sizeof(used));
		dfs(st);
		fr(i,a,b)
			if(!u[i])
				ans.clear();
		return ans;
	}
};
int main(){
}
