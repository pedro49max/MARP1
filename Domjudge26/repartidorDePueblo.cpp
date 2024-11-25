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
    while (cin >> N) {
        vector<vector<Edge>> graph(N + 1);
        vector<vector<Edge>> inverseGraph(N + 1);
        int C;
        cin >> C;
        for (int i = 0; i < C; i++) {
            int u, v, t;
            cin >> u >> v >> t;
            //cout << "El maximo es " << N + 1 << " y tenemos " << u << "," << v << endl;
            graph[u].push_back({ v, t });//grafo dirigido
            inverseGraph[v].push_back({ u,t });
        }
        // Algoritmo de Dijkstra
        vector<int> dist(N + 1, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        int O, P;
        cin >> O>> P;
        dist[O] = 0;
        pq.push({ 0, O }); // (distancia, nodo)

        while (!pq.empty()) {//O(N+C)
            pair<int, int> e = pq.top();//O(logN)
            pq.pop();

            if (e.first > dist[e.second]) continue;

            for (const auto& edge : graph[e.second]) {
                int v = edge.to;
                int esfuerzoToV = edge.time;
                int totalEsfuerzo = e.first + esfuerzoToV;

                if (totalEsfuerzo < dist[v]) {
                    dist[v] = totalEsfuerzo;
                    pq.push({ dist[v], v });//O(logN)
                }
            }
        }
        vector<int> distBack(N + 1, INF);
        distBack[O] = 0;
        pq.push({ 0,O });
        while (!pq.empty()) {//O(N+C)
            pair<int, int> e = pq.top();//O(logN)
            pq.pop();

            if (e.first > distBack[e.second]) continue;

            for (const auto& edge : inverseGraph[e.second]) {
                int v = edge.to;
                int esfuerzoToV = edge.time;
                int totalEsfuerzo = e.first + esfuerzoToV;

                if (totalEsfuerzo < distBack[v]) {
                    distBack[v] = totalEsfuerzo;
                    pq.push({ distBack[v], v });//O(logN)
                }
            }
        }
        int sum = 0;
        for (int pl = 0; pl < P; pl++) {
            int x; cin >> x;
            if (dist[x] == INF || distBack[x] == INF)
                sum = -1;
            else if (sum != -1)
                sum += dist[x] + distBack[x];
        }
        
        
        // La respuesta es la cantidad de formas de llegar al nodo N con la distancia mínima
        if (sum == -1)
            cout << "Imposible" << endl;
        else
            cout << sum << endl;
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