#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;

struct edificio {
    int start;
    int finish;
};

bool operator>(edificio p1, edificio p2) {
    return (p1.finish > p2.finish);
}

typedef priority_queue<edificio, vector<edificio>, greater<edificio>> pq;


void solve() {
    int N; 
    while (cin >> N && N != 0) {
        pq edificios;
        for (int i = 0; i < N; i++) {
            int s, f;
            cin >> s >> f;
            edificio ed; ed.start = s; ed.finish = f;
            edificios.push(ed);
        }
        int counter = 0;
        bool newOne = true;
        int finish = 0;
        while (!edificios.empty()) {
            edificio ed = edificios.top(); edificios.pop();
            if (newOne) {
                counter++;
                finish = ed.finish;
                newOne = false;
            }
            else {
                if (ed.start > finish) {
                    counter++;
                    finish = ed.finish;
                }
                else if (ed.start == finish) {
                    newOne = true;
                    edificios.push(ed);
                }
            }
        }
        cout << counter << endl;
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