//https://loj.ac/p/132



#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 1000010

using namespace std;

typedef long long ll;

int n,q;
ll a[MAXN],C1[MAXN],C2[MAXN];

int lowbit(int x)//计算最低位的1及其后面所有的0表示的数值
{
	return x & -x;
}

void add(ll C[],int x,ll val)//单点修改
{
	for(int i=x;i<=n;i+=lowbit(i))
		C[i]+=val;
}

ll sum(ll C[],int x)//查询前缀和[1,x]
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
        add(C1,i,a[i]-a[i-1]);
        add(C2,i,(a[i]-a[i-1])*i);
    }
}

ll pre(int x)
{
    return (x+1)*sum(C1,x)-sum(C2,x);
}

int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    init();
    
    for(int i=1;i<=q;i++)
    {
        int op,l,r;
        ll x;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d %d %lld",&l,&r,&x);
            add(C1,l,x),add(C1,r+1,-x);
            add(C2,l,x*l),add(C2,r+1,-x*(r+1));
        }
        else if(op==2)
        {
            scanf("%d %d",&l,&r);
            printf("%lld\n",pre(r)-pre(l-1));
        }
    }
    
    return 0;
}
