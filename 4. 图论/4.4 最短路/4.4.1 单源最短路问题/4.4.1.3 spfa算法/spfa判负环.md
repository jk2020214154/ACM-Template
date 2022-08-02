
##### 求单个起点出发能否到达负环

```cpp
//求起点出发能否到达负环
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 100010

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int head[MAXN],ed[MAXN],val[MAXN],nex[MAXN],idx;
int dist[MAXN],vis[MAXN],cnt[MAXN];

void add(int x,int y,int z)
{
    ed[idx]=y;
    val[idx]=z;
    nex[idx]=head[x];
    head[x]=idx++;
}

int spfa(int start)
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    dist[start]=0;
    vis[start]=1;
    queue<int> q;
    q.push(start);
    while(q.size()>0)
    {
        int temp=q.front();
        q.pop();
        vis[temp]=0;
        for(int i=head[temp];i!=-1;i=nex[i])
        {
            if(dist[ed[i]]>dist[temp]+val[i])
            {
                dist[ed[i]]=dist[temp]+val[i];
                /****添加部分****/
                cnt[ed[i]]=cnt[temp]+1;
                if(cnt[ed[i]]>=n)
                    return 1;
                /****添加部分****/
                if(vis[ed[i]]==0)
                {
                    q.push(ed[i]);
                    vis[ed[i]]=1;
                }
            }
        }
    }
    return 0;
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
    int res=spfa(1);
    if(res==1)
        printf("Yes\n");
    else printf("No\n");
    return 0;
}

```


##### 求整个图是否存在负环

[题目链接](https://www.acwing.com/problem/content/854/)

给定一个 $n$ 个点 $m$ 条边的有向图，图中可能存在重边和自环， **边权可能为负数**。

请你判断图中是否存在负权回路。

#### 输入格式

第一行包含整数 $n$ 和 $m$。

接下来 $m$ 行每行包含三个整数 $x,y,z$，表示存在一条从点 $x$ 到点 $y$ 的有向边，边长为 $z$。

#### 输出格式

如果图中**存在**负权回路，则输出 `Yes`，否则输出 `No`。

#### 数据范围

$1 \le n \le 2000$,  
$1 \le m \le 10000$,  
图中涉及边长绝对值均不超过 $10000$。

#### 输入样例：

    3 3
    1 2 -1
    2 3 4
    3 1 -4
    

#### 输出样例：

    Yes


```cpp

//求整个图是否存在负环
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 100010

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int head[MAXN],ed[MAXN],val[MAXN],nex[MAXN],idx;
int dist[MAXN],vis[MAXN],cnt[MAXN];

void add(int x,int y,int z)
{
    ed[idx]=y;
    val[idx]=z;
    nex[idx]=head[x];
    head[x]=idx++;
}

int spfa()
{
    memset(dist,0x3f,sizeof(dist));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    /****修改部分****/
    for(int i=1;i<=n;i++)
    {
        q.push(i);
        vis[i]=1;
    }
    /****修改部分****/
    while(q.size()>0)
    {
        int temp=q.front();
        q.pop();
        vis[temp]=0;
        for(int i=head[temp];i!=-1;i=nex[i])
        {
            if(dist[ed[i]]>dist[temp]+val[i])
            {
                dist[ed[i]]=dist[temp]+val[i];
                cnt[ed[i]]=cnt[temp]+1;
                if(cnt[ed[i]]>=n)
                    return 1;
                if(vis[ed[i]]==0)
                {
                    q.push(ed[i]);
                    vis[ed[i]]=1;
                }
            }
        }
    }
    return 0;
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
    int res=spfa();
    if(res==1)
        printf("Yes\n");
    else printf("No\n");
    return 0;
}

```