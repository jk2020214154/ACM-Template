//http://47.110.135.197/problem.php?id=5238

#include <iostream>
#include <algorithm>
 
#define MAXN 100010
 
using namespace std;
 
int n;
int res[MAXN];
 
struct node{
    int dat;
    int id;
}s[MAXN];
 
int cmp(node x,node y)
{
    return x.dat<y.dat;
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i].dat);
        s[i].id=i;
    }
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;i++)
        res[s[i].id]=i-1;
     
    for(int i=1;i<=n;i++)
        printf("%d ",res[i]);
     
    return 0;
}
