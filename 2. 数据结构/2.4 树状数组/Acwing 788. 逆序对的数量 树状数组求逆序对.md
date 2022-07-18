[题目链接](https://www.acwing.com/problem/content/790/)


给定一个长度为 $n$ 的整数数列，请你计算数列中的逆序对的数量。

逆序对的定义如下：对于数列的第 $i$ 个和第 $j$ 个元素，如果满足 $i < j$ 且 $a\[i\] > a\[j\]$，则其为一个逆序对；否则不是。

#### 输入格式

第一行包含整数 $n$，表示数列的长度。

第二行包含 $n$ 个整数，表示整个数列。

#### 输出格式

输出一个整数，表示逆序对的个数。

#### 数据范围

$1 \\le n \\le 100000$，  
数列中的元素的取值范围 $\[1,10^9\]$。

#### 输入样例：

    6
    2 3 4 5 6 1
    

#### 输出样例：

    5
    

#### 正序求解


```cpp
// Problem: 逆序对的数量
// Contest: AcWing
// URL: https://www.acwing.com/problem/content/790/
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// Date: 2022-07-18 10:44:54
// 
// Powered by CP Editor (https://cpeditor.org)

/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/


#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

typedef long long ll;

int n;
struct node{
    int num;
    int pos;
}s[MAXN];

int id[MAXN],C[MAXN];
ll res;

int cmp(node a,node b)
{
    if(a.num==b.num)
        return a.pos<b.pos;
    return a.num<b.num;
}


int lowbit(int x)
{
    return x&-x;
}

void add(int x,int val)
{
    for(int i=x;i<=n;i+=lowbit(i))
        C[i]+=val;
}

ll sum(int x)
{
    ll ans=0;
    for(int i=x;i>=1;i-=lowbit(i))
        ans+=C[i];
    return ans;
}



int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i].num);
        s[i].pos=i;
    }
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++)
        id[s[i].pos]=i;  
    for(int i=1;i<=n;i++)
    {
        add(id[i],1);
        res+=i-sum(id[i]);
    } 
    printf("%lld\n",res);
    return 0;
}
```

#### 逆序求解


```cpp
// Problem: 逆序对的数量
// Contest: AcWing
// URL: https://www.acwing.com/problem/content/790/
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// Date: 2022-07-18 10:44:54
// 
// Powered by CP Editor (https://cpeditor.org)

/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/


#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

typedef long long ll;

int n;
struct node{
    int num;
    int pos;
}s[MAXN];

int id[MAXN],C[MAXN];
ll res;

int cmp(node a,node b)
{
    if(a.num==b.num)
        return a.pos<b.pos;
    return a.num<b.num;
}


int lowbit(int x)
{
    return x&-x;
}

void add(int x,int val)
{
    for(int i=x;i<=n;i+=lowbit(i))
        C[i]+=val;
}

ll sum(int x)
{
    ll ans=0;
    for(int i=x;i>=1;i-=lowbit(i))
        ans+=C[i];
    return ans;
}



int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i].num);
        s[i].pos=i;
    }
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++)
        id[s[i].pos]=i;  
    for(int i=n;i>=1;i--)
    {
        add(id[i],1);
        res+=sum(id[i]-1);
    } 
    printf("%lld\n",res);
    return 0;
}

```


