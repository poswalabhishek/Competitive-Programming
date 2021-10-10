#include<iostream>
#include<cmath>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=1<<20;
template<class T>
struct Complex{
	T a,b;
	Complex(T x=0,T y=0):a(x),b(y){}
	Complex operator+(Complex r){
		return Complex(a+r.a,b+r.b);
	}
	Complex operator-(Complex r){
		return Complex(a-r.a,b-r.b);
	}
	Complex operator*(Complex r){
		return Complex(a*r.a-b*r.b,a*r.b+b*r.a);
	}
};
typedef Complex<double> Cb;
void transform(Cb *a,Cb *y,int k,int ty){
	int i,j,where,m,tmp,st;
	fr(i,0,(1<<k)-1){
		where=0;
		fr(j,0,k-1)
			where=where*2+((i>>j)&1);
		y[where]=a[i]*(ty==1?1:1.0/(1<<k));
	}
	fr(i,1,k){
		m=1<<i;
		Cb wm=Cb(cos(ty*2*acos(-1)/m),sin(ty*2*acos(-1)/m));
		for(st=0;st<(1<<k);st+=m){
			Cb w=1;
			fr(j,0,(m>>1)-1){
				Cb t=w*y[st+j+(m>>1)],u=y[st+j];
				y[st+j]=u+t;
				y[st+j+(m>>1)]=u-t;
				w=w*wm;
			}
		}
	}
}
void FFT(Cb *a,int n,Cb *b,int m,Cb *c,int &k){
	for(k=0;(1<<k)<n+m;k++);
	transform(a,c,k,1);
	transform(b,a,k,1);
	for(int i=0;i<(1<<k);i++)
		a[i]=a[i]*c[i];
	transform(a,c,k,-1);
}
int main(){
}