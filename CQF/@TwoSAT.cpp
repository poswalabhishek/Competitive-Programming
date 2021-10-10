#include<iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 2100;//最大人数 
class SAT{
    private:
        vector<int> g[N];    //原图边连接情况 
        int n, m, h[N], id[N];    //id[]表示原图中每个点都属于哪个强连通分量 
        int cnt, scnt, dfn[N], low[N], cur[N];
        int stack[N], top, est[N], etop;
        vector<int> tree[N];    //有向无环图的边连接情况(新图) 
        vector<int> contain[N];    //新图中每个点都包含原图中的哪些点 
        void dfs(int);
        void tsDfs(int);
        void topologicalSort();
        void colorDfs(int);
        void color();
        void tagAnswer();
        void printAnswer();
        void getOneAnswer();
        void buildGraph();
    public:
        void scR();
        bool build();
        bool judge();
        void solve();
};
/*函数build是对原图初始化(根据实际输入情况做相应的更改)*/
bool SAT::build(){
    if (scanf("%d %d",&n,&m)==EOF)
        return false;
	n*=2;
    for (int i=0;i<n;i++)
        g[i].clear();
    for (int i=0;i<m;i++) {
        int a,b,c,d;
        scanf("%d %d",&a,&b);//a，b是互斥的。a所在组的另一点为c，b所在组的另一点为d。原图中插入边a->d和边b->c。 
		if(a>0){
			a=(a-1)*2;
			c=a+1;
		}
		else{
			c=(-a-1)*2;
			a=c+1;
		}
		if(b>0){
			b=(b-1)*2;
			d=b+1;
		}
		else{
			d=(-b-1)*2;
			b=d+1;
		}
		g[c].push_back(b);
        g[d].push_back(a);
    }
    return true;
}
void SAT::dfs(int src){
    etop = top = 0;
    stack[top++] = src;
    while(top != 0){
        int    c = stack[top-1];
        if(dfn[c] == -1){ 
            h[c] = dfn[c] = low[c] = cnt++; 
            est[etop++] = c; 
        }
        for(; cur[c] >= 0; cur[c]--){
            int no = g[c][cur[c]];
            if(dfn[no] == -1){ 
                stack[top++] = no; 
                break; 
            }
            h[c] <?= low[no];
        }
        if(cur[c] >= 0)
            continue;
        top--; 
        int k;
        if(h[c] != low[c]){ 
            low[c] = h[c]; 
            continue; 
        }
        do{
            k = est[--etop];
            id[k] = scnt; low[k] = N;
        }while(k != c);
        scnt++;
    }
}
/*函数scR和dfs是求原图的强连通分量*/
void SAT::scR(){
    memset(dfn, -1, sizeof(dfn));
    cnt = scnt = 0;
    for(int i = 0; i < n; i++){ 
        cur[i] = g[i].size()-1;
        contain[i].clear();
    }
    for(int i = 0; i < n; i++)
        if(dfn[i] == -1) 
            dfs(i);
    /*统计每个强连通分量都包含哪些点，为后面求可行方案做准备。如果不求可行解，可注释掉。*/
    for (int i=0;i<n;i++)
        contain[id[i]].push_back(i);
}
/*函数judge判断是否能找出一个可行方案出来*/
bool SAT::judge(){
    for (int i=0;i<n;i+=2)
        if (id[i]==id[i+1])
            return false;
    return true;
}
/*函数buildGraph把每个强连通分量作为一个点，重新构图。(缩点，得到的是一个有向无环图) 
用的是链接表的形式，可能有很多重边。可以加一些预处理消除重边。s*/
void SAT::buildGraph(){
    for (int i=0;i<scnt;i++)
        tree[i].clear();
    for (int i=0;i<n;i++)
        for (int j=0;j<g[i].size();j++){
            int a=id[i];
            int b=id[g[i][j]];
            if (a!=b)
                tree[b].push_back(a);
        }
}
void SAT::tsDfs(int k){
    dfn[k]=cnt++;
    for (int i=0;i<tree[k].size();i++){
        int w=tree[k][i];
        if (dfn[w]==-1)
            tsDfs(w);
    }  
    low[scnt++]=k;             
}
/*函数topologicalSort和tsDfs是对新图进行拓扑排序，排序后的结果存在low数组中 */
void SAT::topologicalSort(){
    for (int i=0;i<scnt;i++){
        dfn[i]=-1;
        low[i]=-1;
    }
    int nn=scnt;
    cnt=scnt=0;
    for (int i=0;i<nn;i++)
        if (dfn[i]==-1)
            tsDfs(i);
}
void SAT::colorDfs(int k){
    dfn[k]=2;
    for (int i=0;i<tree[k].size();i++){
        int w=tree[k][i];
        if (dfn[w]==-1)
            colorDfs(w);
    }          
}
/*函数color和colorDfs是对新图进行着色，新图中着色为1的点组成一组可行解*/ 
void SAT::color(){
    for (int i=0;i<scnt;i++)
        dfn[i]=-1; 
    for (int i=scnt-1;i>=0;i--)
        if (dfn[low[i]]==-1){
            /*新图中low[i]着色为1后，它的矛盾点应标记为2*/
            int a=contain[low[i]][0];//在原图中找一点属于强连通分量low[i]的点a，点a所属组的另一点b所属的强连通分量id[b]一定是low[i]矛盾点。 
            int b;
            if (a%2==0)
                b=a+1;
            else
                b=a-1;
            dfn[low[i]]=1;
            if (dfn[id[b]]==-1)
                colorDfs(id[b]); //由于依赖关系，有id[b]能达的点都是low[i]的矛盾点 
        }
}
/*函数tagAnswer由新图对原图的点进行标记，得到原图的可行解*/
void SAT::tagAnswer(){
    for (int i=0;i<n;i++)
        low[i]=-1;
    for (int i=0;i<scnt;i++)
        if (dfn[i]==1)//i为新图中可行解包含的点，那么原图中强连通分量属于i的点都是原图中可行解的点 
            for (int j=0;j<contain[i].size();j++)
                low[contain[i][j]]=1;
}
/*函数printAnswer打印原图的可行解*/ 
void SAT::printAnswer(){
    for (int i=0,j=0;i<n;i++,j++)
        if (low[i]==1){
            printf("%d",i);
            if (j!=n/2-1)
                printf(" ");
            else
                printf("\n");
        }
}
/*函数getOneAnswer得到原图的一组可行解*/ 
void SAT::getOneAnswer(){
    buildGraph();
    topologicalSort();
    color();
    tagAnswer();
    printAnswer();
}
/*函数solve可根据实际要求，进行更改输出*/ 
void SAT::solve(){
    scR();
    if (judge()){
        printf("1\n");
        getOneAnswer();
    }
    else
        printf("0\n");
}
int main(){
    SAT sat;
    while (sat.build())
        sat.solve();
}
