
[题目链接](https://www.acwing.com/problem/content/852/)


给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环，所有边权均为非负值。

请你求出 $1$ 号点到 $n$ 号点的最短距离，如果无法从 $1$ 号点走到 $n$ 号点，则输出 $-1$。

#### 输入格式

第一行包含整数 $n$ 和 $m$。

接下来 $m$ 行每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

#### 输出格式

输出一个整数，表示 $1$ 号点到 $n$ 号点的最短距离。

如果路径不存在，则输出 $-1$。

#### 数据范围

$1 \le n,m \le 1.5 \times 10^5$,  
图中涉及边长均不小于 $0$，且不超过 $10000$。  
数据保证：如果最短路存在，则最短路的长度不超过 $10^9$。

#### 输入样例：

    3 3
    1 2 2
    2 3 1
    1 3 4
    

#### 输出样例：

    3



#### Dijkstra算法堆优化版(与**题目结果略有差异**)

##### 小根堆实现
```cpp
//堆优化版Dijkstra（小根堆）+链式前向星
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 150010

using namespace std;

typedef pair<int,int> PII;
const int inf=0x3f3f3f3f;
int n,m;
int dist[MAXN],vis[MAXN];
int head[MAXN],ed[MAXN],nex[MAXN],val[MAXN],idx;

void add(int x,int y,int z)
{
    ed[idx]=y;
    val[idx]=z;
    nex[idx]=head[x];
    head[x]=idx++;
}

void dijkstra(int start)
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[start]=0;
    priority_queue<PII,vector<PII>,greater<PII> >q;
    q.push({0,start});//把起点压入优先队列中
    while(q.size()>0)
    {
        PII temp=q.top();//取出距离起点最近的点
        q.pop();
        int temp_dis=temp.first,temp_pos=temp.second;
        if(vis[temp_pos]==1)
            continue;
        vis[temp_pos]=1;
        for(int i=head[temp_pos];i!=-1;i=nex[i])
        {
            if(vis[ed[i]]==1)
                continue;
            if(dist[ed[i]]>temp_dis+val[i])
            {
                dist[ed[i]]=temp_dis+val[i];
                q.push({dist[ed[i]],ed[i]});
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
        //add(y,x,z);存在无向图,反向加一条边
    }
    dijkstra(1);
    for(int i=1;i<=n;i++)
    {
        if(dist[i]==inf)
            printf("-1\n");
        else printf("%d\n",dist[i]);
    }
    return 0;
}

```

##### 大根堆(负数操作,实现取小操作)实现

```cpp
//堆优化版Dijkstra（用大根堆模拟小根堆,取负数）+链式前向星
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 150010

using namespace std;

typedef pair<int,int> PII;
const int inf=0x3f3f3f3f;
int n,m;
int dist[MAXN],vis[MAXN];
int head[MAXN],ed[MAXN],nex[MAXN],val[MAXN],idx;

void add(int x,int y,int z)
{
    ed[idx]=y;
    val[idx]=z;
    nex[idx]=head[x];
    head[x]=idx++;
}

void dijkstra(int start)
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[start]=0;
    priority_queue<PII> q;
    q.push({0,start});//把起点压入优先队列中
    while(q.size()>0)
    {
        PII temp=q.top();//取出距离起点最近的点
        q.pop();
        int temp_dis=-temp.first,temp_pos=temp.second;
        if(vis[temp_pos]==1)
            continue;
        vis[temp_pos]=1;
        for(int i=head[temp_pos];i!=-1;i=nex[i])
        {
            if(vis[ed[i]]==1)
                continue;
            if(dist[ed[i]]>temp_dis+val[i])
            {
                dist[ed[i]]=temp_dis+val[i];
                q.push({-dist[ed[i]],ed[i]});
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
        //add(y,x,z);存在无向图,反向加一条边
    }
    dijkstra(1);
    for(int i=1;i<=n;i++)
    {
        if(dist[i]==inf)
            printf("-1\n");
        else printf("%d\n",dist[i]);
    }
    return 0;
}

```