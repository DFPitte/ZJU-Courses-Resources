#include<bits/stdc++.h>
using namespace std;
int n,m,a[100001],mmax=0,l=0;
int main() 
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    scanf("%d",&a[i]);
    l=a[0];
    for(int i=0;i<n;i++)
    {
        int sum=0;
        int j=i;
        while(j>=0&&(a[i]-a[j])<=m)
        {
            sum++;
            j--;
        }
        if(sum>mmax)
        {
            mmax=sum;
            l=a[i];
        }
    }
    l-=m;
    printf("%d %d",l,mmax);
    return 0;
}
