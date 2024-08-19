#include<stdio.h>
int main()
{
    int n,a[100001],c;//define n,c and a
    scanf("%d %d",&n,&c);//read n and c
    for(int i=0;i<n;i++)
    scanf("%d",&a[i]);//inputa
    //start=clock();//start the clock
    int flag=0;//flag is used to mark if the numbers are found 
    for(int i=0;i<n;i++)//Traverse the combination of all array elements
    for(int j=i+1;j<n;j++)
    {
        if(a[i]+a[j]==c)//if the sum of the numbers equals to c
        {
            printf("%d %d\n",a[i],a[j]);//print a[i] and a[j]
            flag=1;//mark flag as 1,meaning the numbers are found
        }
    }
    if(flag==0)printf("No Found\n");//if didn't find the number,print nofound
    return 0;
}