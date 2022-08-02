
Manacher 算法是处理回文串的利器，由一位名叫 Manacher 的大佬在 1975 年提出，可在**线性时间复杂度(即 O(n) )内求解出最长回文子串**。

问题:给定一个字符串 S，求出它的最长回文子串长度。
比如 `ababbac` 的最长回文子串为`abba`，长度为4。



```cpp

#include <iostream>
#include <cstring>

#define MAXN 20000010

using namespace std;

int len,p[MAXN];//变形后字符串的长度
char b[MAXN];//存变形后的字符串
string s;//原始字符串

void init()
{
    len=0;
    b[len++]='!';//起点哨兵
    b[len++]='#';
    for(int i=0;i<s.size();i++)
    {
        b[len++]=s[i];
        b[len++]='#';
    }
    b[len++]='@';//末尾哨兵
}

int manacher()
{
    int rt=0,mid=0,res=0;
    for(int i=1;i<=len-2;i++)
    {
        if(i<rt)
            p[i]=min(p[2*mid-i],rt-i);
        else p[i]=1;
        while(b[i+p[i]]==b[i-p[i]])
        //以i为中心p[i]为半径不断往外扩展,如果相等继续扩展
            p[i]++;
        if(i+p[i]>rt)//如果以i为中心的最大回文串能更新rt
        {
            rt=i+p[i];
            mid=i;//更新rt对应的mid
        }
        res=max(res,p[i]-1);//注意此处是p[i]-1
    }
    return res;   
}

int main()
{
    cin >> s;
    init();
    //cout << b << endl;
    cout << manacher() << endl;
    return 0;
}

```