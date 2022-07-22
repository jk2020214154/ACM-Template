int primes[MAXN],cnt,vis[MAXN];

void get_primes(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(vis[i]==0)
            primes[cnt++]=i;
        for(int j=0;primes[j]<=n/i;j++)
        {
            vis[primes[j]*i]=1;
            if(i%primes[j]==0)//primes[j]一定是i的最小质因子 
                break;
        }
    }
}
