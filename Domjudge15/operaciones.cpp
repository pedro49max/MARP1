#include <iostream>
#include<fstream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
  


int min_pulsations(int start, int target) {//Olog(n)
    vector<int> visited(10000, -1);
    queue<int> q;

    q.push(start);
    visited[start] = 0;  

   
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target) {
            return visited[current];  
        }

        
        int next_add = (current + 1) % 10000;       
        int next_mul = (current * 2) % 10000;       
        int next_div = current / 3;               

        
        if (visited[next_add] == -1) {
            visited[next_add] = visited[current] + 1;
            q.push(next_add);
        }

        if (visited[next_mul] == -1) {
            visited[next_mul] = visited[current] + 1;
            q.push(next_mul);
        }

        if (visited[next_div] == -1) {
            visited[next_div] = visited[current] + 1;
            q.push(next_div);
        }
    }

    return -1; 
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int start, target;

    while (cin >> start >> target) {
        cout << min_pulsations(start, target) << endl;
    }

    return 0;
}
