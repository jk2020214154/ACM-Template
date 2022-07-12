#include <iostream>
#include <cstring>

#define MAXN 10010

using namespace std;

int nex[MAXN];

void get_next(string s)
{
    //初始化
    int j=-1;
    nex[0]=j;
    for(int i=1;i<s.size();i++)
    {
        while(j>=0&&s[i]!=s[j+1])
            j=nex[j];//向前回退
        if(s[i]==s[j+1])
            j++;
        nex[i]=j;//将j（前缀的长度）赋给nex[i]
    }
}


int KMP(string s,string t)
{
    int j=-1;//因为nex数组里记录的起始位置为-1
    for(int i=0;i<s.size();i++)//注意i从0开始
    {
        while(j>=0&&s[i]!=t[j+1])//不匹配
            j=nex[j];//j寻找之前匹配的位置
        if(s[i]==t[j+1])//匹配,j和i同时向后移动
            j++;//i的增加在for循环中
        if(j==(t.size()-1))//所有字符完全匹配
            return (i-t.size()+1);	
    }
    return -1;//匹配失败
}


int main()
{
    string s,t;
    cin >> s >> t;
    get_next(t);
    for(int i=0;i<t.size();i++)
        cout << nex[i] << " ";
    cout << endl;
    cout << KMP(s,t) << endl;
    return 0;
}
