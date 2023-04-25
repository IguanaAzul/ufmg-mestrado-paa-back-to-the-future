// Trabalho de Projeto e Análise em Algoritmos - DCC UFMG.
// Ramon Griffo Costa.
// Problema de mínimo custo e máximo fluxo (min-cost max-flow)
// Temos dado o grafo com as arestas com peso e capacidade.
// Temos o fluxo desejado, o algoritmo deve responder o custo mínimo para esse fluxo se ele for possível.
// Se não for, deve responder "impossivel".

#include <iostream>
#include <queue>
#include <vector>

const int INF = INT32_MAX;
using namespace std;

struct edge {
    int vertex_1, vertex_2, next, cost, capacity;
    explicit edge(int vertex_1 = 0, int vertex_2 = 0, int next = 0, int cost = 0, int capacity = 0)
            : vertex_1(vertex_1)
            , vertex_2(vertex_2)
            , next(next)
            , cost(cost)
            , capacity(capacity)
    {
    }
};

int addEdge(int vertex_1, int vertex_2, int cost, int capacity, int edge_count, vector<int>& previous, vector<edge>& graph) {
    // Aresta adicionada ao grafo.
    graph[edge_count] = edge(vertex_1, vertex_2, previous[vertex_1], cost, capacity);
    previous[vertex_1] = edge_count++;

    // Aresta de retorno, inicializada com capacidade 0 e custo negativo,
    // só vai ser utilizada depois que o augment executar e permitir retorno.
    // Possibilita que outros caminhos sejam testados que não seja o mínimo.
    graph[edge_count] = edge(vertex_2, vertex_1, previous[vertex_2], -cost, 0);
    previous[vertex_2] = edge_count++;
    return edge_count;
}

int augment(int vertex, vector<int>& parents, vector<edge>& graph) {
    int flow = INF;
    for (int i = parents[vertex]; i != -1; i = parents[graph[i].vertex_1]) {
        flow = min(flow, graph[i].capacity);    // Caputa a menor capacidade de todas as arestas no caminho.
    }

    for (int i = parents[vertex]; i != -1; i = parents[graph[i].vertex_1]) {
        graph[i].capacity -= flow;
        graph[i + 1].capacity += flow;  // Ajusta as arestas de retorno para permitir retorno caso haja outro caminho
        // melhor para o fluxo ótimo.
    }
    return flow;
}

// Algoritmo de Dijkstra adaptado
int dijkstra(int origin, int destination, int n_vertices, vector<int>& previous, vector<int>& parents, const vector<edge>& graph) {
    vector<int> distances(n_vertices + 2, INF);
    vector<bool> visited(n_vertices + 1, false);
    queue<int> priority_queue;
    distances[origin] = 0;
    visited[origin] = true;
    priority_queue.emplace(origin);

    while (!priority_queue.empty()) {
        int u = priority_queue.front();
        priority_queue.pop();
        for (int i = previous[u]; i != -1; i = graph[i].next) {
            int v = graph[i].vertex_2;
            if (graph[i].capacity && distances[u] + graph[i].cost < distances[v]) {
                distances[v] = distances[u] + graph[i].cost;
                parents[v] = i;
                if (!visited[v]) {
                    visited[v] = true;
                    priority_queue.emplace(v);
                }
            }
        }
        visited[u] = false;
    }
    return distances[destination];
}

int main() {
    int count = 0;
    int n_cities, n_flights, edge_count, n_friends, n_sits_per_flight;

    while (cin >> n_cities >> n_flights) { // Leitura iterativa de cada instância, quando não houver mais, interrompe.
        count ++;
        cout << "Instancia " << count << endl;
        edge_count = 0; // Contador do número de arestas no grafo.
        vector<edge> graph(n_cities * n_flights + 4);   // Vetor das arestas do grafo
        // (número de cidades * número de vôos + as 4 arestas artificiais).
        vector<int> previous(n_cities + 2, -1); // Vetor para salvar a aresta previous de cada vértice.
        vector<int> parents(n_cities + 2, -1);  // Vetor para salvar a aresta pai de cada vértice e possibilitar
        // a reconstrução dos caminhos descobertos no algoritmo de caminho mínimo para utilizar na função augment.
        vector<int> a(n_flights), b(n_flights), c(n_flights); // Vetores para leitura das informações de
        // origem, destino e custo de cada vôo.
        for (int i = 0; i < n_flights; i++) {
            cin >> a[i] >> b[i] >> c[i];
        }
        cin >> n_friends >> n_sits_per_flight;
        // Arestas artificiais de entrada e saída do fluxo (Vértices 0 e n_cities + 1 são artificiais).
        // Arestas de custo 0 e capacidade n_friends.
        edge_count = addEdge(0, 1, 0, n_friends, edge_count, previous, graph);
        edge_count = addEdge(n_cities, n_cities + 1, 0, n_friends, edge_count, previous, graph);
        for (int i = 0; i < n_flights; i++) {
            // Adiciona aresta no grafo, como descrito na leitura das informações a, b, c (origem, destino e custo).
            // E com capacidade igual ao número de assentos por vôo (n_sits_per_flight).
            edge_count = addEdge(a[i], b[i], c[i], n_sits_per_flight, edge_count, previous, graph);
            // No caso desse problema, como descrito no enunciado, para cada vôo de ida, temos um vôo de volta identico em custo e capacidade.
            edge_count = addEdge(b[i], a[i], c[i], n_sits_per_flight, edge_count, previous, graph);
        }
        int max_flow = 0, resp = 0;
        // Encontra o caminho de menor custo da origem para o destino e retorna o custo.
        int shortest_path = dijkstra(0, n_cities + 1, n_cities, previous, parents, graph);
        while (shortest_path != INF) {
            int flow = augment(n_cities + 1, parents, graph); // Aumenta o fluxo pelo caminho.
            max_flow += flow;
            resp += shortest_path * flow;
            if (max_flow == n_friends) { // Fluxo desejado já atingido.
                break;
            }
            // Recalcula custo do caminho mínimo com as capacidades atualizadas.
            shortest_path = dijkstra(0, n_cities + 1, n_cities, previous, parents, graph);
        }
        if (max_flow != n_friends) {
            cout << "impossivel" << endl << endl;
        }
        else {
            cout << resp << endl << endl;
        }
    }
    return 0;
}
