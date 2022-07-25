[题目链接](https://loj.ac/p/6282) 

#### 题目描述

给出一个长为 $n$ 的数列，以及 $n$ 个操作，操作涉及单点插入，单点询问，数据随机生成。

#### 输入格式

第一行输入一个数字 $n$。

第二行输入 $n$ 个数字，第 $i$ 个数字为 $a_i$，以空格隔开。

接下来输入 $n$ 行询问，每行输入四个数字 $\mathrm{opt}、l、r、c$，以空格隔开。

若 $\mathrm{opt} = 0$，表示在第 $l$ 个数字前插入数字 $r$（$c$ 忽略）。

若 $\mathrm{opt} = 1$，表示询问 $a_r$ 的值（$l$ 和 $c$ 忽略）。

#### 输出格式

对于每次询问，输出一行一个数字表示答案。

#### 样例输入

```
4
1 2 2 3
0 1 3 1
1 1 4 4
0 1 2 2
1 1 2 4

```

#### 输出复制

```
2
3

```

#### 数据范围与提示

对于 $100\%$ 的数据， $1 \leq n \leq 100000, -2^{31} \leq \mathrm{others}、 \mathrm{ans} \leq 2^{31}-1$ 。


#### 可采用重构分块实现(给出去年写过的),也可采用vector暴力插入

```cpp

/**
  * @author  : SDTBU_LY
  * @version : V1.0.0
  * @上联    : ac自动机fail树上dfs序建可持久化线段树
  * @下联    : 后缀自动机的next指针DAG图上求SG函数
**/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> v;


int main()
{
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int temp;
        scanf("%d",&temp);
        v.push_back(temp);
    }
    
    for(int i=1;i<=n;i++)
    {
        int op,l,r,c;
        scanf("%d %d %d %d",&op,&l,&r,&c);
        if(op==0)
            v.insert(v.begin()+l-1,r);
        else if(op==1)
            printf("%d\n",v[r-1]);
        
        
    }
    
    return 0;
}

```


```cpp


#include<stdio.h>
#include<math.h>
#include<string.h>
#define N 100005
int n,m;
int block;///每块中的数量
int num;///块的数量
int l[N],r[N];///每块的左边界，右边界
int a[1010][3010];   ///用来存放元素的二维数组
int b[1010][3010];   ///重新分块时暂时储存元素的数组
int belong[N]; ///第i个元素属于哪一块
int tot=0;   ///记录插入的数的数量是否达到block
int len[N];   ///表示每个块的长度
void build()
{
    m=n;
    block=(int)sqrt(n);
    num=n/block;
    if(n%block) num++;
    for(int i=1;i<=n;i++)
    {
        int kuai=(i-1)/block+1;
        int x;
        scanf("%d",&x);
        a[kuai][++len[kuai]]=x;   ///向二维数组中添加元素
    }
}
void rebuild()
{   ///重新分块
    m+=tot;   ///m记录此时总元素的数量
    tot=0;   ///更新tot
    block=(int)sqrt(m);
    int cnt=0,lenth=0;
    for(int i=1;i<=num;i++)
    {
        for(int j=1;j<=len[i];j++)
        {
            cnt++;
            int id=(cnt-1)/block+1;
            b[id][++lenth]=a[i][j];   ///b数组暂时存放
            if(lenth==block) lenth=0;   ///更新lenth
        }
    }
    num=m/block; 
    if(m%block) 
        num++;
    for(int i=1;i<=num;i++)
    {
        if(i!=num||m%block==0) 
            len[i]=block;   ///更新len数组
        else 
            len[i]=m-block*block;
        for(int j=1;j<=len[i];j++)
            a[i][j]=b[i][j];   ///元素从b数组向a数组转移
    }
}
void update(int x,int y){
    int i,pos=0;
    for(i=1;i<=num;i++)   ///找到插入元素的位置
    {
        if(pos+len[i]>=x) 
            break;
        pos+=len[i];
    }
    len[i]++;   ///更新该块的长度
    for(int j=len[i];j>=x-pos+1;j--)
        a[i][j]=a[i][j-1];    ///该块中元素后移
    a[i][x-pos]=y;    ///插入元素
    tot++;   ///插入的元素+1
    if(tot==block) 
        rebuild();   ///判断是否需要重新分块
}
int query(int x){
    int i,pos=0;
    for(i=1;i<=num;i++)   ///查找答案的位置
    {
        if(pos+len[i]>=x) 
            break;
        pos+=len[i];
    }
    return a[i][x-pos];   ///返回答案
}
int main(){
    scanf("%d",&n);
    build();
    int sum=n;
    while(sum--){
        int opt,l,r,c;
        scanf("%d %d %d %d",&opt,&l,&r,&c);
        if(opt==0) 
            update(l,r);
        else 
            printf("%d\n",query(r));
    }
    return 0;
}

```

