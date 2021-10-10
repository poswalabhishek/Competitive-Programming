#include<iostream>
#include<vector>
#include<string>
#include<queue>
#define fr(i,a,b) for(i=a;i<=b;i++)
#define outputType int
#define vs vector<State*>
using namespace std;
struct Node{
	int cal(){
	}
};
struct State{
	int depth,key;
	Node s;
	State(Node &S,int D=0):s(S),depth(D),key(D+S.cal()){}
};
struct cmp{
	bool operator()(const State*a,const State*b){
		return a->key>b->key;
	}
};
vs expand(State *p){
	vs list;
	return list;
}
bool isFinal(State *p){
	return p->depth==p->key;
}
outputType output(State *p){

}
const int maxh=1<<23;
bool u[maxh];
Node ht[maxh];
priority_queue<State*,vs,cmp> heap;
State *ans;
int l;
int hash(Node r){
	char *s=(char*)&r;
	int i=0,j,len=sizeof(r);
	fr(j,0,len-1)
		i=(i*223+s[j])&(maxh-1);
	while(u[i]&&strncmp(s,(char*)&ht[i],len)!=0)
		i=(i+1)&(maxh-1);
	ht[i]=r;
	return i;
}
void add(State *p){
	int w=hash(p->s);
	if(u[w]){
		delete p;
		return;
	}
	u[w]=true;
	if(isFinal(p))
		ans=p;
	heap.push(p);
}
outputType get(Node st){
	memset(u,l=0,sizeof(u));
	while(!heap.empty())
		heap.pop();
	ans=NULL;
	add(new State(st));
	while(ans==NULL&&!heap.empty()){
		vs tmp=expand(heap.top());
		for(int i=0;i<tmp.size();i++)
			add(tmp[i]);
		delete(heap.top());
		heap.pop();
	}
	if(ans!=NULL)
		return output(ans);
}
int main(){
}
