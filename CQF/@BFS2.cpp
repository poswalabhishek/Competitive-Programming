#include<iostream>
#include<string>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
struct State{
};
const int maxh=1<<20;
int u[maxh];
State ht[maxh],queue[2][maxh/2];
int p[2],q[2],found[2];
int cal(State r){

}
bool same(State a,State b){

}
int hash(State r){
	int i=cal(r);
	while(u[i]&&!same(r,ht[i]))
		i=(i+1)&(maxh-1);
	ht[i]=r;
	return i;
}
void add(State s,int tag){
	int w=hash(s);
	if(u[w]==0||(tag*2-1)*u[w]<0){
		queue[tag][++q[tag]]=s;
		if(u[w]){
			found[tag]=q[tag];
			found[1-tag]=abs(u[w]);
		}
		else
			u[w]=q[tag]*(tag*2-1);
	}
}
void extend(State r,int tag){

}
void BFS2(State s,State t){
	memset(u,q[0]=q[1]=found[0]=found[1]=0,sizeof(u));
	p[0]=p[1]=1;
	add(s,0);
	add(t,1);
	for(int tag=0;p[0]<=q[0]&&p[1]<=q[1]&&found[0]==0;tag=1-tag)
		for(int k=q[tag];p[tag]<=k&&found[0]==0;p[tag]++)
			extend(queue[tag][p[tag]],tag);
}
int main(){

}
