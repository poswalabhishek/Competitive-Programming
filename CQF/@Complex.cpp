#include<iostream>
#define fr(i,a,b) for(i=a;i<=b;i++)
using namespace std;
template<class T>
struct Complex{
	T a,b;
	Complex(T x,T y=0):a(x),b(y){}
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
int main(){
}
