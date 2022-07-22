[题目链接](https://www.acwing.com/problem/content/799/)

输入一个长度为 $n$ 的整数序列。

接下来输入 $m$ 个操作，每个操作包含三个整数 $l, r, c$，表示将序列中 $\[l, r\]$ 之间的每个数加上 $c$。

请你输出进行完所有操作后的序列。

#### 输入格式

第一行包含两个整数 $n$ 和 $m$。

第二行包含 $n$ 个整数，表示整数序列。

接下来 $m$ 行，每行包含三个整数 $l，r，c$，表示一个操作。

#### 输出格式

共一行，包含 $n$ 个整数，表示最终序列。

#### 数据范围

$1 \\le n,m \\le 100000$,  
$1 \\le l \\le r \\le n$,  
$\-1000 \\le c \\le 1000$,  
$\-1000 \\le 整数序列中元素的值 \\le 1000$

#### 输入样例：

    6 3
    1 2 2 1 2 1
    1 3 1
    3 5 1
    1 6 1
    

#### 输出样例：

    3 4 5 3 4 2


```cpp


#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int n,m;
int a[MAXN],d[MAXN];

void add(int v,int l,int r)
{
    d[r+1]-=v;
    d[l]+=v;
}

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
        add(a[i],i,i);
    }    
    for(int i=1;i<=m;i++)
    {
        int l,r,v;
        cin >> l >> r >> v;
        add(v,l,r);
    }
    for(int i=1;i<=n;i++)
    {
        d[i]=d[i]+d[i-1];
        cout << d[i] << ' ';
    }
    return 0;
}

```