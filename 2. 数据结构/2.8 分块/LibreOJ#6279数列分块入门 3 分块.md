 [题目链接](https://loj.ac/p/6279) 
 
#### 题目描述

给出一个长为 $n$ 的数列，以及 $n$ 个操作，操作涉及区间加法，询问区间内小于某个值 $x$ 的前驱（比其小的最大元素）。

#### 输入格式

第一行输入一个数字 $n$。

第二行输入 $n$ 个数字，第 $i$ 个数字为 $a_i$，以空格隔开。

接下来输入 $n$ 行询问，每行输入四个数字 $\mathrm{opt}、l、r、c$，以空格隔开。

若 $\mathrm{opt} = 0$，表示将位于 $[l, r]$ 的之间的数字都加 $c$。

若 $\mathrm{opt} = 1$，表示询问 $[l, r]$ 中 $c$ 的前驱的值（不存在则输出 $-1$）。

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

#### 输出

```
3
-1

```

#### 数据范围与提示

对于 $100\%$ 的数据， $1 \leq n \leq 100000, -2^{31} \leq \mathrm{others}、 \mathrm{ans} \leq 2^{31}-1$ 。


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
#include <cmath>
#include <vector>


#define MAXN 100010

using namespace std;


int n,a[MAXN];

int block,t;
int st[MAXN],ed[MAXN],pos[MAXN];

int add[MAXN];
//int sum[MAXN];

vector<int> v[MAXN];

void init(int n)
{
    block=sqrt(n);
    t=n/block;
    if(n%block!=0)
        t++;    
    for(int i=1;i<=t;i++)
    {
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    
    ed[t]=n;
    
    for(int i=1;i<=n;i++)
        pos[i]=(i-1)/block+1;
}

void update(int x)
{
    int len=v[x].size();
    for(int i=0;i<len;i++)
        v[x][i]=a[st[x]+i];
    sort(v[x].begin(),v[x].end());
}

void modify(int l,int r,int num){
    int lpos=pos[l],rpos=pos[r];//lpos对应l的块,rpos对应r的块
    if(lpos==rpos){//情况1:处理碎片块,l,r的块相同,暴力处理
        for(int i=l;i<=r;i++)//更新区间[l,r]的w[i]
            a[i]+=num;
        update(lpos);
    }
    else{
        for(int i=l;i<=ed[lpos];i++)//情况1:处理碎片块,l所属的块暴力处理,更新[l,ed[lpos]]块的w[i]
            a[i]+=num;
        update(lpos);
        for(int i=lpos+1;i<=rpos-1;i++)//情况2:处理整块,更新[lpos+1,rpos-1]整块的add
            add[i]+=num;
        for(int i=st[rpos];i<=r;i++)//情况1:处理碎片块,r所属的块暴力处理,更新[st[rpos],r]块的w[i]
            a[i]+=num;
        update(rpos);
    }
}


int query(int l,int r,int num)
{
    int lpos=pos[l],rpos=pos[r];//lpos对应l的块,rpos对应r的块
    int res=-1;
    if(lpos==rpos){//情况1:处理碎片块,l,r的块相同,暴力处理
        for(int i=l;i<=r;i++)//区间[l,r]求和
            if(a[i]+add[lpos]<num)
                res=max(res,a[i]+add[lpos]);
    }
    else{
        for(int i=l;i<=ed[lpos];i++)//情况1:处理碎片块,l所属的块暴力处理,区间[l,ed[lpos]]求和
            if(a[i]+add[lpos]<num)
                res=max(res,a[i]+add[lpos]);
       
        
        for(int i=lpos+1;i<=rpos-1;i++)//情况2:处理整块
        {
            int temp=lower_bound(v[i].begin(),v[i].end(),num-add[i])-v[i].begin();
            if(temp==0)
                continue;
            res=max(res,v[i][temp-1]+add[i]);
        
        }
        for(int i=st[rpos];i<=r;i++)//情况1:处理碎片块,r所属的块暴力处理,区间[st[rpos],r]求和
            if(a[i]+add[rpos]<num)
                res=max(res,a[i]+add[rpos]);
    }
    return res;//返回结果
    
}



int main()
{
    scanf("%d",&n);
    init(n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    
    for(int i=1;i<=t;i++)
    {
        for(int j=st[i];j<=ed[i];j++)
            v[i].push_back(a[j]);
        sort(v[i].begin(),v[i].end());
    }    
    
    /*for(int i=1;i<=t;i++)
    {
        for(auto j:v[i])
            cout << j << " ";
        cout << endl;
    }*/
    for(int i=1;i<=n;i++)
    {
        int op,l,r,c;
        scanf("%d %d %d %d",&op,&l,&r,&c);
        if(op==0)
            modify(l,r,c);
        else if(op==1)
            printf("%d\n",query(l,r,c));
        /*for(int i=1;i<=t;i++)
        {
            for(auto j:v[i])
                cout << j << " ";
            cout << endl;
        }*/
    }
        
    
    
    
    return 0;
}

```
