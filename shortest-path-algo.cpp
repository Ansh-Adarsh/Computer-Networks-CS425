#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

const int INF = 1e9;
const int N = 10; // A, B, C, D, E, F, G, H, J, K

int charToIndex(char ch) {
    ch = toupper(ch);
    if (ch == 'A') return 0;
    if (ch == 'B') return 1;
    if (ch == 'C') return 2;
    if (ch == 'D') return 3;
    if (ch == 'E') return 4;
    if (ch == 'F') return 5;
    if (ch == 'G') return 6;
    if (ch == 'H') return 7;
    if (ch == 'J') return 8;
    if (ch == 'K') return 9;
    return -1;
}

char indexToChar(int idx) {
    string nodes = "ABCDE FGHJK";
    if (idx == 0) return 'A';
    if (idx == 1) return 'B';
    if (idx == 2) return 'C';
    if (idx == 3) return 'D';
    if (idx == 4) return 'E';
    if (idx == 5) return 'F';
    if (idx == 6) return 'G';
    if (idx == 7) return 'H';
    if (idx == 8) return 'J';
    if (idx == 9) return 'K';
    return '?';
}

void printPath(const vector<int>& parent, int src, int dest) {
    vector<int> path;
    for (int cur = dest; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    if (path.empty() || path[0] != src) {
        cout << "No path found.\n";
        return;
    }

    for (size_t i = 0; i < path.size(); i++) {
        cout << indexToChar(path[i]);
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << '\n';
}

pair<int, vector<int>> dijkstra(int src, int dest,
                                const vector<vector<pair<int,int>>>& adj) {
    vector<int> dist(N, INF), parent(N, -1);
    vector<bool> visited(N, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        int d = top.first;
        int u = top.second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist[dest], parent};
}

pair<int, vector<int>> bellmanFord(int src, int dest, const vector<Edge>& edges) {
    vector<int> dist(N, INF), parent(N, -1);
    dist[src] = 0;

    for (int i = 1; i <= N - 1; i++) {
        bool changed = false;
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                changed = true;
            }
        }
        if (!changed) break;
    }

    return {dist[dest], parent};
}

int main() {
    vector<vector<pair<int,int>>> adj(N);
    vector<Edge> edges;

    auto addUndirectedEdge = [&](char a, char b, int w) {
        int u = charToIndex(a);
        int v = charToIndex(b);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    };

    // Graph from the assignment figure
    addUndirectedEdge('A', 'B', 1);
    addUndirectedEdge('A', 'E', 1);
    addUndirectedEdge('B', 'C', 1);
    addUndirectedEdge('C', 'G', 1);
    addUndirectedEdge('C', 'F', 3);
    addUndirectedEdge('C', 'J', 4);
    addUndirectedEdge('D', 'E', 5);
    addUndirectedEdge('D', 'H', 1);
    addUndirectedEdge('D', 'K', 1);
    addUndirectedEdge('D', 'J', 2);
    addUndirectedEdge('E', 'G', 1);
    addUndirectedEdge('G', 'H', 1);
    addUndirectedEdge('K', 'F', 1);

    char sChar, tChar;
    cout << "Enter source node (A/B/C/D/E/F/G/H/J/K): ";
    cin >> sChar;
    cout << "Enter destination node (A/B/C/D/E/F/G/H/J/K): ";
    cin >> tChar;

    int src = charToIndex(sChar);
    int dest = charToIndex(tChar);

    if (src == -1 || dest == -1) {
        cout << "Invalid source or destination node.\n";
        return 0;
    }

    pair<int, vector<int>> dijResult = dijkstra(src, dest, adj);
    int dijCost = dijResult.first;
    vector<int> dijParent = dijResult.second;
    
    pair<int, vector<int>> bfResult = bellmanFord(src, dest, edges);
    int bfCost = bfResult.first;
    vector<int> bfParent = bfResult.second;

    cout << "\n===== Dijkstra's Algorithm (Link State) =====\n";
    if (dijCost == INF) {
        cout << "No path found.\n";
    } else {
        cout << "Path: ";
        printPath(dijParent, src, dest);
        cout << "Total Cost: " << dijCost << '\n';
    }

    cout << "\n===== Bellman-Ford Algorithm (Distance Vector) =====\n";
    if (bfCost == INF) {
        cout << "No path found.\n";
    } else {
        cout << "Path: ";
        printPath(bfParent, src, dest);
        cout << "Total Cost: " << bfCost << '\n';
    }

    return 0;
}