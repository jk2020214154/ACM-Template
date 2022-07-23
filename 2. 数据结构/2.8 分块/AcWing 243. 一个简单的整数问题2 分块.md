[题目链接](https://www.acwing.com/problem/content/244/)

给定一个长度为 $N$ 的数列 $A$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1.  `C l r d`，表示把 $A\[l\],A\[l+1\],…,A\[r\]$ 都加上 $d$。
2.  `Q l r`，表示询问数列中第 $l \\sim r$ 个数的和。

对于每个询问，输出一个整数表示答案。

#### 输入格式

第一行两个整数 $N,M$。

第二行 $N$ 个整数 $A\[i\]$。

接下来 $M$ 行表示 $M$ 条指令，每条指令的格式如题目描述所示。

#### 输出格式

对于每个询问，输出一个整数表示答案。

每个答案占一行。

#### 数据范围

$1 \\le N,M \\le 10^5$,  
$|d| \\le 10000$,  
$|A\[i\]| \\le 10^9$

#### 输入样例：

    10 5
    1 2 3 4 5 6 7 8 9 10
    Q 4 4
    Q 1 10
    Q 2 4
    C 3 6 3
    Q 2 4
    

#### 输出样例：

    4
    55
    9
    15


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

#define MAXN 100010

using namespace std;

typedef long long ll;

int n,m,w[MAXN],add[MAXN];
ll sum[MAXN];

int st[MAXN],ed[MAXN],pos[MAXN];


void modify(int l,int r,int num)
{
    int lpos=pos[l],rpos=pos[r];
    if(lpos==rpos)
    {
        for(int i=l;i<=r;i++)
            w[i]+=num;
        sum[lpos]+=num*(r-l+1);
    }
    else
    {
        for(int i=l;i<=ed[lpos];i++)
            w[i]+=num;
        sum[lpos]+=num*(ed[lpos]-l+1);
        
        for(int i=lpos+1;i<=rpos-1;i++)
            add[i]+=num;
        
        for(int i=st[rpos];i<=r;i++)
            w[i]+=num;

        sum[rpos]+=num*(r-st[rpos]+1);
    }
    
}

ll query(int l,int r)
{
    int lpos=pos[l],rpos=pos[r];
    ll res=0;
    if(lpos==rpos)
    {
        for(int i=l;i<=r;i++)
            res+=w[i];
        res+=add[lpos]*(r-l+1);
    }
    else
    {
        for(int i=l;i<=ed[lpos];i++)
            res+=w[i];
        res+=add[lpos]*(ed[lpos]-l+1);
        
        for(int i=lpos+1;i<=rpos-1;i++)
            res+=sum[i]+add[i]*(ed[i]-st[i]+1);
        
        for(int i=st[rpos];i<=r;i++)
            res+=w[i];

        res+=add[rpos]*(r-st[rpos]+1);        
    }
    return res;
}



int main()
{
    scanf("%d %d",&n,&m);
    
    int block=sqrt(n);//块的大小,每块有block个元素
    
    int t=n/block;//块的数量,共分为t块
    if(n%block!=0)//sqrt(n)的结果不是整数,最后加上一小块
        t++;
    
    for(int i=1;i<=t;i++)//遍历块
    {
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    ed[t]=n;//sqrt(n)的结果不是整数,将右端点更新为n
    
    for(int i=1;i<=n;i++)//遍历所有元素的位置
        pos[i]=(i-1)/block+1;
    
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w[i]);
        //sum[pos[i]]+=w[i];
    }    
    for(int i=1;i<=t;i++)//遍历所有的块
        for(int j=st[i];j<=ed[i];j++)//遍历块内所有元素
            sum[i]+=w[j];
    
    
    for(int i=1;i<=m;i++)
    {
        int l,r,num;
        char op;
        scanf(" %c %d %d",&op,&l,&r);
        if(op=='C')
        {
            scanf("%d",&num);
            modify(l,r,num);
        }
        else if(op=='Q')
            printf("%lld\n",query(l,r));
    
    }
    
    
    
    return 0;
}

```

