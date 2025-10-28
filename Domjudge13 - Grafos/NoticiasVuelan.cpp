#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include"ConjuntosDisjuntos.h"
using namespace std;




void solve() {
    int N, M;
    while (cin >> N >> M) {
        ConjuntosDisjuntos conjuntos(N);
        for (int i = 0; i < M; i++) {
            int f;
            cin >> f;
            int a;
            if (f > 0)
                cin >> a;
            for (int j = 1; j < f; j++) {
                int b;
                cin >> b;
                conjuntos.unir(a - 1, b - 1);
            }
        }
        if (N > 0)
            cout << conjuntos.tam(0);
        for (int i = 1; i < N; i++) {
            cout << " " << conjuntos.tam(i);
        }
        cout << endl;
    }
}

int main() {
        // Para la entrada por fichero.
            // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    solve();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}