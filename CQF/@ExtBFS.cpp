#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
struct State{

};
const int maxh=1<<20;
bool u[maxh];
State ht[maxh],queue[maxh/2];
int p,q,found;
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
bool isFinal(State s){

}
void add(State s){
	int w=hash(s);
	if(u[w])
		return;
	u[w]=true;
	queue[++q]=s;
	if(isFinal(s))
		found=q;
}
void extend(State s){

}
int BFS(State s){
	memset(u,found=q=0,sizeof(u));
	p=1;
	for(add(s);p<=q&&found==0;p++)
		extend(queue[p]);
	return found;
}
int main(){
}
