#### [题目链接](https://www.acwing.com/problem/content/156/)

给定一个大小为 $n \\le 10^6$ 的数组。

有一个大小为 $k$ 的滑动窗口，它从数组的最左边移动到最右边。

你只能在窗口中看到 $k$ 个数字。

每次滑动窗口向右移动一个位置。

以下是一个例子：

该数组为 `[1 3 -1 -3 5 3 6 7]`，$k$ 为 $3$。

| 窗口位置 | 最小值 | 最大值 |
| :-: | :-: | :-: |
| \[1 3 -1\] -3 5 3 6 7 | \-1 | 3 |
| 1 \[3 -1 -3\] 5 3 6 7 | \-3 | 3 |
| 1 3 \[-1 -3 5\] 3 6 7 | \-3 | 5 |
| 1 3 -1 \[-3 5 3\] 6 7 | \-3 | 5 |
| 1 3 -1 -3 \[5 3 6\] 7 | 3 | 6 |
| 1 3 -1 -3 5 \[3 6 7\] | 3 | 7 |

你的任务是确定滑动窗口位于每个位置时，窗口中的最大值和最小值。

#### 输入格式

输入包含两行。

第一行包含两个整数 $n$ 和 $k$，分别代表数组长度和滑动窗口的长度。

第二行有 $n$ 个整数，代表数组的具体数值。

同行数据之间用空格隔开。

#### 输出格式

输出包含两个。

第一行输出，从左至右，每个位置滑动窗口中的最小值。

第二行输出，从左至右，每个位置滑动窗口中的最大值。

#### 输入样例：

    8 3
    1 3 -1 -3 5 3 6 7
    

#### 输出样例：

    -1 -3 -3 -3 3 3
    3 3 5 5 6 7


#### 手写数组模拟
```cpp
//滑动窗口(POJ该题数据加强,此代码会TLE掉)
#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN=1000010;

int n,k,a[MAXN];
int q[MAXN],front,rear;//队头front,队尾rear

int main()
{
    scanf("%d %d",&n,&k);
    for(int i=0;i<=n-1;i++)
        scanf("%d",&a[i]);
    //求最小值,使用单调递增队列
    front=0,rear=-1;
    for(int i=0;i<=n-1;i++)
    {
        if(front<=rear&&q[front]<=i-k)//处理滑动窗口左端
            front++;
        while(front<=rear&&a[i]<=a[q[rear]])//把大于等于入队元素在队列中的值都剔除
            rear--;
        q[++rear]=i;//将该元素的下标放入队列中
        if(i>=k-1)//达到区间长度输出队头元素,此处也可存入数组中,全部处理完再输出
            printf("%d ",a[q[front]]);
    }
    printf("\n");
    //求最大值,使用单调递减队列
    front=0,rear=-1;
    for(int i=0;i<=n-1;i++)
    {
        if(front<=rear&&q[front]<=i-k)//处理滑动窗口左端
            front++;
        while(front<=rear&&a[i]>=a[q[rear]])//把小于等于入队元素在队列中的值都剔除
            rear--;
        q[++rear]=i;//将该元素的下标放入队列中
        if(i>=k-1)//达到区间长度输出队头元素
            printf("%d ",a[q[front]]);
    }

    return 0;
}
```


#### 双端队列

```cpp
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int MAXN=1000010;

int n,k,a[MAXN];
deque<int> dq1,dq2;

int main()
{
    scanf("%d %d",&n,&k);
    //求最小值,使用单调递增队列
    for(int i=0;i<=n-1;i++)
    {
        scanf("%d",&a[i]);
        if(dq1.size()>0&&dq1.front()<=i-k)//处理滑动窗口左端
            dq1.pop_front();//弹出队头
        while(dq1.size()>0&&a[i]<=a[dq1.back()])//把大于等于入队元素在队列中的值都剔除
            dq1.pop_back();
        dq1.push_back(i);//将该元素的下标放入队列中
        if(i>=k-1)//达到区间长度输出队头元素,此处也可存入数组中,全部处理完再输出
            printf("%d ",a[dq1.front()]);
    }
    printf("\n");
    //求最大值,使用单调递减队列
    for(int i=0;i<=n-1;i++)
    {
        if(dq2.size()>0&&dq2.front()<=i-k)//处理滑动窗口左端
            dq2.pop_front();
        while(dq2.size()>0&&a[i]>=a[dq2.back()])//把小于等于入队元素在队列中的值都剔除
            dq2.pop_back();
        dq2.push_back(i);//将该元素的下标放入队列中
        if(i>=k-1)//达到区间长度输出队头元素
            printf("%d ",a[dq2.front()]);
    }

    return 0;
}
```
