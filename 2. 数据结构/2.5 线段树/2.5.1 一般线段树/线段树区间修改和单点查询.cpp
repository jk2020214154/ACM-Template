//https://loj.ac/p/131

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
        tree[root].sum=a[l];
        tree[root].add=0;
        return ;
    }
    int mid=(l+r)/2;
    build(2*root,l,mid);
    build(2*root+1,mid+1,r);
    pushup(root);
}

void modify(int root,int l,int r,int val)
{
    if(l<=tree[root].l&&r>=tree[root].r)
    {
        tree[root].sum+=(tree[root].r-tree[root].l+1)*val;
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

ll query(int root,int pos)
{
    if(tree[root].l==pos&&tree[root].r==pos)
        return tree[root].sum;
    pushdown(root);
    int mid=(tree[root].l+tree[root].r)/2;
    if(pos<=mid)
        return query(2*root,pos);
    else return query(2*root+1,pos);
}


int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int l,r;
            ll val;
            scanf("%d %d %lld",&l,&r,&val);
            modify(1,l,r,val);
        }
        else if(op==2)
        {
            int pos;
            scanf("%d",&pos);
            printf("%lld\n",query(1,pos));
        }
    }
    return 0;
}
