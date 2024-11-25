#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include "Grafo.h"
using namespace std;

void dfs(const Grafo& grafo, int v, vector<bool>& visited, int& count, vector<bool> &group) {
    queue<int> q;
    visited[v] = true;
    group[v] = true;
    count++;
    for (int w : grafo.ady(v)) {
        if (!visited[w]) {
            dfs(grafo, w, visited, count, group);
        }
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int V,M;
    
    while(cin >> V >> M) { //O(V +A)
        Grafo grafo(V);
        for (int i = 0; i < M; ++i) {//O(A*M)
            int A;
            cin >> A;
            vector<int> amigos(A);
            for (int x = 0; x < A; x++) {
                int aux;
                cin >> aux;
                amigos[x]= aux - 1;
            }
            for (int a1 = 1; a1 < A; a1++) {
                grafo.ponArista(amigos[0], amigos[a1]);
            }
        }
        vector<int> component_size(V, 0);
        vector<bool> visited(V, false);
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) {
                vector<bool> group(V, false);
                int count = 0;
                dfs(grafo, v, visited, count, group);
                // Asignamos el tamaño de la componente a todos sus miembros
                for (int u = 0; u < V; ++u) {
                    if (group[u]) {
                        component_size[u] = count;
                    }
                }
            }
        }
        cout << component_size[0]; //O(V+A)
        for (int i = 1; i < V; i++) {
            cout << " " << component_size[i];
        }
        cout << "\n";
    }
    return 0;
}