[题目链接](https://www.acwing.com/problem/content/255/)

#### 题目描述

您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：

1.  插入数值 $x$。
2.  删除数值 $x$(若有多个相同的数，应只删除一个)。
3.  查询数值 $x$ 的排名(若有多个相同的数，应输出最小的排名)。
4.  查询排名为 $x$ 的数值。
5.  求数值 $x$ 的前驱(前驱定义为小于 $x$ 的最大的数)。
6.  求数值 $x$ 的后继(后继定义为大于 $x$ 的最小的数)。

**注意：** 数据保证查询的结果一定存在。

#### 输入格式

第一行为 $n$，表示操作的个数。

接下来 $n$ 行每行有两个数 $opt$ 和 $x$，$opt$ 表示操作的序号($1 \\le opt \\le 6$)。

#### 输出格式

对于操作 $3,4,5,6$ 每行输出一个数，表示对应答案。

#### 数据范围

$1 \\le n \\le 100000$,所有数均在 $\-10^7$ 到 $10^7$ 内。

#### 输入样例：

    8
    1 10
    1 20
    1 30
    3 20
    4 2
    2 10
    5 25
    6 -1
    

#### 输出样例：

    2
    20
    20
    20
    


```cpp

// Problem: 普通平衡树
// Contest: AcWing
// URL: https://www.acwing.com/problem/content/description/255/
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// Date: 2022-07-15 19:32:11
// 
// Powered by CP Editor (https://cpeditor.org)

/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/


#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 100010

using namespace std;

typedef long long ll;

int n,tot=0;
int op[MAXN],id[MAXN];
ll a[MAXN],b[MAXN];


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

int query_rank(int root,int l,int r)
{
    if(l<=tree[root].l&&r>=tree[root].r)
        return tree[root].dat;
    int mid=(tree[root].l+tree[root].r)/2;
    int res=0;
    if(l<=mid)
        res+=query_rank(2*root,l,r);
    if(r>mid)
        res+=query_rank(2*root+1,l,r);
    return res;
}


int k_th(int root,int pos)
{
    if(tree[root].l==tree[root].r)
        return tree[root].l;
    //int mid=(tree[root].l+tree[root].r)/2;
    if(pos<=tree[2*root].dat)
        return k_th(2*root,pos);
    else return k_th(2*root+1,pos-tree[2*root].dat);
    
    
}


int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %lld",&op[i],&a[i]);
        if(op[i]!=4)
            b[++tot]=a[i];
    }
    
    sort(b+1,b+tot+1);
    tot=unique(b+1,b+tot+1)-(b+1);
    
    //cout << tot << endl;
    
    build(1,1,tot);
    
    for(int i=1;i<=n;i++)
    {
        if(op[i]!=4)
            id[i]=lower_bound(b+1,b+tot+1,a[i])-b;
    }
    
    for(int i=1;i<=n;i++)
    {
        //cout << id[i]  << "***" << endl;
        if(op[i]==1)
            modify(1,id[i],1);
        else if(op[i]==2)
            modify(1,id[i],-1);
        else if(op[i]==3)
            printf("%d\n",query_rank(1,1,id[i]-1)+1);
        else if(op[i]==4)
            printf("%lld\n",b[k_th(1,a[i])]);
        else if(op[i]==5)
            printf("%lld\n",b[k_th(1,query_rank(1,1,id[i]-1))]);
        else if(op[i]==6)
            printf("%lld\n",b[k_th(1,query_rank(1,1,id[i])+1)]);
    }
    
    return 0;
}

```
