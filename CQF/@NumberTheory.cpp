#include<iostream>
template<class T>
T extGCD(T a,T b,T &x,T &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	T tmp=extGCD(b,a%b,y,x);
	y-=a/b*x;
	return tmp;
}
template<class T>
T extMod(T a,T b){
	T tmp=a%b;
	return tmp<0?tmp+b:tmp;
}
int main(){
}