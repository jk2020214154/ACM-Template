/*
将b看作是二进制，从右往左第k位的1表示因子中含有a^(2^k)
连乘会很大(有时候需要开long long)，考虑不断求余
*/
int fast_pow(int a,int b,int p)
{
    int res=1;
    while(b)
    {
        if(b%2==1)//b&1
            res=res*a%p;
        a=a*a%p;
        b/=2;//b>>=1;
    }
    return res;
}
