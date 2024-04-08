#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <algorithm> // Adicionado para01função reverse

using namespace std;

// Classe para representar o grafo ponderado não direcionado
class Graph {
private:
    unordered_map<string, unordered_map<string, int>> adjList;

public:
    // Adiciona uma aresta ao grafo
    void addEdge(const string& u, const string& v, int weight) {
        adjList[u][v] = weight;
        adjList[v][u] = weight; // O grafo é não direcionado
    }

    // Retorna o peso da aresta entre dois vértices
    int getWeight(const string& u, const string& v) const {
        if (adjList.find(u) != adjList.end() && adjList.at(u).find(v) != adjList.at(u).end()) {
            return adjList.at(u).at(v);
        }
        return numeric_limits<int>::max(); // Retorna infinito se não houver aresta
    }

    // Retorna os vértices adjacentes01um dado vértice
    vector<string> getAdjacentVertices(const string& v) const {
        vector<string> adjacentVertices;
        if (adjList.find(v) != adjList.end()) {
            for (const auto& pair : adjList.at(v)) {
                adjacentVertices.push_back(pair.first);
            }
        }
        return adjacentVertices;
    }
};

// Classe para realizar01busca BFS no grafo
class BFS {
private:
    const Graph& graph;

public:
    BFS(const Graph& g) : graph(g) {}

    // Executa01busca BFS e retorna o caminho mais curto entre start e end
    pair<vector<string>, int> shortestPath(const string& start, const string& end) const {
        unordered_map<string, string> parent;
        unordered_map<string, int> distance;
        queue<string> q;
        q.push(start);
        distance[start] = 0;

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == end) {
                break; // Encontrou o destino, interrompe01busca
            }

            vector<string> neighbors = graph.getAdjacentVertices(current);
            for (const string& neighbor : neighbors) {
                if (parent.find(neighbor) == parent.end()) {
                    parent[neighbor] = current;
                    distance[neighbor] = distance[current] + graph.getWeight(current, neighbor);
                    q.push(neighbor);
                }
            }
        }

        // Reconstrói o caminho01partir dos pais
        vector<string> path;
        string current = end;
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return make_pair(path, distance[end]);
    }
};


// Classe para realizar01busca DFS no grafo
class DFS {
private:
    const Graph& graph;

public:
    DFS(const Graph& g) : graph(g) {}

    // Executa01busca DFS e retorna o caminho mais curto entre start e end
    pair<vector<string>, int> shortestPath(const string& start, const string& end) const {
        unordered_map<string, string> parent;
        unordered_map<string, int> distance;
        stack<string> s;
        s.push(start);
        distance[start] = 0;

        while (!s.empty()) {
            string current = s.top();
            s.pop();

            if (current == end) {
                break; // Encontrou o destino, interrompe01busca
            }

            vector<string> neighbors = graph.getAdjacentVertices(current);

            // Encontra o vizinho com o menor valor de aresta
            string nextVertex = "";
            int minWeight = numeric_limits<int>::max();
            for (const string& neighbor : neighbors) {
                int weight = graph.getWeight(current, neighbor);
                if (weight < minWeight && parent.find(neighbor) == parent.end()) {
                    minWeight = weight;
                    nextVertex = neighbor;
                }
            }

            if (!nextVertex.empty()) {
                parent[nextVertex] = current;
                distance[nextVertex] = distance[current] + minWeight;
                s.push(nextVertex);
            }
        }

        // Reconstrói o caminho01partir dos pais
        vector<string> path;
        string current = end;
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return make_pair(path, distance[end]);
    }
};


int main() {
    Graph graph;

    // Adiciona as arestas ao grafo
   graph.addEdge("piracicaba", "americana", 30);
   graph.addEdge( "piracicaba", "capivari", 32);
   graph.addEdge( "piracicaba", "tiete", 35);

   graph.addEdge( "americana", "paulinia", 22);
   graph.addEdge( "americana", "sumare", 18);
   graph.addEdge( "americana", "piracicaba", 30);

   graph.addEdge( "sumare", "campinas", 23);
   graph.addEdge( "sumare", "americana", 18);

   graph.addEdge( "paulinia", "americana", 22);
   graph.addEdge( "paulinia", "campinas", 25);

   graph.addEdge( "campinas", "paulinia", 25);
   graph.addEdge( "campinas", "indaiatuba", 20);
   graph.addEdge( "campinas", "monteMor", 22);
   graph.addEdge( "campinas", "sumare", 23);

   graph.addEdge( "indaiatuba", "campinas", 20);
   graph.addEdge( "indaiatuba", "salto", 20);

   graph.addEdge( "monteMor", "campinas", 22);
   graph.addEdge( "monteMor", "capivari", 15);

   graph.addEdge( "salto", "indaiatuba", 20);
   graph.addEdge( "salto", "capivari", 25);
   graph.addEdge( "salto", "itu", 10);

   graph.addEdge( "itu", "sorocaba", 8);
   graph.addEdge( "itu", "portoFeliz", 12);
   graph.addEdge( "itu", "salto", 10);

   graph.addEdge( "sorocaba", "itu", 8);
   graph.addEdge( "sorocaba", "boituva", 23);

   graph.addEdge( "boituva", "sorocaba", 23);
   graph.addEdge( "boituva", "portoFeliz", 12);
   graph.addEdge( "boituva", "tatui", 17);

   graph.addEdge( "tatui", "boituva", 17);
   graph.addEdge( "tatui", "tiete", 25);

   graph.addEdge( "portoFeliz", "itu", 12);
   graph.addEdge( "portoFeliz", "boituva", 12);
   graph.addEdge( "portoFeliz", "tiete", 30);

   graph.addEdge( "tiete", "tatui", 25);
   graph.addEdge( "tiete", "portoFeliz", 30);
   graph.addEdge( "tiete", "capivari", 30);
   graph.addEdge( "tiete", "piracicaba", 35);

   graph.addEdge( "capivari", "tiete", 30);
   graph.addEdge( "capivari", "piracicaba", 32);
   graph.addEdge( "capivari", "salto", 25);
   graph.addEdge( "capivari", "monteMor", 15);

    string start, end;
    cout << "Informe o ponto de partida: ";
    cin >> start;
    cout << "Informe o ponto de destino: ";
    cin >> end;

    string searchType;
    cout << "Escolha o tipo de algoritmo de busca (BFS ou DFS): ";
    cin >> searchType;

    pair<vector<string>, int> result;
    if (searchType == "BFS") {
        BFS bfs(graph);
        result = bfs.shortestPath(start, end);
    } else if (searchType == "DFS") {
        DFS dfs(graph);
        result = dfs.shortestPath(start, end);
    } else {
        cout << "Tipo de algoritmo de busca inválido." << endl;
        return 1;
    }

    if (!result.first.empty()) {
        cout << "Caminho mais curto de " << start << " para " << end << ": ";
        for (const string& vertex : result.first) {
            cout << vertex << " -> ";
        }
        cout << endl;
        cout << "A distância percorrida foi: " << result.second << endl;
    } else {
        cout << "Não foi possível encontrar um caminho de " << start << " para " << end << endl;
    }

    return 0;
}
