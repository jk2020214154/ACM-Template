#### [题目链接](https://www.acwing.com/problem/content/description/140/)


很久很久以前，森林里住着一群兔子。

有一天，兔子们想要研究自己的 DNA 序列。

我们首先选取一个好长好长的 DNA 序列（小兔子是外星生物，DNA 序列可能包含 $26$ 个小写英文字母）。

然后我们每次选择两个区间，询问如果用两个区间里的 DNA 序列分别生产出来两只兔子，这两个兔子是否一模一样。

注意两个兔子一模一样只可能是他们的 DNA 序列一模一样。

#### 输入格式

第一行输入一个 DNA 字符串 $S$。

第二行一个数字 $m$，表示 $m$ 次询问。

接下来 $m$ 行，每行四个数字 $l\_1, r\_1, l\_2, r\_2$，分别表示此次询问的两个区间，注意字符串的位置从 $1$ 开始编号。

#### 输出格式

对于每次询问，输出一行表示结果。

如果两只兔子完全相同输出 `Yes`，否则输出 `No`（注意大小写）。

#### 数据范围

$1 \\le length(S),m \\le 1000000$

#### 输入样例：

    aabbaabb
    3
    1 3 5 7
    1 3 6 8
    1 2 1 2
    

#### 输出样例：

    Yes
    No
    Yes
    
 ```cpp
 #include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


const int MAXN=1000010,P=131,M=1e9+7;
typedef unsigned long long ull;
typedef long long ll;
int n;
char s[MAXN];//已知字符串s从1开始存储
ull Hash1[MAXN],p1[MAXN];//此处用自动取模
ll Hash2[MAXN],p2[MAXN];//此处采用单Hash方法
//Hash1和Hash2共同构成双Hash方法


ull get_hash1(int l,int r)
{
	return Hash1[r]-Hash1[l-1]*p1[r-l+1];
}

ll get_hash2(int l,int r)
{
	return ((Hash2[r]-Hash2[l-1]*p2[r-l+1])%M+M)%M;
}

int main()
{
    
    scanf("%s %d",s+1,&n);
    p1[0]=p2[0]=1;
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)
    {//此处为了方便,字符串的字符分配值应是多少就是该字符的ascii码
        p1[i]=p1[i-1]*P;//求P的次方
        Hash1[i]=Hash1[i-1]*P+s[i];//利用类似前缀和的思想求Hash
        p2[i]=((p2[i-1]%M)*(P%M))%M;//(nm)%mod=(n%mod * m%mod) %mod;
        Hash2[i]=(((Hash2[i-1]%M)*P)%M+s[i])%M;
    }
    
    for(int i=1;i<=n;i++)
    {
        int l1,r1,l2,r2;
        scanf("%d %d %d %d",&l1,&r1,&l2,&r2);
        //cout << get_hash2(l1,r1) << "  " << get_hash2(l2,r2) << endl;
        if(get_hash2(l1,r1)==get_hash2(l2,r2))
            printf("Yes\n");
        else printf("No\n");
    }
    
    return 0;
}
 
 
 
 ```
