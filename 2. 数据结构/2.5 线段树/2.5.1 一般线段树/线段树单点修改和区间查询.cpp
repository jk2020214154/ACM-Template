//https://loj.ac/p/130

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
    ll dat;
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
        tree[root].dat=a[l];
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
        tree[root].dat+=val;
    else
    {
        int mid=(tree[root].l+tree[root].r)/2;
        if(pos<=mid)
            modify(2*root,pos,val);
        else modify(2*root+1,pos,val);
        pushup(root);
    }
}

ll query(int root,int l,int r)
{
    if(l<=tree[root].l&&r>=tree[root].r)
        return tree[root].dat;
    else
    {
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

}


int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        ll op,x,y;
        scanf("%lld %lld %lld",&op,&x,&y);
        if(op==1)
            modify(1,x,y);
        else 
            printf("%lld\n",query(1,x,y));
    }
    return 0;
}
