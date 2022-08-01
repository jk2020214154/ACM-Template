

[题目链接](https://www.acwing.com/problem/content/329/)


农夫约翰的土地由 $M \\times N$ 个小方格组成，现在他要在土地里种植玉米。

非常遗憾，部分土地是不育的，无法种植。

而且，相邻的土地不能同时种植玉米，也就是说种植玉米的所有方格之间都不会有公共边缘。

现在给定土地的大小，请你求出共有多少种种植方法。

土地上什么都不种也算一种方法。

#### 输入格式

第 $1$ 行包含两个整数 $M$ 和 $N$。

第 $2..M+1$ 行：每行包含 $N$ 个整数 $0$ 或 $1$，用来描述整个土地的状况，$1$ 表示该块土地肥沃，$0$ 表示该块土地不育。

#### 输出格式

输出总种植方法对 $10^8$ 取模后的值。

#### 数据范围

$1 \\le M,N \\le 12$

#### 输入样例：

    2 3
    1 1 1
    0 1 0
    

#### 输出样例：

    9

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 15
#define MAXM (1<<12)

using namespace std;


const int mod=1e8;

int m,n;
int g[MAXN];

int f[MAXN][MAXM];

vector<int> state;
vector<int> pre[MAXM];


int check(int x)
{
    for(int i=0;i<n;i++)
        if(((x>>i)&1)&&((x>>(i+1))&1))
            return 0;
    return 1;
}

int main()
{
    scanf("%d %d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<=n-1;j++)
        {
            int temp;
            scanf("%d",&temp);
            if(temp==0)
                g[i]+=(1<<j);
        }
    }
    /*
    for(int i=1;i<=n;i++)
        printf("%d\n",g[i]);*/
    
    for(int i=0;i<(1<<n);i++)
        if(check(i)==1)
            state.push_back(i);
    
    for(int i=0;i<state.size();i++)
        for(int j=0;j<state.size();j++)
        {
            int a=state[i],b=state[j];
            if((a&b)==0)
                pre[i].push_back(j);
        }
        
    f[0][0]=1;
    for(int i=1;i<=m;i++)
        for(int a=0;a<state.size();a++)
            for(int b=0;b<pre[a].size();b++)
            {
                if((g[i]&state[a])==0)
                    f[i][state[a]]=(f[i][state[a]]+f[i-1][state[pre[a][b]]])%mod;
            }
    
    int res=0;
    for(int i=0;i<state.size();i++)
    {
        if((g[m]&state[i])==0)
            res=(res+f[m][state[i]])%mod;
    }
    printf("%d\n",res);
    //printf("%d\n",f[m+1][0]);
    
    return 0;
}


```
