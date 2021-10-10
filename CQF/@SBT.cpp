#include<iostream>
#include<stdio.h>
#include<map>
#include<algorithm>
#define sz(t) (t==NULL?0:t->s)
#define fr(i,a,b) for(i=a;i<=b;++i)
#define ll long long
using namespace std;
const int maxn=100002;
const int limit=1000000000;
pair<int,int> x[maxn];
bool cmp(pair<int,int> a,pair<int,int> b){
	return a.second<b.second;
}
int n,ca,i;
map<int,int> g;
map<int,int>::iterator it;
ll ans,a,b;
ll sum(ll a,ll b){
	return (a+b)*(b-a+1)/2;
}
int main(){
	cin>>ca;
	while(ca--){
		cin>>n;
		fr(i,1,n)
			scanf("%d%d",&x[i].first,&x[i].second);
		x[0].second=0;
		sort(x+1,x+1+n,cmp);
		g.clear();
		g[0]=0;
		ans=0;
		for(i=n;i>=1;i--){
			g[x[i].first]++;
			left=x[i].second-x[i-1].second;
			while(left>0){
				it=g.lower_bound(limit);
				if(it->first==0)
					break;
				a=it->first;
				b=it->second;
				g.erase(it);
				it=g.lower_bound(limit);
				if(b*(ll)(a-it->first)<=left){
					ans+=b*sum(it->first+1,a);
					g[it->first]+=b;
					left-=b;
				}
				else{
					ll amount=a-left/b;
					ans+=b*sum(amount+1,a)+(left%b)*sum(amount,a);
					g[amount]+=b-left%b;
					if(left%b)
						g[amount]+=left%b;
					left=0;
				}
			}
		}
		cout<<ans<<endl;
	}
}
