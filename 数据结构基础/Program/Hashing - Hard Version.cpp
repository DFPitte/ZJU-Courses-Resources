#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 1000;
int n,num[N],in[N];
struct cmp {
    bool operator()(int i, int j) {
        return num[i] > num[j];
    }
};

int main() {
    scanf("%d", &n);
    vector<vector<int>> g(n);
    priority_queue<int, vector<int>, cmp> q;
    bool flag=0;
    for(int i = 0;i < n; i++)
    {
        scanf("%d",&num[i]);
        if(num[i] > 0)
        {
            int k = num[i]%n;
            in[i] = (i-k+n)%n;//表示当前位置i到哈希值k的距离
            if(in[i] == 0)
            q.push(i);
            else
            {
                for(int j = 0;j <= in[i]; j++)
                {
                    g[(k+j)%n].push_back(i);
                }
            }
        }
        
        
    }
    while(!q.empty())
        {
            int tmp = q.top();
            q.pop();
            if(!flag){
                printf("%d",num[tmp]);
                flag = 1;
            }
            else printf(" %d",num[tmp]);
            for(int i = 0;i < g[tmp].size(); i++)
            {
                int v = g[tmp][i];
                in[v]--;
                if(in[v] == 0)
                q.push(v);
            }   
        }
    return 0;
}