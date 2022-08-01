[题目链接](https://www.luogu.com.cn/problem/P3366)



# 【模板】最小生成树

## 题目描述

如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出 `orz`。

## 输入格式

第一行包含两个整数 $N,M$，表示该图共有 $N$ 个结点和 $M$ 条无向边。

接下来 $M$ 行每行包含三个整数 $X_i,Y_i,Z_i$，表示有一条长度为 $Z_i$ 的无向边连接结点 $X_i,Y_i$。

## 输出格式

如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。如果该图不连通则输出 `orz`。

## 样例 #1

### 样例输入 #1

```
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3
```

### 样例输出 #1

```
7
```

## 提示

数据规模：

对于 $20\%$ 的数据，$N\le 5$，$M\le 20$。

对于 $40\%$ 的数据，$N\le 50$，$M\le 2500$。

对于 $70\%$ 的数据，$N\le 500$，$M\le 10^4$。

对于 $100\%$ 的数据：$1\le N\le 5000$，$1\le M\le 2\times 10^5$，$1\le Z_i \le 10^4$。


样例解释：

 ![](https://cdn.luogu.com.cn/upload/pic/2259.png) 

所以最小生成树的总边权为 $2+2+3=7$。



#### prim算法朴素版


```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 5010
#define MAXM 400010//由于是无向图,开两倍的空间存边

using namespace std;

const int inf=0x3f3f3f3f;
int n,m;
int dis[MAXN],vis[MAXN];
int head[MAXN],ed[MAXM],nex[MAXM],val[MAXM],idx;

void add(int a,int b,int c){
    ed[idx]=b;
    val[idx]=c;
    nex[idx]=head[a];
    head[a]=idx++;
}

int prim(){
    for(int i=1;i<=n;i++)//将每个点到生成树的距离初始化为无穷大
        dis[i]=inf;
    int res=0;
    dis[1]=0;//将1(也可选择其他的点)作为生成树的起点
    for(int i=1;i<=n;i++){
        int pos=-1;
        for(int j=1;j<=n;j++)//找到未被访问并且距离最小的点
            if(vis[j]==0&&(pos==-1||dis[pos]>dis[j]))
                pos=j;
        if(dis[pos]==inf)//所有点都未连通
            return -1;
        vis[pos]=1;//标记作为它已被使用
        res+=dis[pos];
        for(int j=head[pos];j!=-1;j=nex[j])//枚举从pos点出发的边并更新dis
            if(vis[ed[j]]==0&&dis[ed[j]]>val[j])
                dis[ed[j]]=val[j];
    }
    return res;
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int start_,end_,val_;
        scanf("%d %d %d",&start_,&end_,&val_);
        add(start_,end_,val_);
        add(end_,start_,val_);
    }
    int ans=prim();
    if(ans==-1)
        printf("orz\n");
    else printf("%d\n",ans);
    return 0;
}

```
