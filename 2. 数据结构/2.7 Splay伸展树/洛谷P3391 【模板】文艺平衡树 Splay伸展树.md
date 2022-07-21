[题目链接](https://www.luogu.com.cn/problem/P3391)


# 【模板】文艺平衡树

## 题目描述

您需要写一种数据结构（可参考题目标题），来维护一个有序数列。  

其中需要提供以下操作：翻转一个区间，例如原有序序列是 $5\ 4\ 3\ 2\ 1$，翻转区间是 $[2,4]$ 的话，结果是 $5\ 2\ 3\ 4\ 1$。

## 输入格式

第一行两个正整数 $n,m$，表示序列长度与操作个数。序列中第 $i$ 项初始为 $i$。  
接下来 $m$ 行，每行两个正整数 $l,r$，表示翻转的区间。

## 输出格式

输出一行 $n$ 个正整数，表示原始序列经过 $m$ 次变换后的结果。

## 样例 #1

### 样例输入 #1

```
5 3
1 3
1 3
1 4
```

### 样例输出 #1

```
4 3 2 1 5
```

## 提示

【数据范围】  
对于 $100\%$ 的数据，$1 \le n, m \leq 100000 $，$1 \le l \le r \le n$。


```cpp
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


int n,m;

struct Tree{
    int fa;//fa表示该点的父结点
    int son[2];//son[0]表示该点的左儿子,son[1]表示该点的右儿子
    int siz;//siz表示以该点为根的子树的大小
    int val;//val表示该点的权值
    int flag;//翻转区间标记
}tree[MAXN];

int root,tot;

void pushup(int x)
{
    tree[x].siz=tree[tree[x].son[0]].siz+tree[tree[x].son[1]].siz+1;
}

void pushdown(int x)
{
    if(tree[x].flag)
    {
        swap(tree[x].son[0],tree[x].son[1]);
        tree[tree[x].son[0]].flag^=1;
        tree[tree[x].son[1]].flag^=1;
        tree[x].flag=0;
    }
}

void rotate(int x)//旋转操作(涵盖左旋和右旋)
{
    int y=tree[x].fa;//y是x的父结点
    int z=tree[y].fa;//z是y的父结点,即z是x的祖父结点
    int k=tree[y].son[1]==x;//判断x是y的哪一个儿子,k=0表示左儿子,k=1表示右儿子
    tree[z].son[tree[z].son[1]==y]=x;//z的原来y的位置变为x
    tree[x].fa=z;//x的父结点修改为z
    tree[y].son[k]=tree[x].son[k^1];
    //若x是y的左儿子(k=0),则让y的左儿子(k=0)等于x原来的右儿子(k^1)
    //若x是y的右儿子(k=1),则上y的右儿子(k=1)等于x原来的左儿子(k^1)
    tree[tree[x].son[k^1]].fa=y;//更新x原来的(k^1)儿子的父结点为y
    tree[x].son[k^1]=y;//更新x的(k^1)儿子为y
    tree[y].fa=x;//更新y的父结点x
    pushup(y),pushup(x);//上传操作
}


void splay(int x,int goal)//将x旋转为goal的儿子,如果goal是0,则旋转至根
{
    //cout << "wwww" << endl;
    while(tree[x].fa!=goal)//一直旋转到x成为goal的儿子
    {
        //cout << "wwww" << endl;
        int y=tree[x].fa;//y是x的父结点
        int z=tree[y].fa;//z是y的父结点,即z是x的祖父结点
        if(z!=goal)//x的祖先结点z不是目标
        {
            if((tree[y].son[1]==x)^(tree[z].son[1]==y))
                rotate(x);//折线型先旋转x
            else rotate(y);//共线型先旋转y
        }
        rotate(x);//(无论前面是什么类型)都再旋转x
    }
    if(goal==0)//如果goal是0,则将根结点更新为x
        root=x;
    //cout << "wc" << endl;
}


void Insert(int x)
{
   int p=root,fa=0;//从根结点p出发,p的父结点为fa
   while(p!=0)//当p存在并且没有移动到当前的值
   {
       fa=p;//p向下走,fa变为p
       p=tree[p].son[x>tree[p].val];//若大于则在右子树查找,反之则在左子树查找
   }
   p=++tot;//新节点的位置
   if(fa!=0)//如果父结点非根
       tree[fa].son[x>tree[fa].val]=p;
   tree[p].son[0]=tree[p].son[1]=0;//新建的点不存在儿子
   tree[p].fa=fa;//更新父结点
   tree[p].val=x;//更新权值
   tree[p].siz=1;//更新以该点为根的子树的大小
   splay(p,0);//把当前位置移到根,保证结构的平衡
}

int kth(int x)//查询排名为x的位置
{
    int p=root;
    if(tree[p].siz<x)//当前树上无这么多数
        return 0;//不存在
    while(1)
    {
        pushdown(p);
        if(x<=tree[tree[p].son[0]].siz)//左儿子
            p=tree[p].son[0];
        else if(x>tree[tree[p].son[0]].siz+1)//右儿子
        {
            x-=tree[tree[p].son[0]].siz+1;
            p=tree[p].son[1];
        }
        else return p;//当前结点
    }
}

void inorder(int p)
{
    pushdown(p);
    if(tree[p].son[0])
        inorder(tree[p].son[0]);
    if(tree[p].val>=1&&tree[p].val<=n)
        printf("%d ",tree[p].val);
    if(tree[p].son[1])
        inorder(tree[p].son[1]);
}


int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n+1;i++)//添加0和n+1的哨兵
        Insert(i);
    //inorder(root);
    //cout << "?" << endl;
    for(int i=1;i<=m;i++)
    {
        int  l,r;
        scanf("%d %d",&l,&r);
        l=kth(l),r=kth(r+2);
        //cout << l << " " << r << "..." << endl;
        //存在哨兵,查询l的前驱l-1,由于存在哨兵,即查询kth(l-1+1)的值
        //同理,查询r的后继r+1,由于存在哨兵,即查询kth(r+1+1)的值
        splay(l,0);
        splay(r,l);
        //cout << "?" << endl;
        tree[tree[r].son[0]].flag^=1;

    }
    //cout << "?" << endl;
    inorder(root);
    
    return 0;
}

```
