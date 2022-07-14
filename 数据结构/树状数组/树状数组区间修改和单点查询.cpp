//https://loj.ac/p/131

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 1000010

using namespace std;

typedef long long ll;

int n,q;
ll a[MAXN],C[MAXN],pre[MAXN];

int lowbit(int x)//计算最低位的1及其后面所有的0表示的数值
{
	return x & -x;
}

void add(int x,ll val)//单点修改
{
	for(int i=x;i<=n;i+=lowbit(i))
		C[i]+=val;
}

ll sum(int x)//查询前缀和[1,x]
{
	ll res=0;
	for(int i=x;i>=1;i-=lowbit(i))
		res+=C[i];
	return res;
}

void init()
{
    for(int i=1;i<=n;i++)
    {
        add(i,a[i]-a[i-1]);
    }
}

int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    init();
    
    for(int i=1;i<=q;i++)
    {
        int op,l,r,pos;
        ll x;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d %d %lld",&l,&r,&x);
            add(l,x),add(r+1,-x);
        }
        else if(op==2)
        {
            scanf("%d",&pos);
            printf("%lld\n",sum(pos));
        }
    }
    
    return 0;
}
