#include<bits/stdc++.h>
using namespace std;
int n,m,p,ma[1001][1001];
bool f(int s[],int num)
{
    bool visit[1001] = {false};
    if(s[0] != s[num-1]) return false;
    if(num!=n+1) return false;
    for(int i = 0;i<num-1;i++)
    {
        if(visit[s[i]] == true) return false;
        if(ma[s[i]][s[i+1]] == 0) return false;
        visit[s[i]] = true;
    }

    return true;
}
int main()
{
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        ma[x][y] = 1;
        ma[y][x] = 1;
    }
    scanf("%d",&p);
    for(int i = 0;i<p;i++)
    {
        int num,a[1001];
        scanf("%d",&num);
        for(int j=0;j<num;j++){
            scanf("%d",&a[j]);

        }
        if(f(a,num)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}