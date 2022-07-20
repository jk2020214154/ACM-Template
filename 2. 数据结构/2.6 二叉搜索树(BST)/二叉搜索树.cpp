

#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 100010

using namespace std;

struct BST{
    int l,r;//左右子节点在数组中的下标
    int val;//结点关键码
}a[MAXN];//数组模拟链表

int tot,root,INF=1 << 30;

int New(int val)
{
    a[++tot].val=val;
    return tot;
}

void Build()
{
    New(-INF),New(INF);
    root=1,a[1].r=2;
}


int Get(int p,int val)
{
    if(p==0)//检索失败
        return 0;
    if(val==a[p].val)//检索成功
        return p;
    if(val<a[p].val)//遍历左子树
        return Get(a[p].l,val);
    else return Get(a[p].r,val);//遍历右子树
}


void Insert(int &p,int val)
{
    if(p==0)
    {
        p=New(val);//注意此处是引用,其父结点的l或r会被同时更新
        return ;
    }
    if(val==a[p].val)//存在相同元素,不作处理
        return ;
    if(val<a[p].val)//遍历左子树
        Insert(a[p].l,val);
    else Insert(a[p].r,val);//遍历右子树
}


int GetNext(int val){
    int ans=2;//初始化为INF的编号
    int p=root;//从根结点开始枚举
    while(p!=0){
        if(a[p].val==val){//检索成功
            if(a[p].r>0){//有右子树
                p=a[p].r;
                while(a[p].l>0)//右子树一直向左走
                    p=a[p].l;
                ans=p;
            }
            break;
        }
        //每经过一个结点,都尝试更新后继
        if(a[p].val>val&&a[p].val<a[ans].val)
            ans=p;
        if(val<a[p].val)//检索过程,访问左子树
            p=a[p].l;
        else p=a[p].r;//检索过程,访问右子树
    }
    return ans;
}

int GetPre(int val)
{
    int ans=1;//初始化为-INF的编号
    int p=root;//从根结点开始枚举
    while(p!=0){
        if(a[p].val==val){//检索成功
            if(a[p].l>0){//有左子树
                p=a[p].l;
                while(a[p].r>0)//左子树一直向右走
                    p=a[p].r;
                ans=p;
            }
            break;
        }
        //每经过一个结点,都尝试更新前驱
        if(a[p].val<val&&a[p].val>a[ans].val)
            ans=p;
        if(val<a[p].val)//检索过程,访问左子树
            p=a[p].l;
        else p=a[p].r;//检索过程,访问右子树
    }
    return ans;
}

void Remove(int &p,int val)//从子树p中删除值为val的结点
{
    if(p==0)//检索失败
        return ;
    if(a[p].val==val)//已经检索到值为val的结点
    {
        if(a[p].l==0)//没有左子树,有右子树
            p=a[p].r;//右子树代替p的位置,注意p是引用
        else if(a[p].r==0)//没有右子树,有左子树
            p=a[p].l;//左子树代替p的位置,注意p是引用
        else//既有左子树又有右子树
        {
            //求后继结点
            int next=a[p].r;
            while(a[next].l>0)
                next=a[next].l;
            //next一定没有左子树
            Remove(a[p].r,a[next].val);
            //让结点next代替结点p的位置
            a[next].l=a[p].l,a[next].r=a[p].r;
            p=next;//注意p是引用
        }
        return ;
    }
    if(val<a[p].val)//遍历左子树
        Remove(a[p].l,val);
    else Remove(a[p].r,val);//遍历右子树
}




void inorder(int p)
{
    if(a[p].l!=0)
        inorder(a[p].l);
    printf("%d %d***\n",p,a[p].val);
    printf("***%d %d***\n",a[p].l,a[p].r);
    if(a[p].r!=0)
        inorder(a[p].r);    
}


int main()
{
    //Build();
    Insert(root,5);
    Insert(root,2);
    Insert(root,9);
    Insert(root,-INF);    
    
    Insert(root,3);
    Insert(root,6);
    Insert(root,+INF);
    Insert(root,1);
    Insert(root,8);
    
    inorder(root);
    
    int pos=GetPre(0);
    
    printf("%d %d\n",pos,a[pos].val);
    
    Remove(root,5);
    
    inorder(root);
    
    return 0;
}
