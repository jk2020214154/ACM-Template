#### [题目链接](https://www.acwing.com/problem/content/247/)


给定一个长度为 $N$ 的数列 $A$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1.  `C l r d`，表示把 $A\[l\],A\[l+1\],…,A\[r\]$ 都加上 $d$。
2.  `Q l r`，表示询问 $A\[l\],A\[l+1\],…,A\[r\]$ 的最大公约数($GCD$)。

对于每个询问，输出一个整数表示答案。

#### 输入格式

第一行两个整数 $N,M$。

第二行 $N$ 个整数 $A\[i\]$。

接下来 $M$ 行表示 $M$ 条指令，每条指令的格式如题目描述所示。

#### 输出格式

对于每个询问，输出一个整数表示答案。

每个答案占一行。

#### 数据范围

$N \\le 500000, M \\le 100000$,  
$1 \\le A\[i\] \\le 10^{18}$,  
$|d| \\le 10^{18}$

#### 输入样例：

    5 5
    1 3 5 7 9
    Q 1 5
    C 1 5 1
    Q 1 5
    C 3 3 6
    Q 2 4
    

#### 输出样例：

    1
    2
    4


```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 500010

using namespace std;

typedef long long ll;


int n,m;
ll a[MAXN];
struct Tree{
    int l;
    int r;
    ll sum;
    ll d;
}tree[4*MAXN];

ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}

void pushup(Tree &root,Tree &l,Tree &r)
{
    root.sum=l.sum+r.sum;
    root.d=gcd(l.d,r.d);
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
        tree[root].sum=tree[root].d=a[l]-a[l-1];
        return ;
    }
    int mid=(l+r)/2;
    
    build(2*root,l,mid);
    build(2*root+1,mid+1,r);
    pushup(root);
    
    
}

void modify(int root,int pos,ll val)
{
    if(tree[root].l==pos&&tree[root].r==pos)
    {
        tree[root].sum=tree[root].d=tree[root].sum+val;
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
            return  res;
        }
    }
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
        ll d;
        scanf(" %c %d %d",&op,&l,&r);
        if(op=='Q')
        {
            //gcd(a1,a2,...,an)=gcd(a1,a2-a1,a3-a2,...,an-a{n-1})
            Tree left=query(1,1,l);//由差分反向求出实际值
            Tree right={0,0,0,0};
            if(l+1<=n)
                right=query(1,l+1,r);
            printf("%lld\n",abs(gcd(left.sum,right.d)));
        }
        else if(op=='C')
        {
            scanf("%lld",&d);
            modify(1,l,d);
            if(r+1<=n)
                modify(1,r+1,-d);
        }
        
        
        
    }
    return 0;
}
```
