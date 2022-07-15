#include <iostream>
#include <cstring>

#define MAXN 10010

using namespace std;

int nex[MAXN];

void get_next(string s)
{
    //初始化
    int j=0;
    nex[0]=0;
    for(int i=1;i<s.size();i++)
    {
        while(j>0&&s[i]!=s[j])// j要保证大于0，因为下面有取j-1作为数组下标的操作
            j=nex[j-1];//向前回退，注意这里，是要找前一位的对应的回退位置了
        if(s[i]==s[j])
            j++;
        nex[i]=j;//将j（前缀的长度）赋给nex[i]
    }
}


int KMP(string s,string t)
{
    int j=0;
    for(int i=0;i<s.size();i++)//注意i从0开始
    {
        while(j>0&&s[i]!=t[j])//不匹配
            j=nex[j-1];//j寻找之前匹配的位置
        if(s[i]==t[j])//匹配,j和i同时向后移动
            j++;//i的增加在for循环中
        if(j==t.size())//所有字符完全匹配,注意此处是size()
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
