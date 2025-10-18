#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include<queue>
#include<map>
#include<set>
#include<string>
#include <sstream>

using namespace std;

struct Nodo {
    int musicos;
    int partituras;
    int c;
};

bool operator>(Nodo p1, Nodo p2) {
    return (p1.c < p2.c);
}

typedef priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;

void resuelveCaso() {
    int p,n;
    while (cin >> p >> n) {
        pq nodos;
        for (int i = 0; i < n; i++) {
            Nodo x;
            cin >> x.musicos;
            x.partituras = 1;
            x.c = x.musicos;
            nodos.push(x);
        }
        p -= n;
        while (p > 0) {
            Nodo x = nodos.top();nodos.pop();
            x.partituras++;
            p--;
            if(x.musicos % x.partituras == 0)
                x.c = x.musicos / x.partituras;
            else
                x.c = (x.musicos / x.partituras) + 1;
            
            nodos.push(x);
        }
        Nodo x = nodos.top();
        cout << x.c << endl;
    }
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}