int gcd(int a,int b)//最大公约数
{
    if(b==0)
        return a;
    return gcd(b,a%b);
    //亦可用下行代码解决
    //return b?gcd(b,a%b):a;
}

int lcm(int a,int b)//最小公倍数
{
    return a/gcd(a,b)*b;
    //一般不写为a*b/gcd(a,b)
}



__gcd(a,b);//该函数前面是两个下划线。
