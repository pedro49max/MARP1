#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include <sstream>
#include <climits>
#include <tuple>
using namespace std;

const int INF = INT_MAX;

struct Edge {
    int to, weight;
};

void solve() {//O((N+C)*logN)
    int N, C;
    while (cin >> N >> C) {
        vector<vector<Edge>> graph(N + 1);
        vector<vector<int>> normalGraph(N + 1);
        for (int i = 0; i < C; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({ v, w });
            graph[v].push_back({ u, w }); // Porque las calles son bidireccionales
            normalGraph[u].push_back(v);
            normalGraph[v].push_back(u);
        }

        int consultas; cin >> consultas;
        for (int i = 0; i < consultas; i++) {
            int a, b; cin >> a >> b;
            // Algoritmo de Dijkstra
            vector<int> dist(N + 1, INF);
            vector<int> counter(N + 1, 0); // Cantidad de formas de llegar a cada nodo
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

            dist[a] = 0;
            counter[a] = 0;
            pq.push({ 0, a }); // (distancia, nodo)

            while (!pq.empty()) {//O(N+C)
                pair<int, int> e = pq.top();//O(logN)
                pq.pop();

                if (e.first > dist[e.second]) continue;

                for (const auto& edge : graph[e.second]) {
                    int v = edge.to, w = edge.weight;

                    if (dist[e.second] + w < dist[v]) {
                        dist[v] = dist[e.second] + w;
                        counter[v] = counter[e.second] + 1;
                        pq.push({ dist[v], v });//O(logN)
                    }
                    else if (dist[e.second] + w == dist[v] && counter[v] > counter[e.second] + 1) {
                        counter[v] = counter[e.second] + 1;
                        pq.push({ dist[v], v });//O(logN)
                    }
                }
            }

            queue<pair<int, int>> xd;//counter, nodo
            vector<bool> visited(N + 1, false);
            vector<int> counters(N + 1, INF);
            visited[a] = true;
            xd.push({ 0,a });
            while (!xd.empty()) {//O(N+C)
                pair<int, int> e = xd.front();//O(logN)
                xd.pop();
                for (int x : normalGraph[e.second]) {
                    if (!visited[x] || (visited[x] && e.first + 1 < counters[x])) {
                        visited[x] = true;
                        counters[x] = e.first + 1;
                        if(x!=b)
                            xd.push({ e.first + 1, x });
                    }

                }
            }
            //cout << counters[b] << "==" << counter[b] << "\n\n";
            // La respuesta es la cantidad de formas de llegar al nodo N con la distancia mínima
            if (dist[b] == INF)
                cout << "SIN CAMINO" << endl;
            else {
                cout << dist[b];
                if(counters[b]==counter[b])
                    cout<< " SI" << endl;
                else
                    cout << " NO" << endl;
            }
        }
        cout << "---\n";
    }
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    solve();

    return 0;
}