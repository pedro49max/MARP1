#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;





typedef priority_queue<int, vector<int>, greater<int>> pq;




void solve() {
    int N;
    while (cin >> N) {
        pq defensa, ataque;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            ataque.push(x);
        }
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            defensa.push(x);
        }
       /*for (int i = 0; i < N; i++) {
            int def = defensa.top(), atq = ataque.top();
            defensa.pop(); ataque.pop();
            cout << def << " vs " << atq << endl;
        }*/
        int counter = 0;
        while (!defensa.empty() && !ataque.empty()) {
            int def = defensa.top(), atq = ataque.top(); 
            defensa.pop(); ataque.pop();
            if (atq <= def)
                counter++;
            else
                ataque.push(atq);
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