//http://47.110.135.197/problem.php?id=5237

#include <iostream>
#include <cstring>
#include <algorithm>
  
#define MAXN 100010
  
using namespace std;
  
int n,a[MAXN],b[MAXN],c[MAXN];
int res[MAXN];
  
int main()
{
    scanf("%d",&n);
    //以下标1为序列的起点，一般情况下从0开始也可以
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];//b是一个临时数组，用来得到离散化的映射关系
    }
    //下面使用了STL中的sort(排序)，unique(去重)，lower_bound(查找)函数
    sort(b+1,b+n+1);//排序
    int k=0;//去重,并获得去重后的长度k
    for(int i=1;i<=n;i++)
    {
        if(i==1||b[i]!=b[i-1])
            c[++k]=b[i];
    }
    //注:实际上[k+1,n]仍存在,保存着重复元素
    for(int i=1;i<=n;i++)
    {
        //通过二分查找lower_bound，快速地把元素和映射对应起来
        res[i]=lower_bound(c+1,c+k+1,a[i])-(c+1);
        printf("%d ",res[i]);
    }
      
    return 0;
}
