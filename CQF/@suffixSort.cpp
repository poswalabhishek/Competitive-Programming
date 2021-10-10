#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=200002;
int sa[maxn],rank[maxn],nrank[maxn],nsa[maxn],cnt[maxn],x[maxn],h[maxn];
void suffixSort(int n,int limit){
	int i,k;
	memset(cnt,0,sizeof(cnt));
	fr(i,0,n-1)
		cnt[x[i]]++;
	fr(i,1,limit)
		cnt[i]+=cnt[i-1];
	for(i=n-1;i>=0;i--)
		sa[--cnt[x[i]]]=i;
	rank[sa[0]]=0;
	fr(i,1,n-1)
		rank[sa[i]]=rank[sa[i-1]]+(x[sa[i-1]]!=x[sa[i]]);
	for(k=1;k<n;k*=2){
		fr(i,0,n-1)
			cnt[rank[sa[i]]]=i+1;
		for(i=n-1;i>=0;i--)
			if(sa[i]-k>=0)
				nsa[--cnt[rank[sa[i]-k]]]=sa[i]-k;
		fr(i,n-k,n-1)
			nsa[--cnt[rank[i]]]=i;
		nrank[sa[0]]=0;
		rank[n]=-1;
		fr(i,1,n-1)
			nrank[nsa[i]]=nrank[nsa[i-1]]+(rank[nsa[i]]!=rank[nsa[i-1]]||rank[nsa[i]+k]!=rank[nsa[i-1]+k]);
		memmove(rank,nrank,n*4);
		memmove(sa,nsa,n*4);
	}
}
void setHeight(int n){
	int i,j,k=0;
	fr(i,0,n-1)
		if(rank[i]){
			k=k?k-1:0;
			j=sa[rank[i]-1];
			while(i+k<n&&j+k<n&&x[j+k]==x[i+k])
				k++;
			h[rank[i]]=k;
		}
		else
			h[0]=k=0;
}
int main(){
}