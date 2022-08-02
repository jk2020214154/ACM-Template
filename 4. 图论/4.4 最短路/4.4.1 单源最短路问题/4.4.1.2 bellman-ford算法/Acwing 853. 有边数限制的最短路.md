[题目链接](https://www.acwing.com/problem/content/855/)



给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环， **边权可能为负数**。

请你求出从 $1$ 号点到 $n$ 号点的最多经过 $k$ 条边的最短距离，如果无法从 $1$ 号点走到 $n$ 号点，输出 `impossible`。

注意：图中可能 **存在负权回路** 。

#### 输入格式

第一行包含三个整数 $n,m,k$。

接下来 $m$ 行，每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

点的编号为 $1 \sim n$。

#### 输出格式

输出一个整数，表示从 $1$ 号点到 $n$ 号点的最多经过 $k$ 条边的最短距离。

如果不存在满足条件的路径，则输出 `impossible`。

#### 数据范围

$1 \le n,k \le 500$,  
$1 \le m \le 10000$,  
$1 \le x,y \le n$，  
任意边长的绝对值不超过 $10000$。

#### 输入样例：

    3 3 1
    1 2 1
    2 3 1
    1 3 3
    

#### 输出样例：

    3

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 510
#define MAXM 100010

using namespace std;

const int inf=0x3f3f3f3f;

struct node{
    int a;
    int b;
    int val;
}edge[MAXM];

int n,m,k;
int dis[MAXN],last[MAXN];


void bellman_ford()
{
    memset(dis,0x3f,sizeof(dis));
    
    dis[1]=0;
    for(int i=1;i<=k;i++)
    {
        memcpy(last,dis,sizeof(last));
        for(int j=1;j<=m;j++)
            dis[edge[j].b]=min(dis[edge[j].b],last[edge[j].a]+edge[j].val);
    }
}

int main()
{
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++)
        cin >> edge[i].a >> edge[i].b >> edge[i].val;
    bellman_ford();
    if(dis[n]>inf/2)
        printf("impossible\n");
    else printf("%d\n",dis[n]);
    return 0;
}

```