//快速乘

int fast_mul(int a,int b,int p)
{
    int res=0;
    while(b)
    {
        if(b%2==1)//b&1
            res=(res+a)%p;
        a=(a+a)%p;
        b/=2;//b>>=1;
    }
    return res;
}
