[题目链接](https://www.acwing.com/problem/content/description/255/)

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
 #include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

const int inf=0x3f3f3f3f;

int n;

struct Tree{
    int fa;//fa表示该点的父结点
    int son[2];//son[0]表示该点的左儿子,son[1]表示该点的右儿子
    int cnt;//cnt表示该点在树上出现的次数
    int siz;//siz表示以该点为根的子树的大小
    int val;//val表示该点的权值
}tree[MAXN];

int root,tot;

void pushup(int x)//上传操作
{
    tree[x].siz=tree[tree[x].son[0]].siz+tree[tree[x].son[1]].siz+tree[x].cnt;
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
    while(tree[x].fa!=goal)//一直旋转到x成为goal的儿子
    {
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
}

void Find(int x)//查找x的位置,并将其旋转至根结点
{
    int p=root;//从根结点出发
    if(p==0)//树是空树
        return ;
    while(tree[p].son[x>tree[p].val]&&x!=tree[p].val)
        p=tree[p].son[x>tree[p].val];
    //直到检索到x=tree[p].val停止,
    //否则如果x>tree[p].val,在右子树查找,如果x<tree[p].val在左子树查找
    splay(p,0);
}

void Insert(int x)
{
    int p=root,fa=0;//从根结点p出发,p的父结点为fa
    while(p!=0&&x!=tree[p].val)//当p存在并且没有移动到当前的值
    {
        fa=p;//p向下走,fa变为p
        p=tree[p].son[x>tree[p].val];//若大于则在右子树查找,反之则在左子树查找
    }
    if(p!=0)//存在该值的位置
        tree[p].cnt++;//计数+1
    else//不存在该值的位置,新建一个结点保存
    {
        p=++tot;//新节点的位置
        if(fa!=0)//如果父结点非根
            tree[fa].son[x>tree[fa].val]=p;
        tree[p].son[0]=tree[p].son[1]=0;//新建的点不存在儿子
        tree[p].fa=fa;//更新父结点
        tree[p].val=x;//更新权值
        tree[p].cnt=1;//更新数量
        tree[p].siz=1;//更新以该点为根的子树的大小
    }
    splay(p,0);//把当前位置移到根,保证结构的平衡
}


int Pre_Next(int x,int state)//查询前驱和后继合并,state=0(找前驱),state=1(找后继)
{
    Find(x);//将x旋转至根结点
    int p=root;//从根结点出发
    //由于x可能不在树上,find函数找到是最接近x的点,故root可能是x的前驱或者后继
    if(tree[p].val>x&&state==1)//p(root)为后继
        return p;
    if(tree[p].val<x&&state==0)//p(root)为前驱
        return p;
    
    p=tree[root].son[state];//前驱到达它的左儿子,后继到达它的右儿子
    
    //前驱到达左儿子然后沿着该左儿子的右边一直走
    //后继到达右儿子然后沿着该右儿子的左边一直走
    while(tree[p].son[state^1]!=0)
        p=tree[p].son[state^1];
    return p;
}


void Remove(int x)//删除x
{
    int last=Pre_Next(x,0);//查找x的前驱
    int nex=Pre_Next(x,1);//查找x的后继
    splay(last,0),splay(nex,last);
    //将前驱旋转到根结点,后继旋转到根结点的下面
    //此时后继是前驱的右儿子,x是后继的左儿子,并且x是叶子结点
    int k=tree[nex].son[0];//后继的左儿子
    if(tree[k].cnt>1)//如果个数超过一个
    {
        tree[k].cnt--;//计数-1
        splay(k,0);//旋转
    }
    else tree[nex].son[0]=0;//这个结点直接丢掉(不存在)
}


int kth(int x)//查询排名为x的数
{
    int p=root;
    if(tree[p].siz<x)//当前树上无这么多数
        return 0;//不存在
    while(1)
    {
        int y=tree[p].son[0];//左儿子
        if(x>tree[y].siz+tree[p].cnt)//如果排名比左儿子的大小与当前结点的数量要大,去右儿子找
        {
            x-=tree[y].siz+tree[p].cnt;
            p=tree[p].son[1];
        }
        else //否则的话在当前结点或者左儿子查找
        {
            if(x<=tree[y].siz)//在左儿子上找
                p=y;
            else return tree[p].val;//否则就在当前结点上
        }
    }
}


int main()
{
    scanf("%d",&n);
    Insert(inf);
    Insert(-inf);
    for(int i=1;i<=n;i++)
    {
        int op,num;
        scanf("%d %d",&op,&num);
        if(op==1)//插入数值num
            Insert(num);
        else if(op==2)//删除数值num
            Remove(num);
        else if(op==3)//查询数值num的排名
        {
            Find(num);
            printf("%d\n",tree[tree[root].son[0]].siz);
            //有哨兵,故结果不需要再+1
        }
        else if(op==4)//查询排名为num的数值
            printf("%d\n",kth(num+1));
        else if(op==5)//求数值num的前驱
            printf("%d\n",tree[Pre_Next(num,0)].val);
        else if(op==6)//求数值num的后继
            printf("%d\n",tree[Pre_Next(num,1)].val);        
        
    }
    
    
    
    return 0;
}

```
