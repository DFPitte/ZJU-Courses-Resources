#include<stdio.h>
int m,n,k,st[10001],top=-1;
int isfull()
{
    return (top+1)==m;
}
int isempty()
{
    return top==-1;
}
void push(int x)
{
    if(isfull())
    return;
    st[++top]=x;
}
void pop()
{
    if(isempty())return;
    st[top--];
}
int gettop()
{
    if(isempty())return -1;
    return st[top];
}
int main()
{
    scanf("%d %d %d",&m,&n,&k);
    for(int i=0;i<k;i++)
    {
        int num,nxt=1,flag=0;
        top=-1;
        for(int j=0;j<n;j++)
        {
            scanf("%d",&num);
            while(nxt<=num&&(isempty()||gettop()!=num))
            {
                if(isfull())
                {
                    flag=1;
                    break;
                }
                push(nxt);
                nxt++;
                
            }
            if(flag==0&&gettop()==num)
            pop();
            else
            flag=1;
        }
        if(flag==0)
        printf("YES\n");
        else printf("NO\n");
        
    }
    return 0;
}