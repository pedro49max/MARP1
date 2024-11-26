#include <stdio.h>
#include <iostream>
#include<fstream>
#include<vector>
#include<queue>;
#include "GrafoValorado.h"
#include"ConjuntosDisjuntos.h"
#include"PriorityQueue.h"
using namespace std;



class Aeropuerto {
    int cost;
    int Aero;
public:
    //O(A*(log(A))
    Aeropuerto(GrafoValorado<int> const& g, int A) : cost(0), Aero(0){
        Aero = g.V();
        PriorityQueue<Arista<int>> pq(g.aristas());//O(A*(log(A))
        ConjuntosDisjuntos cjtos(g.V());//O(V)
        vector<Arista<int>> _ARM;
        bool sigue = true;
        while (!pq.empty() && _ARM.size() < g.V() - 1 && sigue) {
            auto a = pq.top(); pq.pop();//O(log(A))
            int v = a.uno(), w = a.otro(v);
            if (a.valor() >= A)
                sigue = false;
            else if (!cjtos.unidos(v, w) && _ARM.size() < g.V() - 1) {//O(log(V))
                cjtos.unir(v, w);//O(log(V))
                Aero--;
                _ARM.push_back(a); cost += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        cost += Aero * A;

    }
    int coste() {
        return cost;
    }
    int aeropuertos() {
        return Aero;
    }
};


bool resuelveCaso() {
    int V, E, A;
    cin >> V >> E >> A;
    if (!cin) return false;
    GrafoValorado<int> grafo(V);
    int u, v, c;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> c;
        grafo.ponArista({ u - 1,v - 1,c });
    }

    Aeropuerto solucion(grafo, A);

    cout << solucion.coste() << ' ' << solucion.aeropuertos() << '\n';
    return true;
}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;

}
