#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <set>

using namespace std;

const int MAXN = 500; // 最大城市数量
const int INF = numeric_limits<int>::max(); // 无穷大代表不可达

vector<pair<int, int>> adj[MAXN]; // 邻接列表，存储图
int n, m, k; // 城市数，道路数，阈值

void dijkstra(int src, vector<int>& dist, vector<int>& pred) {
    dist.assign(n, INF);
    pred.assign(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d_u = pq.top().first;
        pq.pop();

        if (d_u != dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void findHubs(int src, int dest) {
    vector<int> dist, pred;
    dijkstra(src, dist, pred);

    vector<int> path;
    for (int at = dest; at != -1; at = pred[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    vector<int> count(n, 0);
    for (int city : path) {
        if (city != src && city != dest) { // 排除源点和终点
            count[city]++;
        }
    }

    vector<int> hubs;
    for (int i = 0; i < n; ++i) {
        if (count[i] >= k) {
            hubs.push_back(i);
        }
    }

    if (hubs.empty()) {
        cout << "None\n";
    } else {
        for (int i = 0; i < hubs.size(); ++i) {
            if (i > 0) cout << " ";
            cout << hubs[i];
        }
        cout << "\n";
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // 无向图
    }

    int T;
    cin >> T;
    while (T--) {
        int src, dest;
        cin >> src >> dest;
        findHubs(src, dest);
    }

    return 0;
}
