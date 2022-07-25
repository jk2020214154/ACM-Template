[题目链接](https://loj.ac/p/6277) 

#### 题目描述

给出一个长为 $n$ 的数列，以及 $n$ 个操作，操作涉及区间加法，单点查值。

#### 输入格式

第一行输入一个数字 $n$。

第二行输入 $n$ 个数字，第 $i$ 个数字为 $a_i$，以空格隔开。

接下来输入 $n$ 行询问，每行输入四个数字 $\mathrm{opt}$、$l$、$r$、$c$，以空格隔开。

若 $\mathrm{opt} = 0$，表示将位于 $[l, r]$ 的之间的数字都加 $c$。

若 $\mathrm{opt} = 1$，表示询问 $a_r$ 的值（$l$ 和 $c$ 忽略）。

#### 输出格式

对于每次询问，输出一行一个数字表示答案。

#### 样例输入

```
4
1 2 2 3
0 1 3 1
1 0 1 0
0 1 2 2
1 0 2 0

```

#### 输出

```
2
5

```

#### 数据范围与提示

对于 $100\%$ 的数据， $1 \leq n \leq 50000$, $-2^{31} \leq \mathrm{others}$、 $\mathrm{ans} \leq 2^{31}-1$ 。

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
#include <cmath>

#define MAXN 50010

using namespace std;


int n,a[MAXN];

int block,t;
int st[MAXN],ed[MAXN],pos[MAXN];

int add[MAXN];
//int sum[MAXN];


void init(int n)
{
    block=sqrt(n);
    t=n/block;
    if(n%block!=0)
        t++;    
    for(int i=1;i<=t;i++)
    {
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    
    ed[t]=n;
    
    for(int i=1;i<=n;i++)
        pos[i]=(i-1)/block+1;
}

void modify(int l,int r,int num){
    int lpos=pos[l],rpos=pos[r];//lpos对应l的块,rpos对应r的块
    if(lpos==rpos){//情况1:处理碎片块,l,r的块相同,暴力处理
        for(int i=l;i<=r;i++)//更新区间[l,r]的w[i]
            a[i]+=num;
    }
    else{
        for(int i=l;i<=ed[lpos];i++)//情况1:处理碎片块,l所属的块暴力处理,更新[l,ed[lpos]]块的w[i]
            a[i]+=num;
        for(int i=lpos+1;i<=rpos-1;i++)//情况2:处理整块,更新[lpos+1,rpos-1]整块的add
            add[i]+=num;
        for(int i=st[rpos];i<=r;i++)//情况1:处理碎片块,r所属的块暴力处理,更新[st[rpos],r]块的w[i]
            a[i]+=num;
    }
}




int main()
{
    scanf("%d",&n);
    init(n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    
    for(int i=1;i<=n;i++)
    {
        int op,l,r,c;
        scanf("%d %d %d %d",&op,&l,&r,&c);
        if(op==0)
            modify(l,r,c);
        else if(op==1)
            printf("%d\n",a[r]+add[pos[r]]);
    } 
    
    return 0;
}


```
