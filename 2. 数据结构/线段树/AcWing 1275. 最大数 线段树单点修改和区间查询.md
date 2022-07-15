#### [题目链接](https://www.acwing.com/problem/content/1277/)


给定一个正整数数列 $a\_1,a\_2,…,a\_n$，每一个数都在 $0 \\sim p-1$ 之间。

可以对这列数进行两种操作：

1.  添加操作：向序列后添加一个数，序列长度变成 $n+1$；
2.  询问操作：询问这个序列中最后 $L$ 个数中最大的数是多少。

程序运行的最开始，整数序列为空。

一共要对整数序列进行 $m$ 次操作。

写一个程序，读入操作的序列，并输出询问操作的答案。

#### 输入格式

第一行有两个正整数 $m,p$，意义如题目描述；

接下来 $m$ 行，每一行表示一个操作。

如果该行的内容是 `Q L`，则表示这个操作是询问序列中最后 $L$ 个数的最大数是多少；

如果是 `A t`，则表示向序列后面加一个数，加入的数是 $(t+a)\\ mod\\ p$。其中，$t$ 是输入的参数，$a$ 是在这个添加操作之前最后一个询问操作的答案（如果之前没有询问操作，则 $a=0$）。

第一个操作一定是添加操作。对于询问操作，$L>0$ 且不超过当前序列的长度。

#### 输出格式

对于每一个询问操作，输出一行。该行只有一个数，即序列中最后 $L$ 个数的最大数。

#### 数据范围

$1 \\le m \\le 2 \\times 10^5$,  
$1 \\le p \\le 2 \\times 10^9$,  
$0 \\le t < p$

#### 输入样例：

    10 100
    A 97
    Q 1
    Q 1
    A 17
    Q 2
    A 63
    Q 1
    Q 1
    Q 3
    A 99
    

#### 输出样例：

    97
    97
    97
    60
    60
    97
    

#### 样例解释

最后的序列是 $97,14,60,96$。


```cpp
    #include <iostream>
    #include <cstring>
    #include <algorithm>

    #define MAXN 200010


    using namespace std;

    typedef long long ll;
    int m;
    ll p;


    struct Tree{
    int l;
    int r;
    ll dat;
    }tree[4*MAXN];

    void pushup(int root)
    {
    tree[root].dat=max(tree[2*root].dat,tree[2*root+1].dat);
    // tree[root].dat=max(tree[root << 1].dat,tree[root << 1 | 1].dat);
    }


    void build(int root,int l,int r)
    {
    tree[root].l=l,tree[root].r=r;
    if(l==r)//叶子结点
    return ;
    int mid=(l+r)/2;
    // int mid= l + r >> 1;//由于+的优先级大于>>,故会先算l+r,再右移
    build(2*root,l,mid);
    // build(root << 1,l,mid);
    build(2*root+1,mid+1,r);
    // build(root << 1 | 1,mid+1,r);
    }


    void modify(int root,int pos,ll val)//单点修改
    {
    if(tree[root].l==pos&&tree[root].r==pos)
    tree[root].dat=val;
    else
    {
    int mid=(tree[root].l+tree[root].r)/2;
    // int mid=tree[root].l+tree[root].r >> 1;
    if(pos<=mid)
        modify(2*root,pos,val);
        // modify(root << 1,pos,val);
    else 
        modify(2*root+1,pos,val);
        // modify(root << 1 | 1,pos,val);

    pushup(root);
    }
    }


    ll query(int root,int l,int r)
    {
    if(l<=tree[root].l&&r>=tree[root].r)
    return tree[root].dat;

    int mid=(tree[root].l+tree[root].r)/2;
    // int mid=tree[root].l+tree[root].r >> 1;

    ll res=0;
    if(l<=mid)
    res=max(res,query(2*root,l,r));
    // res=max(res,query(root << 1,l,r));
    if(r>mid)
    res=max(res,query(2*root+1,l,r));
    // res=max(res,query(root << 1 | 1,l,r));
    return res;

    }




    int main()
    {
    ll cnt=0,last=0;
    scanf("%d %lld\n",&m,&p);
    build(1,1,m);
    for(int i=1;i<=m;i++)
    {
    ll num;
    char op;
    scanf("%c %lld ",&op,&num);
    if(op=='Q')
    {
        last=query(1,cnt-num+1,cnt);
        printf("%lld\n",last);
    }
    else if(op=='A')
    {
        modify(1,cnt+1,(num+last)%p);
        cnt++;
    }


    }
    return 0;
    }

```
