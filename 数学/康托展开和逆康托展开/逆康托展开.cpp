#include<iostream>
#include<algorithm>
#include<cstring>

#define MAXN 110

using namespace std;

int n,k,fac[10];
int vis[MAXN],res[MAXN];

void init()//初始化
{
    fac[0]=1;
    //递推求阶乘
    for(int i=1;i<=9;i++)
        fac[i]=fac[i-1]*i;
}

int cantor(int n,char a[])//n表示个数,a[]表示该排列顺序
{
    int res=0;
    for(int i=0;i<=n-1;i++)
    {
        int cnt=0;
        //内循环作用:找到a[i]是当前数列中未出现的数中的第几小
        for(int j=i+1;j<=n-1;j++)
            if(a[j]<a[i])
                cnt++;
        
        res+=cnt*(fac[n-1-i]);
    }
    return res+1;
    //如果输出的是排名就要+1,普通的话就直接返回res即可
}

void incantor(int n,int x)
{    
    x--;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n-1;i++)
    {
        int cnt=x/fac[n-1-i];//比ai小且没有出现过的数的个数
        x%=fac[n-i-1];//更新x
        for(int j=1;j<=n;j++)//找到对于的ai,从1开始寻找
        {
            if(vis[j]==1)//被标记，就跳过
                continue;
            if(cnt==0)//cnt==0代表当前数就是ai
            {
                vis[j]=1;//标记
                res[i]=j;
                break;
            }
            cnt--;
        }
    }
}


int main()
{
    char a[10];
    init();
    /*scanf("%d",&n);
    scanf("%s",a);
    printf("%d\n",cantor(n,a));*/
    
    scanf("%d %d",&n,&k);

    incantor(n,k);
    for(int i=0;i<=n-1;i++)
        printf("%d ",res[i]);
    return 0;
}
