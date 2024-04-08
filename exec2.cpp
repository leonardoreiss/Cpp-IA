#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

// Estrutura para representar uma aresta no grafo
struct Edge {
    int dest, weight;
};

// Função para imprimir o caminho mais curto
void printShortestPath(const vector<int>& parent, int startVertex, int endVertex) {
    cout << "Caminho mais curto de P1 à Loja:" << endl;
    vector<int> path;
    int currentVertex = endVertex;
    while (currentVertex != startVertex) {
        path.push_back(currentVertex);
        currentVertex = parent[currentVertex];
    }
    path.push_back(startVertex);
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i != 0)
            cout << " -> ";
    }
    cout << endl;
}

// Função que implementa o algoritmo de Dijkstra
void dijkstra(const vector<vector<Edge>>& graph, int V, int startVertex, int endVertex) {
    // Vetor para armazenar as distâncias mínimas do vértice inicial para todos os outros vértices
    vector<int> dist(V, INT_MAX); 
    
    // Vetor para armazenar o pai de cada vértice no caminho mais curto
    vector<int> parent(V, -1); 
    
    // Fila de prioridade para armazenar os vértices a serem explorados,
    // ordenados com base nas distâncias mínimas
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    
    // A distância do vértice inicial para ele mesmo é 0
    dist[startVertex] = 0;
    
    // Adiciona o vértice inicial na fila de prioridade
    pq.push({0, startVertex});

    // Loop principal do algoritmo de Dijkstra
    while (!pq.empty()) {
        // Extrai o vértice com a menor distância da fila de prioridade
        int u = pq.top().second;
        pq.pop();

        // Itera sobre todas as arestas saindo do vértice atual
        for (const Edge& edge : graph[u]) {
            int v = edge.dest; // Vértice de destino da aresta
            int weight = edge.weight; // Peso da aresta

            // Se uma distância menor for encontrada através deste vértice, atualize a distância e o pai
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                
                // Adiciona o vértice atualizado na fila de prioridade
                pq.push({dist[v], v});
            }
        }
    }

    // Verifica se foi possível criar um caminho para o destino
    if (dist[endVertex] == INT_MAX) {
        cout << "Não foi possível encontrar um caminho para a loja." << endl;
    } else {
        // Se sim, imprime a distância total percorrida e o caminho mais curto
        cout << "Distância total percorrida: " << dist[endVertex] << endl;
        printShortestPath(parent, startVertex, endVertex);
    }
}

int main() {
    // Impressão do diagrama do grafo
    cout << "[01]------->[02]------>[03]        \n";
    cout << " |           ^          |          \n";
    cout << " v           |          |          \n";
    cout << "[04]------->[05]        |          \n";
    cout << " |           ^          |          \n";
    cout << " |           |          |          \n";
    cout << " v           v          v          \n";
    cout << "[06]->[07]->[08]------>[09]----¬   \n";
    cout << " |     |     ^          |      |   \n";
    cout << " |     |     |          |      |   \n";
    cout << " |     |     v          |      |   \n";
    cout << " |     L--->[10]        |      |   \n";
    cout << " |           ^          |      |   \n";
    cout << " v           |          v      v   \n";
    cout << "[11]--------[12]---->[13]<--[14] \n";

    const int V = 15;
    vector<vector<Edge>> graph(V);

    // Preenchimento do grafo com as arestas e pesos
    graph[1].push_back({2, 10});
    graph[2].push_back({3, 13});
    graph[1].push_back({4, 8});
    graph[4].push_back({5, 7});
    graph[4].push_back({6, 10});
    graph[5].push_back({8, 7}); 
    graph[6].push_back({7, 9});
    graph[8].push_back({7, 4});
    graph[7].push_back({10, 4});
    graph[8].push_back({5, 7}); 
    graph[5].push_back({2, 6});
    graph[3].push_back({9, 9}); 
    graph[8].push_back({9, 10});
    graph[6].push_back({11, 12});
    graph[11].push_back({12, 14});
    graph[12].push_back({13, 20});
    graph[9].push_back({13, 16});
    graph[9].push_back({14, 11});
    graph[14].push_back({13, 5});
    graph[10].push_back({12, 9});
    graph[12].push_back({10, 9});
    graph[10].push_back({12, 5});

    int startVertex;

    // Solicitação da nova localização de P1 ao usuário
    cout << "Insira a nova localização de P1 (1 a 14): ";
    cin >> startVertex;

    // Verificação da entrada do usuário
    if (startVertex < 1 || startVertex > 14) {
        cout << "Localização inválida. Insira um número entre 1 e 14." << endl;
        return 1;
    }

    // Execução do algoritmo de Dijkstra
    dijkstra(graph, V, startVertex, 9); // Loja é o vértice 9

    return 0;
}
