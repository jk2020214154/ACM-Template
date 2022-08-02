
[题目链接](https://www.acwing.com/problem/content/851/)


给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环，所有边权均为正值。

请你求出 $1$ 号点到 $n$ 号点的最短距离，如果无法从 $1$ 号点走到 $n$ 号点，则输出 $-1$。

#### 输入格式

第一行包含整数 $n$ 和 $m$。

接下来 $m$ 行每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

#### 输出格式

输出一个整数，表示 $1$ 号点到 $n$ 号点的最短距离。

如果路径不存在，则输出 $-1$。

#### 数据范围

$1 \le n \le 500$,  
$1 \le m \le 10^5$,  
图中涉及边长均不超过10000。

#### 输入样例：

    3 3
    1 2 2
    2 3 1
    1 3 4
    

#### 输出样例：

    3



#### Dijkstra算法朴素版(与**题目结果略有差异**)


```cpp

//朴素版Dijkstra算法
#include<iostream>
#include<cstring>
#include<algorithm>

#define MAXN 3010

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int dist[MAXN],vis[MAXN];
int g[MAXN][MAXN];//用邻接矩阵存图

void dijkstra(int start)
{
    memset(dist,0x3f,sizeof(dist));//将dist数组置为无穷大
    memset(vis,0,sizeof(vis));//将标记数组vis清零
    dist[start]=0;
    for(int i=1;i<=n-1;i++)//重复进行n-1次
    {
        int pos=-1;//找到未标记结点中dist最小的
        for(int j=1;j<=n;j++)
            if(vis[j]==0&&(pos==-1||dist[j]<dist[pos]))
                pos=j;
        vis[pos]=1;
        //用全局最小值点pos更新其他结点
        for(int j=1;j<=n;j++)
            dist[j]=min(dist[j],dist[pos]+g[pos][j]);
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    memset(g,0x3f,sizeof(g));//将邻接矩阵置为无穷大
    for(int i=1;i<=n;i++)
        g[i][i]=0;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        g[x][y]=min(g[x][y],z);//由于存在重边,需更新为该边的最小值
    }
    dijkstra(1);//求单源最短路径
    for(int i=1;i<=n;i++)
    {
        if(dist[i]==inf)//该点无法从起点start到达
            printf("-1\n");
        else printf("%d\n",dist[i]);
    }
    return 0;
}

```