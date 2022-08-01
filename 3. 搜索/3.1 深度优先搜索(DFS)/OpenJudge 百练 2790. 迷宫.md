[题目链接](http://bailian.openjudge.cn/practice/2790?lang=en_US)

### 描述
一天Extense在森林里探险的时候不小心走入了一个迷宫，迷宫可以看成是由n * n的格点组成，每个格点只有2种状态，.和#，前者表示可以通行后者表示不能通行。同时当Extense处在某个格点时，他只能移动到东南西北(或者说上下左右)四个方向之一的相邻格点上，Extense想要从点A走到点B，问在不走出迷宫的情况下能不能办到。如果起点或者终点有一个不能通行(为#)，则看成无法办到。
### 输入
第1行是测试数据的组数k，后面跟着k组输入。每组测试数据的第1行是一个正整数n (1 <= n <= 100)，表示迷宫的规模是n * n的。接下来是一个n * n的矩阵，矩阵中的元素为.或者#。再接下来一行是4个整数ha, la, hb, lb，描述A处在第ha行, 第la列，B处在第hb行, 第lb列。注意到ha, la, hb, lb全部是从0开始计数的。
### 输出
k行，每行输出对应一个输入。能办到则输出“YES”，否则输出“NO”。
### 样例输入
    2
    3
    .##
    ..#
    #..
    0 0 2 2
    5
    .....
    ###.#
    ..#..
    ###..
    ...#.
    0 0 4 0
### 样例输出
    YES
    NO

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define MAXN 110

using namespace std;

int t,n,vis[MAXN][MAXN];
int sx,sy,ex,ey;
char g[MAXN][MAXN];

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};//移动方向-->上右下左

/*
//也可以写成该种(只有上下左右)
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

//一个点周围一圈（左上、上、右上、右、右下、下、左下、左）
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

*/

int dfs(int x,int y)
{
    if(g[x][y]=='#')//当前点的位置不能通行
        return 0;
    if(x==ex&&y==ey)//该点到达终点位置坐标，返回1
        return 1;
    
    vis[x][y]=1;//每次标记当前点走过
    
    for(int i=0;i<=3;i++)
    {
        int dx=x+dir[i][0],dy=y+dir[i][1];//偏移位置坐标
        if(dx>=0&&dx<=n-1&&dy>=0&&dy<=n-1&&vis[dx][dy]==0)//判断当前位置合法且是否被访问过
            if(dfs(dx,dy))//能借助偏移位置到达终点，递归返回1
                return 1;
    }
    return 0;//所有情况都走过仍然无法到达终点，返回0
}

int main()
{
    cin >> t;
    while(t--)
    {
        scanf("%d\n",&n);
        memset(vis,0,sizeof(vis));
        for(int i=0;i<=n-1;i++)
            scanf("%s",g[i]);
        
        cin >> sx >> sy >> ex >> ey;

        if(dfs(sx,sy)==1)
            printf("YES\n");
        else printf("NO\n");
    }    
    return 0;
}

```