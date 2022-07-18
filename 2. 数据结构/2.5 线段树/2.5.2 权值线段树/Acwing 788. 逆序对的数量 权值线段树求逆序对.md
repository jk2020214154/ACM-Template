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

int n;
struct node{
    int num;
    int pos;
}s[MAXN];

int id[MAXN];
ll res;

int cmp(node a,node b)
{
    if(a.num==b.num)
        return a.pos<b.pos;
    return a.num<b.num;
}


struct Tree{
    int l;
    int r;
    int dat;
}tree[4*MAXN];


void pushup(int root)
{
    tree[root].dat=tree[2*root].dat+tree[2*root+1].dat;
}

void build(int root,int l,int r)
{
    tree[root].l=l,tree[root].r=r;
    if(l==r)
    {
        tree[root].dat=0;
        return ;
    }
    int mid=(l+r)/2;
    build(2*root,l,mid);
    build(2*root+1,mid+1,r);
    pushup(root);
}


void modify(int root,int pos,int val)
{
    if(tree[root].l==pos&&tree[root].r==pos)
    {
        tree[root].dat+=val;
        return ;
    }
    int mid=(tree[root].l+tree[root].r)/2;
    if(pos<=mid)
        modify(2*root,pos,val);
    else modify(2*root+1,pos,val);
    pushup(root);
}

ll query(int root,int l,int r)
{
    if(l<=tree[root].l&&r>=tree[root].r)
        return tree[root].dat;
    int mid=(tree[root].l+tree[root].r)/2;
    ll ans=0;
    if(l<=mid)
        ans+=query(2*root,l,r);
    if(r>mid)
        ans+=query(2*root+1,l,r);
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
    
    build(1,1,n);

    for(int i=n;i>=1;i--)
    {
        modify(1,id[i],1);
        res+=query(1,1,id[i]-1);
    }    

    printf("%lld\n",res);
    return 0;
}

```
