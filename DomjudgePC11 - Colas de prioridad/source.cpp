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
    double votos;
    double escanos;
    double c;
    int id;
};

bool operator>(Nodo p1, Nodo p2) {
    return (p1.c < p2.c) ||(p1.c==p2.c && (p1.votos < p2.votos || (p1.votos == p2.votos && p1.id > p2.id)));
}

typedef priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;

void resuelveCaso() {
    int C, N;
    cin >> C >> N;
    while (C != 0 || N != 0) {
        pq nodos;
        for (int i = 0; i < C; i++) {
            Nodo x;
            cin >> x.votos;
            x.escanos = 0;
            x.id = i;
            x.c = x.votos;
            nodos.push(x);
        }
        for (int i = 0; i < N; i++) {
            Nodo x = nodos.top();nodos.pop();
            x.escanos++;
            x.c = x.votos / (1 + x.escanos);
            nodos.push(x);
        }
        vector<Nodo> listaNodos(C);
        for (int i = 0; i < C; i++) {
            Nodo x = nodos.top();nodos.pop();
            listaNodos[x.id] = x;
        }
        cout << listaNodos[0].escanos;
        for (int i = 1; i < C; i++) {
            cout << " " << listaNodos[i].escanos;
        }
        cout << endl;
        cin >> C >> N;
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