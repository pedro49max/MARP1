#include <iostream>
#include<fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

class ArbolLibre {
private:
    Grafo const& grafo;
    vector<bool> visitado;
    bool tieneCiclo;

public:
    ArbolLibre(Grafo const& g) : grafo(g), visitado(g.V(), false), tieneCiclo(false) {}

    bool dfs(int nodo, int padre) {
        visitado[nodo] = true;
        for (int vecino : grafo.ady(nodo)) {
            if (!visitado[vecino]) {
                if (!dfs(vecino, nodo))
                    return false;
            }
            else if (vecino != padre) {
                tieneCiclo = true;
                return false;
            }
        }
        return true;
    }

    bool esArbolLibre() {
        if (!dfs(0, -1))
            return false;

        for (bool v : visitado) {
            if (!v)
                return false;
        }

        return !tieneCiclo;
    }
};

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int V, A;
    while (cin >> V >> A) { //O(V +A)
        Grafo grafo(V);

        for (int i = 0; i < A; ++i) {//O(A)
            int u, v;
            cin >> u >> v;
            grafo.ponArista(u, v);
        }


        if (A != V - 1) {//O(1)
            cout << "NO" << endl;
            continue;
        }


        ArbolLibre arbol(grafo);
        if (arbol.esArbolLibre()) {//O(V + A)
            cout << "SI" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
