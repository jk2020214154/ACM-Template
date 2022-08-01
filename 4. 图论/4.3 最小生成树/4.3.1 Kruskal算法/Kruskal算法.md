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


#### Kruskal算法

```cpp


#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int fa[MAXN];
struct node{
    int start_;
    int end_;
    int val;
}s[2*MAXN];

int cmp(struct node a,struct node b){
    return a.val<b.val;
}

void init(int n){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    if(fa[x]!=x)
        fa[x]=find(fa[x]);
    return fa[x];
}

int main(){
    int n,m,res=0,cnt=0;
    scanf("%d %d",&n,&m);
    init(n);
    for(int i=1;i<=m;i++)
        scanf("%d %d %d",&s[i].start_,&s[i].end_,&s[i].val);
    sort(s+1,s+m+1,cmp);
    for(int i=1;i<=m;i++){
        int f_start=find(s[i].start_),f_end=find(s[i].end_);
        if(f_start!=f_end){
            fa[f_end]=f_start;
            res+=s[i].val;
            cnt++;
        }
    }
    if(cnt<n-1)
        printf("orz\n");
    else printf("%d\n",res);
    return 0;
}
```