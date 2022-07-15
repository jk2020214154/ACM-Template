#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int n,fac[10];

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


int main()
{
    char a[10];
    init();
    scanf("%d",&n);
    scanf("%s",a);
    printf("%d\n",cantor(n,a));
    return 0;
}
