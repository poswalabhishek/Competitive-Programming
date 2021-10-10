#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
void qsort(int a,int b,int x[]){
	if(a>=b)
		return;
	int i=a,j=b,k=x[(a+b)>>1];
	do{
		while(x[j]>k)
			j--;
		while(x[i]<k)
			i++;
		if(i<=j)
			swap(x[i++],x[j--]);
	}while(i<=j);
	qsort(a,j,x);
	qsort(i,b,x);
}
long long mergeSort(int a,int b,int list[]){
	if(a>=b)
		return 0;
	int m=(a+b)>>1,i=a,j=m+1,k,*tmp=new int[b-a+1]+a;
	long long tot=mergeSort(a,m,list)+mergeSort(m+1,b,list);
	fr(k,a,b)
		if(j>b||i<=m&&list[i]<=list[j]){
			tmp[k]=list[i++];
			tot+=j-m-1;
		}
		else
			tmp[k]=list[j++];
	memmove(list+a,tmp+a,(b-a+1)*sizeof(list[0]));
	delete tmp;
	return tot;
}
int main(){
}