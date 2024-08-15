#include<bits/stdc++.h>

#define MAX_CITIES 500 // Define the maximum number of cities.
using namespace std;
int graph[MAX_CITIES][MAX_CITIES]; // Graph representation, where graph[i][j] holds the distance between cities i and j.
int path_count[MAX_CITIES]; // Array to count the number of shortest paths through each city.
int dist[MAX_CITIES]; // Array to store the shortest distance from the source to each city.
int n, m, k; // n: number of cities, m: number of roads, k: threshold number of paths for a hub.

// Dijkstra's algorithm to find the shortest path from a source city to all other cities.
void dijkstra(int src) {
    bool visited[MAX_CITIES] = {false}; // Keeps track of which cities have been visited.

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX; // Initialize distances to infinity.
    }
    dist[src] = 0; // Distance from source to itself is 0.

    for (int count = 0; count < n; count++) { // Loop to find shortest path to all cities.
        int u = -1;
        // Find the unvisited city with the shortest distance.
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        visited[u] = true; // Mark the selected city as visited.

        // Update the shortest path for all adjacent cities.
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

bool used[MAX_CITIES]; // Array to mark cities as visited in the DFS.
int route[MAX_CITIES]; // Array to track the current path route in DFS.

// DFS function to find all paths from src to dest equal to the shortest path length.
void dfs(int p, int len, int dest, int route_len) {
    // If the current path length exceeds the shortest path, stop the search.
    if (route_len > dist[dest]) return;

    // If the destination is reached and the path length equals the shortest path length.
    if (p == dest) {
        if (route_len == dist[dest]) {
            for (int i = 0; i < len; i++) {
                path_count[route[i]]++; // Increment path count for each city in the route.
            }
        }
        return;
    }

    // Explore all adjacent cities using DFS.
    for (int i = 0; i < n; i++) {
        if (graph[p][i] > 0 && !used[i]) {
            used[i] = true; // Mark city as visited.
            route[len++] = i; // Add city to the route.
            dfs(i, len, dest, route_len + graph[p][i]); // Recurse with the new city and updated path length.
            route[--len] = 0; // Remove the city from the route on backtracking.
            used[i] = false; // Unmark city as visited.
        }
    }
}

// Function to identify and print all transportation hubs.
void findTransportationHubs(int src, int dest) {
    memset(path_count, 0, sizeof(path_count)); // Reset path counts.
    dijkstra(src); // Compute shortest paths from src.
    dfs(src, 0, dest, 0); // Use DFS to find all shortest paths from src to dest.

    bool hasHubs = false;
    // Check for and print all transportation hubs.
    for (int i = 0; i < n; i++) {
        if (i != src && i != dest && path_count[i] >= k) {// If the path count is greater than or equal to k, print the city.
            if (hasHubs) printf(" ");
            printf("%d", i);
            hasHubs = true;
        }
    }
    if (!hasHubs) {// If no hubs are found, print "None".
        printf("None");
    }
    printf("\n");
}

int main() {
    //You can change input*.txt file to test other inputs
    freopen("input2.txt", "r", stdin);// Read input from input.txt file.
    // Read the number of cities, roads, and the threshold.
    scanf("%d %d %d", &n, &m, &k);
    memset(graph, 0, sizeof(graph)); // Initialize the graph matrix.
    // Read each road and its length.
    for (int i = 0; i < m; i++) {
        int u, v, length;
        scanf("%d %d %d", &u, &v, &length);
        graph[u][v] = length;// Store the road length between cities u and v.
        graph[v][u] = length;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        findTransportationHubs(src, dest); // Process each query.
    }
    return 0;
}
