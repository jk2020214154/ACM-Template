[题目链接](https://www.acwing.com/problem/content/845/)


$n-$皇后问题是指将 $n$ 个皇后放在 $n \\times n$ 的国际象棋棋盘上，使得皇后不能相互攻击到，即任意两个皇后都不能处于同一行、同一列或同一斜线上。

![1_597ec77c49-8-queens.png](https://cdn.acwing.com/media/article/image/2019/06/08/19_860e00c489-1_597ec77c49-8-queens.png)

现在给定整数 $n$，请你输出所有的满足条件的棋子摆法。

#### 输入格式

共一行，包含整数 $n$。

#### 输出格式

每个解决方案占 $n$ 行，每行输出一个长度为 $n$ 的字符串，用来表示完整的棋盘状态。

其中 `.` 表示某一个位置的方格状态为空，`Q` 表示某一个位置的方格上摆着皇后。

每个方案输出完成后，输出一个空行。

**注意：行末不能有多余空格。**

输出方案的顺序任意，只要不重复且没有遗漏即可。

#### 数据范围

$1 \\le n \\le 9$

#### 输入样例：

    4
    

#### 输出样例：

    .Q..
    ...Q
    Q...
    ..Q.
    
    ..Q.
    Q...
    ...Q
    .Q..


#### dfs按行枚举，时间复杂度为$O(n!)$

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 10

using namespace std;

int n;
char g[MAXN][MAXN];
int col[MAXN],dg[2*MAXN],udg[2*MAXN];//注意对角线和反对角线是2倍的空间

void dfs(int x)
{
    if(x==n)//表示已搜完n行,输出结果
    {
        for(int i=0;i<=n-1;i++)
            printf("%s\n",g[i]);
        printf("\n");
        return ;
    }
    
    for(int y=0;y<=n-1;y++)
        if(col[y]==0&&dg[y+x]==0&&udg[y-x+n]==0)//当前列和对角线和反对角线都未访问
        {
            g[x][y]='Q';
            col[y]=dg[y+x]=udg[y-x+n]=1;
            dfs(x+1);
            col[y]=dg[y+x]=udg[y-x+n]=0;//恢复现场
            g[x][y]='.';
        }
    
}

int main()
{
    cin >> n;
    
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<=n-1;j++)
            g[i][j]='.';
    dfs(0);
    
    return 0;
}

```


#### dfs按每个元素枚举,时间复杂度为$O(2^{n^2})$


```cpp

#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 10

using namespace std;


int n;
char g[MAXN][MAXN];
int row[MAXN],col[MAXN],dg[2*MAXN],udg[2*MAXN];//注意对角线和反对角线是2倍的空间

void dfs(int x,int y,int cnt)//cnt表示放上皇后的个数
{
    if(y==n)
        y=0,x++;
    if(x==n)
    {
        if(cnt==n)
        {
            for(int i=0;i<=n-1;i++)
                printf("%s\n",g[i]);
            printf("\n");
        }
        return ;
    }
    
    //放皇后(当前位置)
    if(row[x]==0&&col[y]==0&&dg[x+y]==0&&udg[y-x+n]==0)
    {
        g[x][y]='Q';
        row[x]=col[y]=dg[x+y]=udg[y-x+n]=1;
        dfs(x,y+1,cnt+1);
        row[x]=col[y]=dg[x+y]=udg[y-x+n]=0;//恢复现场
        g[x][y]='.';
    }
    
    //不放皇后（当前位置）
    dfs(x,y+1,cnt);
    
}


int main()
{
    cin >> n;
    
    for(int i=0;i<=n-1;i++)
        for(int j=0;j<=n-1;j++)
            g[i][j]='.';
    
    dfs(0,0,0);
    
    return 0;
}

```

