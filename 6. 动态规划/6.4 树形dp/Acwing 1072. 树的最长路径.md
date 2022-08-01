[题目链接](https://www.acwing.com/problem/content/1074/)


给定一棵树，树中包含 $n$ 个结点（编号$1$~$n$）和 $n-1$ 条无向边，每条边都有一个权值。

现在请你找到树中的一条最长路径。

换句话说，要找到一条路径，使得使得路径两端的点的距离最远。

注意：路径中可以只包含一个点。

#### 输入格式

第一行包含整数 $n$。

接下来 $n-1$ 行，每行包含三个整数 $a\_i,b\_i,c\_i$，表示点 $a\_i$ 和 $b\_i$ 之间存在一条权值为 $c\_i$ 的边。

#### 输出格式

输出一个整数，表示树的最长路径的长度。

#### 数据范围

$1 \\le n \\le 10000$,  
$1 \\le a\_i,b\_i \\le n$,  
$\-10^5 \\le c\_i \\le 10^5$

#### 输入样例：

    6
    5 1 6
    1 4 5
    6 3 9
    2 6 8
    6 1 7
    

#### 输出样例：

    22
    
    
 ```cpp
 
 #include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 10010
#define MAXM 20010


using namespace std;



int n;
int head[MAXN],ed[MAXM],nex[MAXM],val[MAXM],idx;
int res=0;

void add(int a,int b,int c)
{
    ed[idx]=b;
    val[idx]=c;
    nex[idx]=head[a];
    head[a]=idx++;
}


int dfs(int u,int fa)
{
    int dis=0;//从当前点往下走的最大长度
    int d1=0,d2=0;//d1表示最大值,d2表示次大值
    for(int i=head[u];i!=-1;i=nex[i])
    {
        int j=ed[i];
        if(j==fa)
            continue;
        int d=dfs(j,u)+val[i];
        dis=max(dis,d);
        if(d>=d1)
            d2=d1,d1=d;
        else if(d>d2)
            d2=d;
    }
    res=max(res,d1+d2);
    
    return dis;
}



int main()
{
    memset(head,-1,sizeof(head));    
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        add(a,b,c),add(b,a,c);
    }
    
    dfs(1,-1);
    
    
    printf("%d\n",res);
    return 0;
}


```
 
