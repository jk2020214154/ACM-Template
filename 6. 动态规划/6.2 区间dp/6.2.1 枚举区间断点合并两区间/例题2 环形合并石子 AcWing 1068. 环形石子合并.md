
[题目链接](https://www.acwing.com/problem/content/1070/)


将 $n$ 堆石子绕圆形操场排放，现要将石子有序地合并成一堆。

规定每次只能选相邻的两堆合并成新的一堆，并将新的一堆的石子数记做该次合并的得分。

请编写一个程序，读入堆数 $n$ 及每堆的石子数，并进行如下计算：

*   选择一种合并石子的方案，使得做 $n-1$ 次合并得分总和最大。
*   选择一种合并石子的方案，使得做 $n-1$ 次合并得分总和最小。

#### 输入格式

第一行包含整数 $n$，表示共有 $n$ 堆石子。

第二行包含 $n$ 个整数，分别表示每堆石子的数量。

#### 输出格式

输出共两行：

第一行为合并得分总和最小值，

第二行为合并得分总和最大值。

#### 数据范围

$1 \\le n \\le 200$

#### 输入样例：

    4
    4 5 9 4
    

#### 输出样例：

    43
    54
    
    
 ```cpp


#include<iostream>
#include<algorithm>
#include<cstring>

#define MAXN 410

using namespace std;


const int inf=0x3f3f3f3f;

int n,a[MAXN];

int f[MAXN][MAXN];
int g[MAXN][MAXN];
int sum[MAXN];


int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n;i++)
        sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=2*n;i++)
    {
        for(int j=1;j<=2*n;j++)
            f[i][j]=inf,g[i][j]=-inf;
        f[i][i]=g[i][i]=0;
    }
    for(int len=2;len<=n;len++)
        for(int l=1;l+len-1<=2*n;l++)
        {
            int r=l+len-1;
            for(int k=l;k<r;k++)
            {
                f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+sum[r]-sum[l-1]);
                g[l][r]=max(g[l][r],g[l][k]+g[k+1][r]+sum[r]-sum[l-1]);
                
            }
        }
    
    
    int res1=inf,res2=-inf;
    for(int i=1;i<=n;i++)
    {
        res1=min(res1,f[i][n+i-1]);
        res2=max(res2,g[i][n+i-1]);
    }
    
     printf("%d\n",res1);
     printf("%d\n",res2);
    
    return 0;
}


```
