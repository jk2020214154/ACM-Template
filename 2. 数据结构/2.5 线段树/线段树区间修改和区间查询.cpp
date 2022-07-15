//https://loj.ac/p/132


#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 1000010

using namespace std;

typedef long long ll;

int n,q;
ll a[MAXN];

struct Tree{
    int l;
    int r;
    ll sum;
    ll add;
}tree[4*MAXN];

void pushup(int root)
{
    tree[root].sum=tree[2*root].sum+tree[2*root+1].sum;
}

void pushdown(int root)
{
    if(tree[root].add)
    {
        tree[2*root].add+=tree[root].add;
        tree[2*root+1].add+=tree[root].add;
        tree[2*root].sum+=tree[root].add*(tree[2*root].r-tree[2*root].l+1);
        tree[2*root+1].sum+=tree[root].add*(tree[2*root+1].r-tree[2*root+1].l+1);
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
        tree[root].add+=val;
        tree[root].sum+=val*(tree[root].r-tree[root].l+1);
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
    if(r<=mid)
        return query(2*root,l,r);
    else if(l>mid)
        return query(2*root+1,l,r);
    else
    {
        ll sum=0;
        sum+=query(2*root,l,r);
        sum+=query(2*root+1,l,r);
        return sum;
    }
}



int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        int op,l,r;
        ll num;
        scanf("%d %d %d",&op,&l,&r);
        if(op==1)
        {
            scanf("%lld",&num);
            modify(1,l,r,num);
        }
        else if(op==2)
            printf("%lld\n",query(1,l,r));
    }


    return 0;
}
