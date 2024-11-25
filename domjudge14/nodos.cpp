#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include "Grafo.h"
using namespace std;

class Amigos {
private:
    Grafo const& grafo;
    vector<bool> visitado;
    vector<int> ttls;

public:
    Amigos(Grafo const& g) : grafo(g), visitado(g.V(), false), ttls(g.V(), -1) {}

    int numContinuos(int nodo, int ttl) {//O(V+A)
        fill(visitado.begin(), visitado.end(), false);  // Reset visited
        fill(ttls.begin(), ttls.end(), -1);             // Reset TTLs

        int count = 0;
        queue<pair<int, int>> q;  // Pair of (node, ttl left)
        q.push({ nodo, ttl });
        visitado[nodo] = true;

        while (!q.empty()) {
            int current = q.front().first;
            int ttl_left = q.front().second;
            q.pop();
            count++;

            if (ttl_left > 0) {
                for (int vecino : grafo.ady(current)) {
                    if (!visitado[vecino]) {//might be cases that have been visited but with a sorter ttl
                        visitado[vecino] = true;
                        q.push({ vecino, ttl_left - 1 });
                    }
                }
            }
        }
        return count;
    }
};

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int V;
    while (cin >> V) { //O(k*(V +A))
        int  A;
        cin  >> A;
        Grafo grafo(V);

        for (int i = 0; i < A; ++i) {//O(A)
            int u, v;
            cin >> u >> v;
            grafo.ponArista(u - 1, v - 1);
        }
        int k;
        cin >> k;
        Amigos red(grafo);
        for (int i = 0; i < k; i++) {//O(k*(V+A))
            int nodo, ttl;
            cin >> nodo >> ttl;
            cout << V - red.numContinuos(nodo -1, ttl) << endl; //O(V+A)
        }
        cout << "---" << endl;


    }

    return 0;
}