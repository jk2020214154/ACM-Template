https://www.acwing.com/problem/content/832/

/*
给定一个长度为 $N$ 的整数数列，输出每个数左边第一个比它小的数，如果不存在则输出 $\-1$。

#### 输入格式

第一行包含整数 $N$，表示数列长度。

第二行包含 $N$ 个整数，表示整数数列。

#### 输出格式

共一行，包含 $N$ 个整数，其中第 $i$ 个数表示第 $i$ 个数的左边第一个比它小的数，如果不存在则输出 $\-1$。

#### 数据范围

$1 \\le N \\le 10^5$  
$1 \\le 数列中元素 \\le 10^9$

#### 输入样例：

    5
    3 4 2 7 5
    

#### 输出样例：

    -1 3 -1 2 2

*/

#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN=100010;

int n,a[MAXN],res[MAXN];
stack<int> sta;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)//遍历数组中每个元素
    {
        while(sta.size()>0&&a[i]<=sta.top())//保证有序性
            sta.pop();
        //更新结果
        if(sta.size()==0)
            res[i]=-1;
        else res[i]=sta.top(); 
        sta.push(a[i]);//入栈
    }
    for(int i=1;i<=n;i++)
        printf("%d ",res[i]);
    return 0;
}
