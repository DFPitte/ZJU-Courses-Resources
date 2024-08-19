#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 505
#define INF INT_MAX

int n, m;
int graph[MAX_N][MAX_N];  // 邻接矩阵存储图
int minEdge[MAX_N];       // 存储与已包含在MST中的顶点集连接的最小权边
int from[MAX_N];          // 记录最小权重边的起点
int visited[MAX_N];       // 标记顶点是否已包含在MST中

void prim(int start) {
    for (int i = 1; i <= n; i++) {
        minEdge[i] = INF;
        visited[i] = 0;
        from[i] = -1;
    }

    minEdge[start] = 0;
    int mst_weight = 0;
    int edges_used = 0;
    int is_unique = 1;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        // 找到未访问的最小权边
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && (u == -1 || minEdge[v] < minEdge[u])) {
                u = v;
            }
        }

        if (minEdge[u] == INF) {
            printf("No MST\n%d\n", n - edges_used+1);
            return;
        }

        visited[u] = 1;
        mst_weight += minEdge[u];
        edges_used++;

        // 更新连接边
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < minEdge[v]) {
                minEdge[v] = graph[u][v];
                from[v] = u;
            } else if (graph[u][v] != 0 && !visited[v] && graph[u][v] == minEdge[v] && from[v] != u) {
                // 存在与最小边权重相同但不是从同一节点来的边
                is_unique = 0;
            }
        }
    }

    if (edges_used < n-1) {
        //printf("edges_used: %d\n", edges_used); 
        printf("No MST\n%d\n", (n - edges_used) + 1);
    } else {
        printf("%d\n", mst_weight);
        printf("%s\n", is_unique ? "Yes" : "No");
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        if (graph[u][v] == 0 || weight < graph[u][v]) {
            graph[u][v] = weight;
            graph[v][u] = weight;
        }
    }

    prim(1);
    return 0;
}
