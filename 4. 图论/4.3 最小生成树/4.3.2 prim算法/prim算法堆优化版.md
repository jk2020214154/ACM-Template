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



#### prime算法堆优化版


```cpp


#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 5010
#define MAXM 400010//由于是无向图,开两倍的空间存边

using namespace std;

typedef pair<int,int> PII;
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

int prim(int start){
    int res=0,cnt=0;
    priority_queue<PII,vector<PII>,greater<PII> > q;
    for(int i=1;i<=n;i++)
        dis[i]=inf;
    dis[start]=0;
    q.push({0,start});
    while(q.size()>0){
        PII temp=q.top();
        q.pop();
        if(vis[temp.second]==1)//当前点访问过
            continue;
        vis[temp.second]=1;//标记该点访问过
        res+=temp.first;//生成树加入该边
        cnt++;//记录点的个数
        for(int i=head[temp.second];i!=-1;i=nex[i])
            if(vis[ed[i]]==0)
                q.push({val[i],ed[i]});
    }
    if(cnt<n)//点的个数小于n
        return -1;
    else return res;
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
    int ans=prim(1);
    if(ans==-1)
        printf("orz\n");
    else printf("%d\n",ans);
    return 0;
}

```