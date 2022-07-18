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

int n,a[MAXN],temp[MAXN];

ll res=0;

void merge_sort(int q[],int l,int r)
{
    if(l>=r)
        return ;
    int mid=(l+r)/2;
    merge_sort(q,l,mid);
    merge_sort(q,mid+1,r);
    int k=1,i=l,j=mid+1;
    while(i<=mid&&j<=r)
    {
        if(q[i]<=q[j])
            temp[k++]=q[i++];
        else 
        {
            res+=(mid-i+1);//增添部分
            temp[k++]=q[j++];
        }
    }
    while(i<=mid)
        temp[k++]=q[i++];
    while(j<=r)
        temp[k++]=q[j++];
    for(int i=l,j=1;i<=r;i++,j++)
        q[i]=temp[j];
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    merge_sort(a,1,n);
    printf("%lld\n",res);
    
    return 0;
}


```
