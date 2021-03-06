[题目链接](https://www.acwing.com/problem/content/243/)


在完成了分配任务之后，西部 $314$ 来到了楼兰古城的西部。

相传很久以前这片土地上(比楼兰古城还早)生活着两个部落，一个部落崇拜尖刀(`V`)，一个部落崇拜铁锹(`∧`)，他们分别用 `V` 和 `∧` 的形状来代表各自部落的图腾。

西部 $314$ 在楼兰古城的下面发现了一幅巨大的壁画，壁画上被标记出了 $n$ 个点，经测量发现这 $n$ 个点的水平位置和竖直位置是两两不同的。

西部 $314$ 认为这幅壁画所包含的信息与这 $n$ 个点的相对位置有关，因此不妨设坐标分别为 $(1,y\_1),(2,y\_2),…,(n,y\_n)$，其中 $y\_1 \\sim y\_n$ 是 $1$ 到 $n$ 的一个排列。

西部 $314$ 打算研究这幅壁画中包含着多少个图腾。

如果三个点 $(i,y\_i),(j,y\_j),(k,y\_k)$ 满足 $1 \\le i < j < k \\le n$ 且 $y\_i > y\_j, y\_j < y\_k$，则称这三个点构成 `V` 图腾;

如果三个点 $(i,y\_i),(j,y\_j),(k,y\_k)$ 满足 $1 \\le i < j< k \\le n$ 且 $y\_i < y\_j, y\_j > y\_k$，则称这三个点构成 `∧` 图腾;

西部 $314$ 想知道，这 $n$ 个点中两个部落图腾的数目。

因此，你需要编写一个程序来求出 `V` 的个数和 `∧` 的个数。

#### 输入格式

第一行一个数 $n$。

第二行是 $n$ 个数，分别代表 $y\_1，y\_2,…,y\_n$。

#### 输出格式

两个数，中间用空格隔开，依次为 `V` 的个数和 `∧` 的个数。

#### 数据范围

对于所有数据，$n \\le 200000$，且输出答案不会超过 $int64$。  
$y\_1 \\sim y\_n$ 是 $1$ 到 $n$ 的一个排列。

#### 输入样例：

    5
    1 5 3 2 4
    

#### 输出样例：

    3 4
   
```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

typedef long long ll;


int n,a[MAXN];
int C[MAXN];
int High[MAXN],Low[MAXN];

int lowbit(int x)
{
    return x&-x;
}

void add(int pos,int val)
{
    for(int i=pos;i<=n;i+=lowbit(i))
        C[i]+=val;
}

int sum(int pos)
{
    int res=0;
    for(int i=pos;i>=1;i-=lowbit(i))
        res+=C[i];
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    
    for(int i=1;i<=n;i++)
    {
        int y=a[i];
        High[i]=sum(n)-sum(y);
        Low[i]=sum(y-1);
        add(y,1);
    }
    
    memset(C,0,sizeof(C));
    ll res1=0,res2=0;
    
    for(int i=n;i>=1;i--)
    {
        int y=a[i];
        res1+=High[i]*(ll)(sum(n)-sum(y));
        res2+=Low[i]*(ll)sum(y-1);
        add(y,1);
    }
    printf("%lld %lld\n",res1,res2);
    return 0;
}


```
