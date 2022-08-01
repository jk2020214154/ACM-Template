[题目链接](https://www.acwing.com/problem/content/description/287/)

Ural 大学有 $N$ 名职员，编号为 $1 \\sim N$。

他们的关系就像一棵以校长为根的树，父节点就是子节点的直接上司。

每个职员有一个快乐指数，用整数 $H\_i$ 给出，其中 $1 \\le i \\le N$。

现在要召开一场周年庆宴会，不过，没有职员愿意和直接上司一起参会。

在满足这个条件的前提下，主办方希望邀请一部分职员参会，使得所有参会职员的快乐指数总和最大，求这个最大值。

#### 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，第 $i$ 行表示 $i$ 号职员的快乐指数 $H\_i$。

接下来 $N-1$ 行，每行输入一对整数 $L, K$，表示 $K$ 是 $L$ 的直接上司。

#### 输出格式

输出最大的快乐指数。

#### 数据范围

$1 \\le N \\le 6000$,  
$\-128 \\le H\_i \\le 127$

#### 输入样例：

    7
    1
    1
    1
    1
    1
    1
    1
    1 3
    2 3
    6 4
    7 4
    4 5
    3 5
    

#### 输出样例：

    5
    
    
 ```cpp

/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 6010

using namespace std;

int n,w[MAXN],deg[MAXN];

int head[MAXN],ed[MAXN],nex[MAXN],idx;


int f[MAXN][2];

void add(int a,int b)
{
    ed[idx]=b;
    nex[idx]=head[a];
    head[a]=idx++;
}


void dfs(int root)
{
    f[root][1]=w[root];
    for(int i=head[root];i!=-1;i=nex[i])
    {
        int j=ed[i];
        dfs(j);
        f[root][0]+=max(f[j][0],f[j][1]);
        f[root][1]+=f[j][0];
    }
}

int main()
{
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    
    for(int i=1;i<=n-1;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        add(b,a);
        deg[a]++;
    }
    
    int root=-1;
    for(int i=1;i<=n;i++)
        if(deg[i]==0)
        {
            root=i;
            break;
        }
    
    dfs(root);
    
    printf("%d\n",max(f[root][0],f[root][1]));
    
    return 0;
}


```
