#include<bits/stdc++.h>
using namespace std;
priority_queue <int ,vector<int> ,greater<int> > q;
vector <int> now,nxt;
int main ()
{
    int n,m,a[100001];
    scanf("%d %d",&n,&m);
    for(int i = 0;i < n;i++)
    scanf("%d",&a[i]);
    for(int i = 0;i < m;i++)
    q.push(a[i]);
    int num = m;
    for(int i = 0;i <= n;i++)
    {
        int tmp = q.top();
        q.pop();
        now.push_back(tmp);
        if(i + m < n)
        if(tmp < a[i+m])
        q.push(a[i+m]);
        else 
        nxt.push_back(a[i+m]);

        
        if(q.empty())
        {
            sort(now.begin(),now.end());
            printf("%d",now[0]);
            for(int j = 1;j < now.size();j++)
            printf(" %d",now[j]);
            printf("\n");
            for(int j = 0;j < nxt.size();j++)
            q.push(nxt[j]);
            now.clear();
            nxt.clear();
        }
    }
    return 0;
}
