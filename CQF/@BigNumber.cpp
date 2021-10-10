#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
const int maxsize=5002;
const int base=1000;
using namespace std;
struct BigNumber{
	int x[maxsize],size,i,j;
	BigNumber(int t):size(0){
		memset(x,0,sizeof(x));
		for(;t;t/=base)
			x[size++]=t%base;
	}
	BigNumber():size(0){
		memset(x,0,sizeof(x));
	}
	BigNumber(string s){
		memset(x,0,sizeof(x));
		int j=1,k=0;
		for(i=s.size()-1;i>=0;i--){
			x[k]+=(s[i]-'0')*j;
			j*=10;
			if(j>=base){
				j=1;
				k++;
			}
		}
		resize(k+1);
	}
	void print(){
		int i=size?size-1:0;
		printf("%d",x[i]);
		while(i--){
			for(j=10;j*x[i]<base&&j<base;j*=10)
				printf("0");
			printf("%d",x[i]);
		}
	}
	BigNumber operator+(BigNumber r){
		if(r.size<size)
			r.size=size;
		fr(i,0,r.size-1){
			r.x[i]+=x[i];
			if(r.x[i]>=base){
				r.x[i]-=base;
				r.x[i+1]++;
			}
		}
		r.resize(r.size+1);
		return r;
	}
	BigNumber operator-(BigNumber r){
		BigNumber tmp;
		fr(i,0,size-1){
			tmp.x[i]+=x[i]-r.x[i];
			if(tmp.x[i]<0){
				tmp.x[i]+=base;
				tmp.x[i+1]--;
			}
		}
		tmp.resize(size);
		return tmp;
	}
	BigNumber operator*(int r){
		int i=0,k=0;
		BigNumber tmp;
		while(i<size||k){
			k+=x[i]*r;
			tmp.x[i++]=k%base;
			k/=base;
		}
		tmp.size=i;
		return tmp;
	}
	BigNumber operator*(BigNumber r){
		BigNumber tmp;
		fr(i,0,size-1)
			fr(j,0,r.size-1)
				tmp.x[i+j]+=x[i]*r.x[j];
		fr(i,0,r.size+size-1){
			tmp.x[i+1]+=tmp.x[i]/base;
			tmp.x[i]%=base;
		}
		tmp.resize(r.size+size);
		return tmp;
	}
	BigNumber operator/(int r){
		int i,k=0;
		BigNumber tmp;
		for(i=size-1;i>=0;i--){
			k=k*base+x[i];
			tmp.x[i]=k/r;
			k%=r;
		}
		tmp.resize(size);
		return tmp;
	}
	BigNumber operator/(BigNumber r){
		int i,j,k,key,temp,len=r.size,para=len<10?len:10;
		double a=r.toDouble(len-1,para)-1e-8,b;
		BigNumber ans,tmp=*this;
		for(i=size-len;i>=0;i--){
			key=int(toDouble(i+len,para)*base/a);
			if(key)
				fr(j,0,len-1){
					x[i+j]-=r.x[j]*key;
					x[i+j+1]-=temp=(base-1-x[i+j])/base;
					x[i+j]+=temp*base;
				}
			do{
				for(k=len;k>=0;k--)
					if(x[k+i]!=r.x[k])
						break;
				if(k>=0&&x[k+i]<r.x[k])
					break;
				key++;
				fr(j,0,len-1){
					x[i+j]-=r.x[j];
					if(x[i+j]<0){
						x[i+j]+=base;
						x[i+j+1]--;
					}
				}
			}while(true);
			ans.x[i]=key;
		}
		memmove(x,tmp.x,sizeof(x));
		ans.resize(size);
		return ans;
	}
	void resize(int r){
		size=r;
		while(size&&x[size-1]==0)
			size--;
	}
	bool operator==(BigNumber r){
		if(r.size!=size)
			return false;
		fr(i,0,size-1)
			if(r.x[i]!=x[i])
				return false;
		return true;
	}
	bool operator>(BigNumber r){
		if(r.size!=size)
			return size>r.size;
		for(i=size-1;i>=0;i--)
			if(r.x[i]!=x[i])
				return x[i]>r.x[i];
		return false;
	}
	double toDouble(int a,int limit){
		double ans=0,value=1;
		int i;
		for(i=a;i>=0&&i>a-limit;i--,value/=base)
			ans+=value*x[i];
		return ans;
	}
};
struct BigInteger{
	int sign;
	BigNumber v;
	BigInteger(int r):sign((r>=0)*2-1),v(abs(r)){}
	BigInteger operator+(BigInteger r){
		if(r.sign==sign)
			r.v=r.v+v;
		else
			if(r.v>v)
				r.v=r.v-v;
			else{
				r.v=v-r.v;
				r.sign=sign;
			}
		return r;
	}
	BigInteger operator-(BigInteger r){
		r.sign=-r.sign;
		return operator+(r);
	}
	BigInteger operator*(BigInteger r){
		r.sign*=sign;
		r.v=v*r.v;
		return r;
	}
	BigInteger operator/(BigInteger r){
		r.sign*=sign;
		r.v=v/r.v;
		return r;
	}
	void print(){
		if(sign<0&&v.size)
			printf("-");
		v.print();
	}
};
int main(){
}
