#### [题目链接](https://www.acwing.com/problem/content/246/)


给定长度为 $N$ 的数列 $A$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1.  `1 x y`，查询区间 $\[x,y\]$ 中的最大连续子段和，即 $\\max\\limits\_{x \\le l \\le r \\le y}${$\\sum\\limits^r\_{i=l} A\[i\]$}。
2.  `2 x y`，把 $A\[x\]$ 改成 $y$。

对于每个查询指令，输出一个整数表示答案。

#### 输入格式

第一行两个整数 $N,M$。

第二行 $N$ 个整数 $A\[i\]$。

接下来 $M$ 行每行 $3$ 个整数 $k,x,y$，$k=1$ 表示查询（此时如果 $x>y$，请交换 $x,y$），$k=2$ 表示修改。

#### 输出格式

对于每个查询指令输出一个整数表示答案。

每个答案占一行。

#### 数据范围

$N \\le 500000, M \\le 100000$,  
$\-1000 \\le A\[i\] \\le 1000$

#### 输入样例：

    5 3
    1 2 -3 4 5
    1 2 3
    2 2 -1
    1 3 2
    

#### 输出样例：

    2
    -1

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 500010


using namespace std;

int n,m,a[MAXN];

struct Tree{
    int l,r;
    int tmax,lmax,rmax;
    int sum;
}tree[4*MAXN];


void pushup(Tree &root,Tree &l,Tree &r)
{
    root.sum=l.sum+r.sum;
    root.lmax=max(l.lmax,l.sum+r.lmax);
    root.rmax=max(r.rmax,r.sum+l.rmax);
    root.tmax=max({l.tmax,r.tmax,l.rmax+r.lmax});
}


void pushup(int root)
{
    pushup(tree[root],tree[2*root],tree[2*root+1]);
}

void build(int root,int l,int r)
{
    tree[root].l=l,tree[root].r=r;
    if(l==r)
    {
        tree[root].tmax=tree[root].lmax=tree[root].rmax=tree[root].sum=a[l];
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
        tree[root].tmax=tree[root].lmax=tree[root].rmax=tree[root].sum=val;
        return ;
    }
    else
    {
        int mid=(tree[root].l+tree[root].r)/2;
        if(pos<=mid)
            modify(2*root,pos,val);
        else modify(2*root+1,pos,val);
        pushup(root);
    }
}

Tree query(int root,int l,int r)
{
    if(l<=tree[root].l&&r>=tree[root].r)
        return tree[root];
    else
    {
        int mid=(tree[root].l+tree[root].r)/2;
        if(r<=mid)
            return query(2*root,l,r);
        else if(l>mid)
            return query(2*root+1,l,r);
        else
        {
            Tree left=query(2*root,l,r);
            Tree right=query(2*root+1,l,r);
            Tree res;
            pushup(res,left,right);
            return res;
        }
    }
}


int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op,l,r;
        scanf("%d %d %d",&op,&l,&r);
        if(op==1)
        {
            if(l>r)
                swap(l,r);
            printf("%d\n",query(1,l,r).tmax);
        }
        else modify(1,l,r);
        
        
    }
    
    return 0;
}

```
