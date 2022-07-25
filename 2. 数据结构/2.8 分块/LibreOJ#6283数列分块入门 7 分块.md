[题目链接](https://loj.ac/p/6283) 

#### 题目描述

给出一个长为 $n$ 的数列，以及 $n$ 个操作，操作涉及区间乘法，区间加法，单点询问。

#### 输入格式

第一行输入一个数字 $n$。

第二行输入 $n$ 个数字，第 $i$ 个数字为 $a_i$，以空格隔开。

接下来输入 $n$ 行询问，每行输入四个数字 $\mathrm{opt}、l、r、c$，以空格隔开。

若 $\mathrm{opt} = 0$，表示将位于 $[l, r]$ 的之间的数字都加 $c$。

若 $\mathrm{opt} = 1$，表示将位于 $[l, r]$ 的之间的数字都乘 $c$。

若 $\mathrm{opt} = 2$，表示询问 $a_r$ 的值 $\mathop{\mathrm{mod}} 10007$（$l$ 和 $c$ 忽略）。

#### 输出格式

对于每次询问，输出一行一个数字表示答案。

#### 样例输入

```
7
1 2 2 3 9 3 2
0 1 3 1
2 1 3 1
1 1 4 4
0 1 7 2
1 2 6 4
1 1 6 5
2 2 6 4

```

#### 输出

```
3
100

```

#### 数据范围与提示

对于 $100\%$ 的数据， $1 \leq n \leq 100000, -2^{31} \leq \mathrm{others}、 \mathrm{ans} \leq 2^{31}-1$ 。


```cpp
/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

#define MAXN 100010

using namespace std;

typedef long long ll;


const int mod=10007;
int n;

int block,t;
int st[MAXN],ed[MAXN],pos[MAXN];


int a[MAXN],sum[MAXN],add[MAXN],mul[MAXN];


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
        mul[i]=1;
    }
    
    ed[t]=n;
    
    for(int i=1;i<=n;i++)
        pos[i]=(i-1)/block+1;
}

void update(int x)
{
    for(int i=st[x];i<=ed[x];i++)
        a[i]=(a[i]*mul[x]+add[x])%mod;
    add[x]=0;
    mul[x]=1;
}


void modify(int l,int r,int num1,int num2)
{
    int lpos=pos[l],rpos=pos[r];
    if(lpos==rpos)
    {
        update(lpos);
        for(int i=l;i<=r;i++)
            a[i]=(a[i]*num1+num2)%mod;
    }
    else
    {
        update(lpos);
        for(int i=l;i<=ed[lpos];i++)
            a[i]=(a[i]*num1+num2)%mod;
        
        for(int i=lpos+1;i<=rpos-1;i++)
        {
            add[i]=(add[i]*num1+num2)%mod;
            mul[i]=(mul[i]*num1)%mod;
        }
        
        update(rpos);
        for(int i=st[rpos];i<=r;i++)
            a[i]=(a[i]*num1+num2)%mod;
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
            modify(l,r,1,c);
        else if(op==1)
            modify(l,r,c,0);
        else if(op==2)
            printf("%d\n",(a[r]*mul[pos[r]]+add[pos[r]])%mod);
        
    }
    return 0;
}

```
