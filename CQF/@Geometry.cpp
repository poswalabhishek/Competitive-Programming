#include<iostream>
#include<vector>
#include<cmath>
#include<list>
#define fr(i,a,b) for(i=a;i<=b;i++)
#define x first
#define y second
#define point(a,b) make_pair(a,b)
using namespace std;
typedef pair<double,double> point;
typedef vector<point> polygon;
const double zero=1e-8;
const double limit=1e8;
const double pi=acos(-1);
point operator+(point a,point b){
	return make_pair(a.x+b.x,a.y+b.y);
}
point operator-(point a,point b){
	return make_pair(a.x-b.x,a.y-b.y);
}
point operator*(point a,double b){
	return make_pair(a.x*b,a.y*b);
}
point operator/(point a,double b){
	return make_pair(a.x/b,a.y/b);
}
double area2(point a,point b,point c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
ostream& operator<<(ostream& os,point r){
	os<<r.x<<" "<<r.y<<" ";
	return os;
}
void print(polygon p){
	int i;
	cout<<p.size()<<":";
	fr(i,0,(int)p.size()-1)
		cout<<"("<<p[i].x<<","<<p[i].y<<")";
	cout<<endl;
}
point poi(point a,point b,point c,point d){
	double s1=area2(a,b,c),s2=area2(a,b,d);
	return make_pair((c.x*s2-d.x*s1)/(s2-s1),(c.y*s2-d.y*s1)/(s2-s1));
}
bool onseg(point a,point b,point c){
	return dis(a,c)+dis(b,c)-dis(a,b)<zero;
}
point rotate(point a,point b,double angle){
	return make_pair((b.x-a.x)*cos(angle)-(b.y-a.y)*sin(angle)+a.x,(b.x-a.x)*sin(angle)+(b.y-a.y)*cos(angle)+a.y);
}
bool intersect(point &a,point &b,point &c,point &d){
	return area2(a,b,c)*area2(a,b,d)<-zero&&area2(c,d,a)*area2(c,d,b)<-zero;
}
double newy(point a,point b,double x){
	return (x-a.x)*(b.y-a.y)/(b.x-a.x)+a.y;
}
bool inside(polygon p,point a){
	double angle=rand();
	point b=make_pair(cos(angle)*1e20,sin(angle)*1e20);
	int i,tot=0;
	fr(i,0,(int)p.size()-1)
		if(onseg(p[i],p[(i+1)%p.size()],a))
			return true;
	fr(i,0,(int)p.size()-1)
		tot+=intersect(p[i],p[(i+1)%p.size()],a,b);
	return tot&1;
}
double cal(point a,point b,point c,point d){
	if(a.x>b.x)
		return -cal(b,a,c,d);
	if(c.x>d.x)
		return -cal(a,b,d,c);
	if(min(b.x,d.x)-max(a.x,c.x)<zero)
		return 0;
	a.x<c.x?a=make_pair(c.x,newy(a,b,c.x)):c=make_pair(a.x,newy(c,d,a.x));
	b.x>d.x?b=make_pair(d.x,newy(a,b,d.x)):d=make_pair(b.x,newy(c,d,b.x));
	point e=area2(a,b,c)*area2(a,b,d)>-zero?(a.y<c.y?a:c):poi(a,b,c,d);
	return ((min(a.y,c.y)+e.y)*(e.x-a.x)+(min(b.y,d.y)+e.y)*(b.x-e.x))*0.5;
}
double intersection(polygon a,polygon b){
	int i,j;
	double s=0,tmp;
	fr(i,0,(int)a.size()-1)
		fr(j,0,(int)b.size()-1)
			s+=tmp=cal(a[i],a[(i+1)%a.size()],b[j],b[(j+1)%b.size()]);
	return s;
}
double intersection(point a,point b,polygon p){
	vector<point> list;
	int i,j;
	double sum=0;
	list.push_back(a);
	list.push_back(b);
	fr(i,0,(int)p.size()-1){
		if(onseg(a,b,p[i]))
			list.push_back(p[i]);
		if(intersect(a,b,p[i],p[(i+1)%p.size()]))
			list.push_back(poi(a,b,p[i],p[(i+1)%p.size()]));
	}
	fr(i,1,(int)list.size()-1)
		fr(j,i+1,(int)list.size()-1)
			if(dis(a,list[i])>dis(a,list[j]))
				swap(list[i],list[j]);
	fr(i,0,(int)list.size()-2)
		if(inside(p,make_pair((list[i].x+list[i+1].x)/2,(list[i].y+list[i+1].y)/2)))
			sum+=dis(list[i],list[i+1]);
	return sum;
}
double area(polygon p){
	if(p.size()==0)
		return 0;
	int i,len=p.size();
	double s=p[len-1].x*p[0].y-p[0].x*p[len-1].y;
	fr(i,0,len-2)
		s+=p[i].x*p[i+1].y-p[i+1].x*p[i].y;
	return s*0.5;
}
bool cmp(point a,point b){
	return a.x*b.y-b.x*a.y>0;
}
polygon convexHull(polygon p){
	if(p.size()<3)
		return p;
	int i,m=1,n=0;
	fr(i,1,(int)p.size()-1)
		if(p[i].x<p[0].x||fabs(p[i].x-p[0].x)<zero&&p[i].y<p[0].y)
			swap(p[0],p[i]);
	fr(i,1,(int)p.size()-1)
		if(fabs(p[i].x-p[0].x)+fabs(p[i].y-p[0].y)>zero)
			p[++n]=make_pair(p[i].x-p[0].x,p[i].y-p[0].y);
	sort(p.begin()+1,p.begin()+n+1,cmp);
	fr(i,1,n)
		p[i]=make_pair(p[i].x+p[0].x,p[i].y+p[0].y);
	fr(i,2,n){
		if(onseg(p[m-1],p[m],p[i]))
			continue;
		while(m&&area2(p[m-1],p[m],p[i])<zero)
			m--;
		p[++m]=p[i];
	}
	p.resize(m+1);
	return p;
}
#define lp list<point>
vector<double> slope;
bool cmp2(int a,int b){
	return slope[a]<slope[b];
}
lp::iterator next(lp::iterator now,lp &p){
	return ++now==p.end()?p.begin():now;
}
lp::iterator back(lp::iterator now,lp &p){
	return now==p.begin()?--p.end():--now;
}
polygon halfPlaneIntersection(point *a,point *b,int n){
	lp p;
	polygon ans;
	vector<int> w;
	int i,j;
	slope.clear();
	fr(i,0,n-1){
		slope.push_back(atan2(b[i].y-a[i].y,b[i].x-a[i].x));
		w.push_back(i);
	}
	sort(w.begin(),w.end(),cmp2);
	p.push_back(make_pair(-limit,-limit));
	p.push_back(make_pair(limit,-limit));
	p.push_back(make_pair(limit,limit));
	p.push_back(make_pair(-limit,limit));
	lp::iterator now=p.begin(),i0,i1,tmp;
	fr(i,0,n-1){
		point c=a[w[i]],d=b[w[i]];
		while(area2(c,d,*now)>area2(c,d,*next(now,p)))
			now=next(now,p);
		while(area2(c,d,*now)>area2(c,d,*back(now,p)))
			now=back(now,p);
		if(area2(c,d,*now)>-zero)
			continue;
		i0=i1=now;
		while(area2(c,d,*back(i0,p))<zero){
			i0=back(i0,p);
			if(i0==now)
				return ans;
		}
		while(area2(c,d,*next(i1,p))<zero)
			i1=next(i1,p);
		p.insert(i0,poi(*i0,*back(i0,p),c,d));
		*i1=poi(*i1,*next(i1,p),c,d);
		for(now=i0;now!=i1;now=tmp){
			tmp=next(now,p);
			p.erase(now);
		}
	}
	for(now=p.begin();now!=p.end();now++)
		ans.push_back(*now);
	return ans;
}
void midperpendicular(point a,point b,point &c,point &d){
	c=(a+b)/2;
	d=point(-(b.y-c.y),b.x-c.x)+c;
}
point circleCenter(point a,point b,point c){
	point ab0,ab1,ac0,ac1;
	midperpendicular(a,b,ab0,ab1);
	midperpendicular(a,c,ac0,ac1);
	return poi(ab0,ab1,ac0,ac1);
}
int main(){
}
