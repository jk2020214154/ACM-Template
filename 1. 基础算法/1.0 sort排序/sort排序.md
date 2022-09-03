sort函数的使用——对无序数组进行排序(在$C++$的环境下运行)

> ①使用的$c++$头文件：

```cpp
#include<algorithm>
using namespace std;
```

> ②使用形式：

```cpp
sort(first_pointer,last_pointer,cmp)
//sort(first_pointer,last_pointer)
```

这个函数可以传两个（或三个）参数，其含义：
* 第一个参数$first$_$pointer$   : 指要排序的数组的起始地址
* 第二个参数$last$_$pointer$    : 指结束的地址（最后一个数据的后一个数据的地址）
> 注:排序的区间为$[first$\_$pointer,last$\_$pointer)$，对数组$t$的第$0$到$len-1$的元素排序，就写$sort(t,t+len)$
* 第三个参数$cmp$是排序的方法 ： 可以是从升序也可以是降序。如果第三个参数不写，则默认的排序是从小到大排序
> 关于$cmp$参数的不同表示形式：
* 定义比较函数（最常用）

```cpp
//从小到大排序用 < ,从大到小排序用 > 
/********************************************************************************/
//一维数组
int arr[100];
int/*int可用bool替换*/ cmp(int a,int b)
{
    return a>b;//降序排列
    //return a<b;//升序排列（默认）
}
    sort(arr,arr+100,cmp);//对arr[0]至arr[99]之间的数进行排序[arr[0],arr[100])
/********************************************************************************/
//结构体
struct stu
{
    int id;
    int value;
}s[100];

int/*int可用bool替换*/ cmp(struct stu a,struct stu b)
{
    if(a.value==b.value) //如果两个结构体的value相同，则按它们的id值从小到大排列
        return a.id<b.id;
    else return a.value<b.value; // 反之按value的值从小到大排列
}
    sort(s,s+100,cmp);
/********************************************************************************/
//向量vector
    vector <int> v;
    sort(v.begin(),v.end());//对整体进行默认升序排列
    //sort(v.begin(),v.begin()+50);/*对部分进行默认升序排列*/
/********************************************************************************/

```

* 使用标准库函数
> 利用$functionnal$头文件（提供一堆基于模板的比较函数对象）中的$greater$和$less$
> 缺点是只能实现**简单的排序**，结构体不适用

```cpp
#include<algorithm>
#include <functional>
using namespace std;

    sort(begin,end,greater<date_type>());//降序排列
    sort(begin,end,less<date_type>());//升序排列

```
* 重载结构体或类的比较运算符

```cpp
/********************************************************************************/
//情况一：在结构体内部重载
typedef struct Student{
    int id;
    string name;
    double grade;
    bool operator<(const Student& s)
    {
        return id>s.id;//降序排列
        //return id<s.id;//升序排列
    }
};
vector<Student> v;
sort(v.begin(),v.end());
/********************************************************************************/
//情况二：在外部重载
vector<Student> v;
bool operator<(const Student& s1, const Student& s2)
{
    return s1.id>s2.id;//降序排列
    //return s1.id<s2.id;//升序排列
}
sort(v.begin(),v.end());
```




