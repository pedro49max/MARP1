#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

struct movie {
    int init;
    int end;
    int duration;
};

bool operator>(movie t1, movie t2) {
    return (t1.end > t2.end) || (t1.end == t2.end && t1.init > t2.init);
}

typedef priority_queue<movie, vector<movie>, greater<movie>> pq;




void solve() {
    int N;
    while (cin >> N && N != 0) {
        pq movies;
        for (int i = 0; i < N; i++) {
            int h,m,duration; char aux; movie mov;
            cin >> h >> aux >> m >> duration;
            duration += 10;
            mov.init = h * 60 + m;
            mov.end = h * 60 + m + duration;
            mov.duration = duration;
            movies.push(mov);
        }
        int time = 0 , counter = 0;
        while (!movies.empty()) {
            movie mov = movies.top(); movies.pop();
            if (time <= mov.init) {
                counter++;
                time = mov.end;
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