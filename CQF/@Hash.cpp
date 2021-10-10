#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
#define HASH int
using namespace std;
const int maxh=1<<20;
bool u[maxh];
int ht[maxh];
template<class T>
int hash2(T r){
	char *s=(char*)&r;
	int i=0,j,len=sizeof(r);
	fr(j,0,len-1)
		i=(i*223+s[j])&(maxh-1);
	while(u[i]&&strncmp(s,(char*)&ht[i],len)!=0)
		i=(i+1)&(maxh-1);
	ht[i]=r;
	return i;
}
int cal(HASH r){
	return r&(maxh-1);
}
bool same(HASH a,HASH b){
	return a==b;
}
int hash(HASH r){
	int i=cal(r);
	while(u[i]&&!same(r,ht[i]))
		i=(i+1)&(maxh-1);
	ht[i]=r;
	return i;
}
int main(){
}
