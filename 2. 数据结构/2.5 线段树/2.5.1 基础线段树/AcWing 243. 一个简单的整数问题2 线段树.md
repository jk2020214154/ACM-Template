[题目链接](https://www.acwing.com/problem/content/description/244/)



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
    
    #include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

typedef long long ll;

int n,m;
ll a[MAXN];

struct Tree{
    int l;
    int r;
    ll sum;
    ll add;//懒标记
}tree[4*MAXN];

void pushup(int root)
{
    tree[root].sum=tree[2*root].sum+tree[2*root+1].sum;
}

void pushdown(int root)
{
    if(tree[root].add!=0)
    {

        tree[2*root].add+=tree[root].add;
        tree[2*root].sum+=(ll)(tree[2*root].r-tree[2*root].l+1)*tree[root].add;
        tree[2*root+1].add+=tree[root].add;
        tree[2*root+1].sum+=(ll)(tree[2*root+1].r-tree[2*root+1].l+1)*tree[root].add;        
        tree[root].add=0;
    }


}

void build(int root,int l,int r)
{
    tree[root].l=l,tree[root].r=r;
    if(l==r)
    {
        tree[root].sum=a[l],tree[root].add=0;
        return ;
    }
    int mid=(l+r)/2;
    build(2*root,l,mid);
    build(2*root+1,mid+1,r);
    pushup(root);
}

void modify(int root,int l,int r,ll val)
{
    if(l<=tree[root].l&&r>=tree[root].r)
    {
        tree[root].sum+=(ll)(tree[root].r-tree[root].l+1)*val;
        tree[root].add+=val;
    }
    else
    {
        pushdown(root);
        int mid=(tree[root].l+tree[root].r)/2;
        if(l<=mid)
            modify(2*root,l,r,val);
        if(r>mid)
            modify(2*root+1,l,r,val);
        pushup(root);
    }


}

ll query(int root,int l,int r)
{

    if(l<=tree[root].l&&r>=tree[root].r)
        return tree[root].sum;
    pushdown(root);
    int mid=(tree[root].l+tree[root].r)/2;
    ll sum=0;
    if(l<=mid)
        sum+=query(2*root,l,r);
    if(r>mid)
        sum+=query(2*root+1,l,r);
    return sum;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        char op;
        int l,r;
        ll num;
        scanf(" %c %d %d",&op,&l,&r);
        if(op=='Q')
            printf("%lld\n",query(1,l,r));
        else if(op=='C')
        {
            scanf("%lld",&num);
            modify(1,l,r,num);
        }
    }
    return 0;
}
  
  
  
```
