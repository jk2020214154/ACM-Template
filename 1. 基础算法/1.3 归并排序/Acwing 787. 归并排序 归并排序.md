[题目链接](https://www.acwing.com/problem/content/789/)


给定你一个长度为 $n$ 的整数数列。

请你使用归并排序对这个数列按照从小到大进行排序。

并将排好序的数列按顺序输出。

#### 输入格式

输入共两行，第一行包含整数 $n$。

第二行包含 $n$ 个整数（所有整数均在 $1 \\sim 10^9$ 范围内），表示整个数列。

#### 输出格式

输出共一行，包含 $n$ 个整数，表示排好序的数列。

#### 数据范围

$1 \\le n \\le 100000$

#### 输入样例：

    5
    3 1 2 4 5
    

#### 输出样例：

    1 2 3 4 5
   
   
```cpp


// Problem: 归并排序
// Contest: AcWing
// URL: https://www.acwing.com/problem/content/789/
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// Date: 2022-07-18 11:04:00
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

int n,a[MAXN],temp[MAXN];

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
        else temp[k++]=q[j++];
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
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
    
    return 0;
}

```


