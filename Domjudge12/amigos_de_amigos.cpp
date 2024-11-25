#include <iostream>
#include<fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

class Amigos {
private:
    Grafo const& grafo;
    vector<bool> visitado;
    int maxNum;

public:
    Amigos(Grafo const& g) : grafo(g), visitado(g.V(), false), maxNum(0) {}

    void dfs(int nodo, int &num) {
        visitado[nodo] = true;
        num++;
        for (int vecino : grafo.ady(nodo)) {
            if (!visitado[vecino]) {
                dfs(vecino, num);
            }
        }
    }

    int maxGrupo(int V) {
        for (int i = 0; i < V; i++) {
            int x = 0;
            if (!visitado[i])
                dfs(i, x);
            if (x > maxNum)
                maxNum = x;
        }
        return maxNum;
    }
};

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int n;
    cin >> n;
    for(int k = 0; k < n; k++) { //O(V +A)
        int V, A;
        cin >> V >> A;
        Grafo grafo(V);

        for (int i = 0; i < A; ++i) {//O(A)
            int u, v;
            cin >> u >> v;
            grafo.ponArista(u -1, v -1);
        }

        Amigos red(grafo);
        cout << red.maxGrupo(V) << endl; //O(V+A)
    

    }

    return 0;
}