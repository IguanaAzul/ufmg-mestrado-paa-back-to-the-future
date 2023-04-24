#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
const int INF = INT32_MAX;

int dijkstra(vector<vector<int>>& graph_matrix, int source, int destination) {
    const unsigned int n = graph_matrix.size();
    vector<int> dist(n, INF);
    dist[source] = 0;
    vector<int> parent(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < n; v++) {
            if (graph_matrix[u][v] != INF) {
                int weight = graph_matrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                    parent[v] = u;
                }
            }
        }
    }
    if (dist[destination] == INF) {
        return INF;
    }
    else{
        vector<int> path;
        int current = destination, previous = current;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
            if (current == -1) {
                break;
            }
            graph_matrix[current][previous] = INF;
            previous = current;
        }
        return dist[destination];
    }
}

int main() {
    int n_cities, n_flights, n_friends, n_sits, count = 0;
    while (cin >> n_cities >> n_flights) {
        count ++;
        vector<vector<int>> cost_matrix(n_cities, vector<int>(n_cities, INF));
        int a, b, c;
        for (int s = 0; s < n_flights; s++) {
            cin >> a >> b >> c;
            cost_matrix[a - 1][b - 1] = c;
            cost_matrix[b - 1][a - 1] = c;
        }
        cin >> n_friends >> n_sits;
        int sits, distance = 0, result = 0;
        cout << "Instancia " << count << endl;
        while (n_friends > 0){
            n_friends -= n_sits;
            if (n_friends < 0) {
                sits = n_sits + n_friends;
            } else {
                sits = n_sits;
            }
            distance = dijkstra(cost_matrix, 0, n_cities-1);
            if (distance == INF) {
                break;
            }
            else {
                result += distance * sits;
            }
        }
        if (distance == INF) {
            cout << "impossivel" << endl << endl;
        } else {
            cout << result << endl << endl;
        }
    }
    return 0;
}
