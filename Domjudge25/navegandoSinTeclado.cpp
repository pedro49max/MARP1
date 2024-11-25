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
    int to, time;
};

void solve() {//O((N+C)*logN)
    int N;
    while (cin >> N && N!= 0) {
        vector<int>delays(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> delays[i];
        }
        vector<vector<Edge>> graph(N + 1);
        int C;
        cin >> C;
        for (int i = 0; i < C; i++) {
            int u, v, t;
            cin >> u >> v >> t;
            graph[u].push_back({ v, t });//grafo dirigido
        }

        // Algoritmo de Dijkstra
        vector<int> dist(N + 1, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[1] = delays[1];
        pq.push({ dist[1], 1 }); // (distancia, nodo)

        while (!pq.empty()) {//O(N+C)
            pair<int, int> e = pq.top();//O(logN)
            pq.pop();

            if (e.first > dist[e.second]) continue;

            for (const auto& edge : graph[e.second]) {
                int v = edge.to;
                int timeToV = edge.time;
                int totalTime = e.first + timeToV + delays[v];

                if (totalTime < dist[v]) {
                    dist[v] = totalTime;
                    pq.push({ dist[v], v });//O(logN)
                }
            }
        }

        // La respuesta es la cantidad de formas de llegar al nodo N con la distancia mínima
        if (dist[N] == INF)
            cout << "Imposible" << endl;
        else
            cout << dist[N] << endl;
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