#include<iostream>
#include<fstream>
#include<vector>
using namespace std;


int minCintas(vector<int> const& D, int K) {
    int cintas = 0;
    bool cinta = false;
    int distance =0; // kilómetros andados desde la última parada
    for (int i = 0; i < D.size(); ++i) { // estamos en gi
        if (!cinta) {
            cintas++;
            distance = 0;
            cinta = true;
        }
        else {
            if (distance + D[i] < K)
                distance += D[i];
            else if (distance + D[i] == K)
                cinta = false;
            else {
                cintas++;
                distance = 0;
            }
        }
    }
    return cintas;
}

void solve() {
    int N, L;
    while (cin >> N >> L) {
        vector<int> manguera(N);
        int prev = 0;
        for (int i = 0; i < N; i++) {
            int aux;
            cin >> aux;
            manguera[i] = aux - prev;
            prev = aux;
        }
        cout << minCintas(manguera, L) << endl;
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