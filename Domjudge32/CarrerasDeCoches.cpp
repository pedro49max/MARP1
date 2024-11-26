#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;



typedef priority_queue<int, vector<int>, greater<int>> pqLtM;
typedef priority_queue<int, vector<int>, less<int>> pqMtL;


void solve() {
    int casos;
    cin >> casos;
    for (int pl = 0; pl < casos; pl++) {
        int N, carga;
        cin >> N >> carga;
        pqLtM creciente;
        pqMtL decreciente;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            creciente.push(x);
            decreciente.push(x);
        }
        int counter = 0, index= 0, otherIndex = N-1;
        //cout << "STRATING INDEXES: index=" << index << " otherIndex=" << otherIndex << endl;
        while (!decreciente.empty() && !creciente.empty() && otherIndex > index) {
            //cout << "index=" << index << " otherIndex=" << otherIndex << endl;
            int grande = decreciente.top(); decreciente.pop();
            int peque = creciente.top(); creciente.pop();
            
            if (grande + peque >= carga) {
                counter++;
                //cout << "Counter = " << counter << endl;
            }
            else  {
                while (!creciente.empty() && grande + peque < carga && otherIndex > index) {
                    peque = creciente.top(); creciente.pop();
                    otherIndex--;
                    //cout << "index=" << index << " otherIndex=" << otherIndex << endl;
                }
                if (grande + peque >= carga && otherIndex > index) {
                    counter++;
                    //cout << "Counter = " << counter << endl;
                }
            }
            index++; otherIndex--;
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