
[题目链接](https://www.acwing.com/problem/content/2808/)


假设你有一条长度为 $5$ 的木版，初始时没有涂过任何颜色。

你希望把它的 $5$ 个单位长度分别涂上红、绿、蓝、绿、红色，用一个长度为 $5$ 的字符串表示这个目标：`RGBGR`。

每次你可以把一段连续的木版涂成一个给定的颜色，后涂的颜色覆盖先涂的颜色。

例如第一次把木版涂成 `RRRRR`，第二次涂成 `RGGGR`，第三次涂成 `RGBGR`，达到目标。

用尽量少的涂色次数达到目标。

#### 输入格式

输入仅一行，包含一个长度为 $n$ 的字符串，即涂色目标。

字符串中的每个字符都是一个大写字母，不同的字母代表不同颜色，相同的字母代表相同颜色。

#### 输出格式

仅一行，包含一个数，即最少的涂色次数。

#### 数据范围

$1 \\le n \\le 50$

#### 输入样例1：

    AAAAA
    

#### 输出样例1：

    1
    

#### 输入样例2：

    RGBGR
    

#### 输出样例2：

    3
    
 ```cpp
 
 #include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 55

using namespace std;


const int inf=0x3f3f3f3f;

int f[MAXN][MAXN];
char s[MAXN];


int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            f[i][j]=inf;
        f[i][i]=1;
    }
    
    for(int len=2;len<=n;len++)
        for(int l=1;l+len-1<=n;l++)
        {
            int r=l+len-1;
            if(s[l]==s[r])
                f[l][r]=min(f[l+1][r],f[l][r-1]);
            else if(s[l]!=s[r])
            {
                for(int k=l;k<r;k++)
                    f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]); 
            }
        }
    
    printf("%d\n",f[1][n]);
    
    return 0;
}


```
