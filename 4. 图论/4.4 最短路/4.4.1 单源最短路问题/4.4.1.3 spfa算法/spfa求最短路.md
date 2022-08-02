
[题目链接](https://www.acwing.com/problem/content/853/)


给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环， **边权可能为负数**。

请你求出 $1$ 号点到 $n$ 号点的最短距离，如果无法从 $1$ 号点走到 $n$ 号点，则输出 `impossible`。

数据保证不存在负权回路。

#### 输入格式

第一行包含整数 $n$ 和 $m$。

接下来 $m$ 行每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

#### 输出格式

输出一个整数，表示 $1$ 号点到 $n$ 号点的最短距离。

如果路径不存在，则输出 `impossible`。

#### 数据范围

$1 \le n,m \le 10^5$,  
图中涉及边长绝对值均不超过 $10000$。

#### 输入样例：

    3 3
    1 2 5
    2 3 -3
    1 3 4
    

#### 输出样例：

    2

##### 与题目要求代码略有差异

```cpp

#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 100010

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int head[MAXN],ed[MAXN],val[MAXN],nex[MAXN],idx;
int dist[MAXN],vis[MAXN];

void add(int x,int y,int z)
{
    ed[idx]=y;
    val[idx]=z;
    nex[idx]=head[x];
    head[x]=idx++;
}

void spfa(int start)
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));//是否在队列中
    dist[start]=0;
    vis[start]=1;
    queue<int> q;
    q.push(start);
    while(q.size()>0)
    {
        int temp=q.front();
        q.pop();
        vis[temp]=0;
        for(int i=head[temp];i!=-1;i=nex[i])//扫描所有出边
        {
            if(dist[ed[i]]>dist[temp]+val[i])
            {
                dist[ed[i]]=dist[temp]+val[i];
                if(vis[ed[i]]==0)
                {
                    q.push(ed[i]);
                    vis[ed[i]]=1;
                }
            }
        }
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        add(x,y,z);
    }
    spfa(1);
    for(int i=1;i<=n;i++)
    {
        if(dist[i]==inf)
            printf("-1\n");
        else printf("%d\n",dist[i]);
    }
    return 0;
}

```

