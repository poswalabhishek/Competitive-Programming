#include<iostream>
const char MAXCH='z';
const char MINCH='a';
struct Tries{
	Tries **child;
	bool end;
	Tries():end(false){
		child=new Tries*[MAXCH-MINCH+1]-MINCH;
		for(char ch=MINCH;ch<=MAXCH;ch++)
			child[ch]=NULL;
	}
	void add(const char *s){
		if(s[0]){
			if(child[s[0]]==NULL)
				child[s[0]]=new Tries();
			child[s[0]]->add(s+1);
		}
		else
			end=true;
	}
	bool find(const char*s){
		return s[0]?child[s[0]]?child[s[0]]->find(s+1):false:end;
	}
};
int main(){

}