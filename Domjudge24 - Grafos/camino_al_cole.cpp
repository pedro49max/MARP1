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
        for (int i = 0; i < C; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({ v, w });
            graph[v].push_back({ u, w }); // Porque las calles son bidireccionales
        }

        // Algoritmo de Dijkstra
        vector<int> dist(N + 1, INF);
        vector<int> ways(N + 1, 0); // Cantidad de formas de llegar a cada nodo
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[1] = 0;
        ways[1] = 1;
        pq.push({ 0, 1 }); // (distancia, nodo)

        while (!pq.empty()) {//O(N+C)
            pair<int, int> e = pq.top();//O(logN)
            pq.pop();

            if (e.first > dist[e.second]) continue;

            for (const auto& edge : graph[e.second]) {
                int v = edge.to, w = edge.weight;

                if (dist[e.second] + w < dist[v]) {
                    dist[v] = dist[e.second] + w;
                    ways[v] = ways[e.second];
                    pq.push({ dist[v], v });//O(logN)
                }
                else if (dist[e.second] + w == dist[v]) {
                    ways[v] += ways[e.second];
                }
            }
        }

        // La respuesta es la cantidad de formas de llegar al nodo N con la distancia mínima
        cout << ways[N] << endl;
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