typedef long long ll;
int primes[MAXN],cnt,vis[MAXN];

void get_primes(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(vis[i]==0)
        {
            primes[cnt++]=i;
            for(int j=i+i;j<=n;j+=i)
                vis[j]=1;
        /*
            for(ll j=(ll)i*i;j<=n;j+=i)
                    vis[j]=1;
        */
        }
    }
}
