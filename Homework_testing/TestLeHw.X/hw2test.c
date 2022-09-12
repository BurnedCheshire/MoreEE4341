//volatile int a, b, c;
int power(int, int);

int main(void)
{
    int x;
    
    x = power(2, 5);
    
    return 0;
}

int power(int baset, int n)
{
    int i, p;
    
    p = 1;
    for(i = 1; i <= n; i++)
    {
        p = p*baset;
        
    }
    return p;
}
//    int p;
//    if(n>1)
//    {
//        p = baset*power(baset, n-1);
//    }
//    else
//    {
//        p = baset;
//    }
//    return p;
//}