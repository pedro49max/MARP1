#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;

struct periodo {
    int start;
    int finish;
};

bool operator>(periodo p1, periodo p2) {
    return (p1.start > p2.start) || (p1.start == p2.start && p1.finish > p2.finish);
}

typedef priority_queue<periodo, vector<periodo>, greater<periodo>> pq;

void solve() {
    int C, F, N;
    while (cin >> C >> F >> N && (C != 0 || F != 0 || N != 0)) {
        pq trabajos;
        for (int i = 0; i < N; i++) {
            periodo p;
            cin >> p.start >> p.finish;
            trabajos.push(p);
        }
        int counter = 0, finish = C, longuest = C;
        bool chance = false;
        while (!trabajos.empty()) {
            periodo p = trabajos.top(); trabajos.pop();
            if (p.start <= finish && p.finish > longuest) {
                longuest = p.finish;
            }
            else if (p.start > finish) {
                finish = longuest;
                counter++;
                if (p.start > finish || finish >= F)
                    break;
                else
                    trabajos.push(p);
            }
        }
        if (finish < F && finish < longuest)
            counter++;
        finish = max(longuest, finish);
        if (finish < F)
            cout << "Imposible" << endl;
        else
            cout << counter<< endl;
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