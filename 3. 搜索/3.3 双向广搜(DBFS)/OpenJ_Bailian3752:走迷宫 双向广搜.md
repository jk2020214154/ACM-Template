#### [题目链接](http://bailian.openjudge.cn/practice/3752/)



#### 描述
一个迷宫由R行C列格子组成，有的格子里有障碍物，不能走；有的格子是空地，可以走。
给定一个迷宫，求从左上角走到右下角最少需要走多少步(数据保证一定能走到)。只能在水平方向或垂直方向走，不能斜着走。
输入
第一行是两个整数，Ｒ和Ｃ，代表迷宫的长和宽。（ 1<= R，C <= 40)
接下来是Ｒ行，每行Ｃ个字符，代表整个迷宫。
空地格子用'.'表示，有障碍物的格子用'#'表示。
迷宫左上角和右下角都是'.'。
输出
输出从左上角走到右下角至少要经过多少步（即至少要经过多少个空地格子）。计算步数要包括起点和终点。
#### 样例输入
    5 5
    ..###
    #....
    #.#.#
    #.#.#
    #.#..
#### 样例输出
    9
    
   
#### 两个方向交替扩展
```cpp
//走迷宫   两个方向交替扩展

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN=50;

typedef pair<int,int> PII;

int n,m;
int dist[MAXN][MAXN],vis[MAXN][MAXN];
char g[MAXN][MAXN];

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

queue<PII> Q1,Q2;

int found;

void BFS_expand(queue<PII>& Q,int flag)
{
    PII s=Q.front();
    Q.pop();
    for(int i=0;i<=3;i++)
    {
        int dx=s.first+dir[i][0],dy=s.second+dir[i][1];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&g[dx][dy]!='#')
        {
            if(flag==1)
            {
                if(vis[dx][dy]!=1)
                {
                    if(vis[dx][dy]==2)
                    {
                        dist[s.first][s.second]+=dist[dx][dy],found=1;
                        return ;
                    }
                    vis[dx][dy]=1;Q.push({dx,dy});
                    dist[dx][dy]=dist[s.first][s.second]+1;
                }
            }
            else
            {
                if(vis[dx][dy]!=2)
                {
                    if(vis[dx][dy]==1)
                    {
                        dist[s.first][s.second]+=dist[dx][dy],found=1;
                        return ;    
                    }      
                    vis[dx][dy]=2;Q.push({dx,dy});
                    dist[dx][dy]=dist[s.first][s.second]+1;                              
                }
            }
        }
    }
}

int dbfs()
{
    found=-1;
    memset(vis,0,sizeof(vis));
    while(Q1.size()>0)
        Q1.pop();
    while(Q2.size()>0)
        Q2.pop();
    vis[1][1]=1,vis[n][m]=2;
    Q1.push({1,1});Q2.push({n,m});//Q2.push(make_pair{n,m});
    dist[1][1]=dist[n][m]=0;
    while(Q1.size()>0||Q2.size()>0)
    {
        PII temp;
        if(Q1.size()>0)
            temp=Q1.front(),BFS_expand(Q1,1);
        if(found==1)
            return dist[temp.first][temp.second]+2;
        if(Q2.size()>0)
            temp=Q2.front(),BFS_expand(Q2,0);
        if(found==1)
            return dist[temp.first][temp.second]+2;
    }
    return -1;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",g[i]+1);
    int res=dbfs();
    printf("%d\n",res);
    return 0;
}

```

#### 选择结点个数较少的那个方向先扩展

```cpp
//走迷宫   选择结点个数较少的那个方向先扩展

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN=50;

typedef pair<int,int> PII;

int n,m;
int dist[MAXN][MAXN],vis[MAXN][MAXN];
char g[MAXN][MAXN];

int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

queue<PII> Q1,Q2;



int dbfs()
{
    int flag;
    memset(vis,0,sizeof(vis));
    while(Q1.size()>0)
        Q1.pop();
    while(Q2.size()>0)
        Q2.pop();
    vis[1][1]=1,vis[n][m]=2;
    Q1.push({1,1});Q2.push({n,m});//Q2.push(make_pair{n,m});
    dist[1][1]=dist[n][m]=0;
    while(Q1.size()>0&&Q2.size()>0)
    {
        PII temp;
        if(Q1.size()>Q2.size())
            temp=Q2.front(),Q2.pop(),flag=2;
        else
            temp=Q1.front(),Q1.pop(),flag=1;
        for(int i=0;i<=3;i++)
        {
            int dx=temp.first+dir[i][0],dy=temp.second+dir[i][1];
            if(dx>=1&&dx<=n&&dy>=1&&dy<=m&&g[dx][dy]!='#')
            {
                if(vis[dx][dy]==0)
                {
                    dist[dx][dy]=dist[temp.first][temp.second]+1,vis[dx][dy]=vis[temp.first][temp.second];
                    if(flag==1)
                        Q1.push({dx,dy});
                    else Q2.push({dx,dy});
                }
                else if(vis[temp.first][temp.second]+vis[dx][dy]==3)//一个为1,一个为2
                    return dist[temp.first][temp.second]+dist[dx][dy]+2;
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",g[i]+1);
    int res=dbfs();
    printf("%d\n",res);
    return 0;
}

```
