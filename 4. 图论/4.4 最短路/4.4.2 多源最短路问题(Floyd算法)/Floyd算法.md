

#### 核心代码

```cpp
int dist[MAXN][MAXN];

void floyd(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}
```

[题目链接](https://www.acwing.com/problem/content/856/)


给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环，边权可能为负数。

再给定 $k$ 个询问，每个询问包含两个整数 $x$ 和 $y$，表示查询从点 $x$ 到点 $y$ 的最短距离，如果路径不存在，则输出 `impossible`。

数据保证图中不存在负权回路。

#### 输入格式

第一行包含三个整数 $n,m,k$。

接下来 $m$ 行，每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

接下来 $k$ 行，每行包含两个整数 $x,y$，表示询问点 $x$ 到点 $y$ 的最短距离。

#### 输出格式

共 $k$ 行，每行输出一个整数，表示询问的结果，若询问两点间不存在路径，则输出 `impossible`。

#### 数据范围

$1 \le n \le 200$,  
$1 \le k \le n^2$  
$1 \le m \le 20000$,  
图中涉及边长绝对值均不超过 $10000$。

#### 输入样例：

    3 3 2
    1 2 1
    2 3 2
    1 3 1
    2 1
    1 3
    

#### 输出样例：

    impossible
    1

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 210
#define MAXM 20010

using namespace std;

const int inf=0x3f3f3f3f;

int n,m,k;
int dist[MAXN][MAXN];

void floyd()
{
    for(int k=n;k>=1;k--)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}

int main()
{
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i==j)
                dist[i][j]=0;
            else dist[i][j]=inf;
    
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        dist[a][b]=min(dist[a][b],c);
    }
    
    floyd();
    
    for(int i=1;i<=k;i++)
    {
        int a,b;
        cin >> a >> b;
        if(dist[a][b]>inf/2)
            printf("impossible\n");
        else printf("%d\n",dist[a][b]);
    }
    
    return 0;
}

```