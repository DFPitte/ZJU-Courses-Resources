#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_V 1000
#define MAX_E 1000

int capacity[MAX_V][MAX_V];
int flow[MAX_V][MAX_V];
char planet_map[MAX_V][4];
int planet_count;

int queue[MAX_V];
int path[MAX_V];

int find_index(char *name) {
    for (int i = 0; i < planet_count; i++) {
        if (strcmp(planet_map[i], name) == 0) {
            return i;
        }
    }
    strcpy(planet_map[planet_count], name);
    return planet_count++;
}

int bfs(int source, int sink) {
    int read = 0, write = 0;
    memset(path, -1, sizeof(path));
    queue[write++] = source;
    path[source] = source;
    while (read < write) {
        int u = queue[read++];
        for (int v = 0; v < planet_count; v++) {
            if (path[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                path[v] = u;
                if (v == sink)
                    return 1;
                queue[write++] = v;
            }
        }
    }
    return 0;
}

int Max_fl(int source, int sink) {
    int max_flow = 0;
    while (bfs(source, sink)) {
        int increment = INT_MAX;
        for (int v = sink; v != source; v = path[v]) {
            int u = path[v];
            increment = (increment < capacity[u][v] - flow[u][v]) ? increment : capacity[u][v] - flow[u][v];
        }
        for (int v = sink; v != source; v = path[v]) {
            int u = path[v];
            flow[u][v] += increment;
            flow[v][u] -= increment;
        }
        max_flow += increment;
    }
    return max_flow;
}

int main() {
    char source[4], destination[4];
    int n;
    scanf("%s %s %d", source, destination, &n);
    
    int source_index = find_index(source);
    int dest_index = find_index(destination);
    
    for (int i = 0; i < n; i++) {
        char src[4], dst[4];
        int cap;
        scanf("%s %s %d", src, dst, &cap);
        int src_idx = find_index(src);
        int dst_idx = find_index(dst);
        capacity[src_idx][dst_idx] += cap;  
    }
    
    printf("%d\n", Max_fl(source_index, dest_index));
    return 0;
}
