[题目链接](https://loj.ac/p/6284) 

#### 题目描述

给出一个长为 $n$ 的数列，以及 $n$ 个操作，操作涉及区间询问等于一个数 $c$ 的元素，并将这个区间的所有元素改为 $c$。

#### 输入格式

第一行输入一个数字 $n$。

第二行输入 $n$ 个数字，第 $i$ 个数字为 $a_i$，以空格隔开。

接下来输入 $n$ 行询问，每行输入三个数字 $l、r、c$，以空格隔开。

表示先查询位于 $[l,r]$ 的数字有多少个是 $c$，再把位于 $[l,r]$ 的数字都改为 $c$。

#### 输出格式

对于每次询问，输出一行一个数字表示答案。

#### 样例输入

```
4
1 2 2 4
1 3 1
1 4 4
1 2 2
1 4 2

```

#### 输出

```
1
1
0
2

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


int a[MAXN],num[MAXN];


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

void update(int x)
{
    if(num[x]==-1)
        return ;
    for(int i=st[x];i<=ed[x];i++)
        a[i]=num[x];
    
    num[x]=-1;

}




int main()
{   
    scanf("%d",&n);
    init(n);
    memset(num,-1,sizeof(num));
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        int sum=0;
        int l,r,c;
        scanf("%d %d %d",&l,&r,&c);
        int lpos=pos[l],rpos=pos[r];
        if(lpos==rpos)
        {
            update(lpos);
            for(int i=l;i<=r;i++)
            {
                if(a[i]==c)
                    sum++;
                else a[i]=c;
            }
        }
        else
        {
            update(lpos);
            for(int i=l;i<=ed[lpos];i++)
            {
                if(a[i]==c)
                    sum++;
                else a[i]=c;
            }
            
            for(int i=lpos+1;i<=rpos-1;i++)
            {
                if(num[i]==-1)
                {
                    for(int j=st[i];j<=ed[i];j++)
                    {
                        if(a[j]==c)
                            sum++;
                        else a[j]=c;
                    }
                    num[i]=c;
                }
                else if(num[i]==c)
                    sum+=ed[i]-st[i]+1;
                else num[i]=c;
            }
            
            update(rpos);
            for(int i=st[rpos];i<=r;i++)
            {
                if(a[i]==c)
                    sum++;
                else a[i]=c;
            }
        }
        printf("%d\n",sum);
        
    }
    return 0;
}


```
