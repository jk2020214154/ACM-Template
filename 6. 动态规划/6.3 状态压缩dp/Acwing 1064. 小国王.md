[题目链接](https://www.acwing.com/problem/content/1066/)

在 $n \\times n$ 的棋盘上放 $k$ 个国王，国王可攻击相邻的 $8$ 个格子，求使它们无法互相攻击的方案总数。

#### 输入格式

共一行，包含两个整数 $n$ 和 $k$。

#### 输出格式

共一行，表示方案总数，若不能够放置则输出$0$。

#### 数据范围

$1 \\le n \\le 10$,  
$0 \\le k \\le n^2$

#### 输入样例：

    3 2
    

#### 输出样例：

    16
    
    
 ```cpp
 
 #include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 12
#define MAXM (1<<10)
#define MAXK 110


using namespace std;

typedef long long ll;

int n,m;
vector<int> state;//保存所有合法状态
int cnt[MAXM];//统计每个状态的个数
ll f[MAXN][MAXK][MAXM];

vector<int> pre[MAXN];//保存当前状态的相邻合法状态的下标,注意不是相邻合法状态的值

int check(int x){//检测状态x是否不存在相邻的1(存在相邻的1返回0,不存在返回1)
    for(int i=0;i<n;i++)
        if(((x>>i)&1)&&((x>>(i+1))&1))//存在相邻的1
            return 0;
    return 1;
}

int count(int x){//统计状态x的1的个数
    int res=0;
    for(int i=0;i<n;i++)
        if((x>>i)&1)
            res++;
        //res+=(x>>i&1);//也可直接写成这种
    return res;
}


int main()
{
    
    scanf("%d %d",&n,&m);
       
    for(int i=0;i<(1<<n);i++)
    	if(check(i)==1){//是合法状态
    		state.push_back(i);//保存合法状态
    		cnt[i]=count(i);   //更新cnt值
    	}
    /*for(int i=0;i<state.size();i++)
        cout << state[i] << "***" << cnt[state[i]] << endl;*/
    for(int i=0;i<state.size();i++)
    	for(int j=0;j<state.size();j++){
    		int a=state[i],b=state[j];
    		if(((a&b)==0)&&check(a|b)==1)//注意要写成(a&b),不然先计算b==0(优先级问题)
    			pre[i].push_back(j);
    	}    
    
    f[0][0][0]=1;
    //循环n可写成n+1,此时直接输出f[n+1][m][0]的值
    for(int i=1;i<=n;i++)//枚举每一层i
    	for(int j=0;j<=m;j++)//枚举个数j
    		for(int a=0;a<state.size();a++)//枚举当前状态
    			for(int b=0;b<pre[a].size();b++)//枚举当前状态相邻的合法状态
    			{
    				int temp_cnt=cnt[state[a]];
    				if(j>=temp_cnt)//同时前i层的个数应大于等于当前行的个数
    					f[i][j][state[a]]+=f[i-1][j-temp_cnt][state[pre[a][b]]];
    			}
    			
    ll res=0;
    for(int i=0;i<state.size();i++)
    	res+=f[n][m][state[i]];
    printf("%lld\n",res);
    //printf("%lld\n",f[n+1][m][0]);
    return 0;
}

```
