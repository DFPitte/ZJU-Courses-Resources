#include<stdio.h>
int n,c;
int a[100001]={0},b[100001];//array a is used to mark if the number has appeared
//for example,if a[i]=1,means number i is in the array b
//array b is used to store the n given numbers
//suppose the integers are no larger than 100000 
int main(void)
{
    scanf("%d %d",&n,&c);//read n and c
    int flag=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&b[i]);//read the numbers
        if(a[c-b[i]]==1)
        {
            printf("%d %d\n",b[i],c-b[i]);//if c-b[i] is appeared,than print the two numbers
            flag=1;//meaning the number are found
        }
        a[b[i]]=1;//mark array a[b[i]] as 1
    }
    if(flag==0)
    printf("No found\n");//output nofound if flag=0
    return 0;
}