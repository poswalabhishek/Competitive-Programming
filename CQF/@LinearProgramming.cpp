/*˵����
	����������Ӧ����class����ģ��������������濪���ڴ��RE��������ʱ�ȷ����档
	N[0]����N�е�Ԫ�ظ�����B[0]����B�е�Ԫ�ظ�����
	�����ʽ�����ļ���ΪinputName���ļ��ж���)��
		����������n, m����ʾδ֪����������Լ����������
		������һ��n������ΪĿ�꺯����ϵ����
		Ȼ��m�У�ÿ��m+1��������ʾһ��Լ����ǰm������ϵ�������һ���ǳ����
	�����ʽ�����ļ���ΪoutputName���ļ����������
		����޽⣬ֻ��һ��"Infeasible"��
		�������������ֻ��һ��"Unbounded"��
		���򣬵�һ��Ϊ����Ŀ�꺯��ֵ����������ÿ��δ֪����ֵ��*/
#include <string>
#include<cmath>
#include <iostream>
using namespace std;
const double eps=1e-10;
const int maxn=2002;
const int oo=19890709;
struct LinearProgramming{
	double A[maxn][maxn],tA[maxn][maxn],b[maxn],tb[maxn],c[maxn],tc[maxn],v;
	int N[maxn],B[maxn],n,m;
	void set(){
		for(int i=1; i<=n; i++){
			scanf("%lf", &c[i]);
			c[i]*=m;
		}
		for(int i=1; i<=m; i++){
			for(int j=1; j<=n; j++)
				scanf("%lf", &A[n+i][j]);
			scanf("%lf", &b[n+i]);
		}
	}
	void pivot(int l, int e){
		tb[e] = b[l]/A[l][e];
		tA[e][l] = 1/A[l][e];
		for(int i=1; i<=N[0]; i++)
			if (N[i] != e)
				tA[e][N[i]] = A[l][N[i]]/A[l][e];
		for(int i=1; i<=B[0]; i++){
			tb[B[i]] = b[B[i]]-A[B[i]][e]*tb[e];
			tA[B[i]][l] = -A[B[i]][e]*tA[e][l];
			for(int j=1; j<=N[0]; j++)
				if (N[j] != e)
					tA[B[i]][N[j]] = A[B[i]][N[j]]-tA[e][N[j]]*A[B[i]][e];
		}
		v += tb[e]*c[e];
		tc[l] = -tA[e][l]*c[e];
		for(int i=1; i<=N[0]; i++)
			if (N[i] != e)
				tc[N[i]] = c[N[i]]-tA[e][N[i]]*c[e];
		for(int i=1; i<=N[0]; i++)
			if (N[i] == e) N[i] = l;
		for(int i=1; i<=B[0]; i++)
			if (B[i] == l) B[i] = e;
		for(int i=1; i<=B[0]; i++){
			for(int j=1; j<=N[0]; j++)
				A[B[i]][N[j]] = tA[B[i]][N[j]];
			b[B[i]] = tb[B[i]];
		}
		for(int i=1; i<=N[0]; i++)
			c[N[i]] = tc[N[i]];
	}
	bool opt(){//false stands for unbounded
		while (true){
			int l, e;
			double maxUp = -1;//������0��
			for(int ie=1; ie<=N[0]; ie++){
				int te = N[ie];
				if (c[te] <= eps) continue;//eps or 0
				double delta = oo;
				int tl = maxn;
				for(int i=1; i<=B[0]; i++)
					if (A[B[i]][te] > eps){//eps or 0
						double temp = b[B[i]]/A[B[i]][te];
						if (delta == oo || temp < delta || temp == delta && B[i] < tl){
							delta = temp;
							tl = B[i];
						}
					}
				if (tl == maxn) return false;
				if (delta*c[te] > maxUp){
					maxUp = delta*c[te];
					l = tl;
					e = te;
				}
			}
			if (maxUp == -1) break;
			pivot(l, e);
		}
		return true;
	}
	void delete0(){
		int p;
		for(p=1; p<=B[0]; p++)
			if (B[p] == 0) break;
		if (p <= B[0]) pivot(0, N[1]);
		for(p=1; p<=N[0]; p++)
			if (N[p] == 0) break;
		for(int i=p; i<N[0]; i++)
			N[i] = N[i+1];
		N[0]--;
	}
	bool initialize(){
		N[0] = B[0] = 0;
		for(int i=1; i<=n; i++)
			N[++N[0]] = i;
		for(int i=1; i<=m; i++)
			B[++B[0]] = n+i;
		v = 0;
		int l = B[1];
		for(int i=2; i<=B[0]; i++)
			if (b[B[i]] < b[l])
				l = B[i];
		if (b[l] >= 0) return true;
		double origC[maxn];
		memcpy(origC, c, sizeof(double)*(n+m+1));
		N[++N[0]] = 0;
		for(int i=1; i<=B[0]; i++)
			A[B[i]][0] = -1;
		memset(c, 0, sizeof(double)*(n+m+1));
		c[0] = -1;
		pivot(l, 0);
		opt();//unbounded
		if (v < -eps) return false;//eps
		delete0();
		memcpy(c, origC, sizeof(double)*(n+m+1));
		bool inB[maxn];
		memset(inB, false, sizeof(bool)*(n+m+1));
		for(int i=1; i<=B[0]; i++)
			inB[B[i]] = true;
		for(int i=1; i<=n+m; i++)
			if (inB[i] && c[i] != 0){
				v += c[i]*b[i];
				for(int j=1; j<=N[0]; j++)
					c[N[j]] -= A[i][N[j]]*c[i];
				c[i] = 0;
			}
		return true;
	}
	double get(){
		set();
		if (!initialize()){
			printf("Infeasible\n");
			return 0;
		}
		if (!opt()){
			printf("Unbounded\n");
			return 0;
		}
		return v;
		bool inN[maxn];
		memset(inN, false, sizeof(bool)*(n+m+1));
		for(int i=1; i<=N[0]; i++)
			inN[N[i]] = true;
		for(int i=1; i<=n; i++)
			if (inN[i]) printf("x%d = %lf\n", i, 0.0);
			else printf("x%d = %lf\n", i, b[i]);
	}
};
LinearProgramming g;
int main(){
	while(cin>>g.n>>g.m)
		printf("Nasa can spend %d taka.\n",(int)ceil(g.get()));
}