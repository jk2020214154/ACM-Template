[题目链接](https://www.acwing.com/problem/content/294/)


司令部的将军们打算在 $N \\times M$ 的网格地图上部署他们的炮兵部队。

一个 $N \\times M$ 的地图由 $N$ 行 $M$ 列组成，地图的每一格可能是山地（用 `H` 表示），也可能是平原（用 `P` 表示），如下图。

在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：

 ![](https://cdn.luogu.com.cn/upload/pic/1881.png) 

如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。

图上其它白色网格均攻击不到。

从图上可见炮兵的攻击范围不受地形的影响。

现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。

#### 输入格式

第一行包含两个由空格分割开的正整数，分别表示 $N$ 和 $M$；

接下来的 $N$ 行，每一行含有连续的 $M$ 个字符(`P` 或者 `H`)，中间没有空格。按顺序表示地图中每一行的数据。

#### 输出格式

仅一行，包含一个整数 $K$，表示最多能摆放的炮兵部队的数量。

#### 数据范围

$N \\le 100,M \\le 10$

#### 输入样例：

    5 4
    PHPP
    PPHH
    PPPP
    PHPP
    PHHP
    

#### 输出样例：

    6
    
    

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 110
#define MAXM 15
#define MAXK (1<<10)

using namespace std;


int n,m;

char g[MAXN][MAXM];
int gg[MAXN],cnt[MAXK];
vector<int> state;

int f[MAXN][MAXK][MAXK];




int check(int x)
{
    for(int i=0;i<m;i++)
        if((x>>i&1)&&((x>>(i+1)&1)||(x>>(i+2)&1)))
            return 0;
    return 1;
}

int count(int x)
{
    int res=0;
    for(int i=0;i<m;i++)
        if(x>>i&1)
            res++;
    return res;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",g[i]);
        for(int j=0;j<m;j++)
            if(g[i][j]=='H')
                gg[i]+=1<<j;
    }
    
    for(int i=0;i<1<<m;i++)
        if(check(i)==1)
        {
            state.push_back(i);
            cnt[i]=count(i);
        }
        
    for(int i=1;i<=n+2;i++)
    {
        for(int j=0;j<state.size();j++)//枚举i-1的状态
            for(int k=0;k<state.size();k++)//枚举i的状态
                for(int u=0;u<state.size();u++)//枚举i-2的状态
                {
                    int a=state[j],b=state[k],c=state[u];
                    if((a&b)==0&&(a&c)==0&&(b&c)==0&&(gg[i-1]&a)==0&&(gg[i]&b)==0)
                        f[i&1][j][k]=max(f[i&1][j][k],f[(i-1)&1][u][j]+cnt[b]);
                }
    }
    
    printf("%d\n",f[(n+2)&1][0][0]);
    return 0;
}

```

