#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

const long long INF = 10e8;

typedef pair<long, long> ii;

struct Period {
	ii t;
	long long p = INF;
};

bool operator>(Period p1, Period p2) {
	return (p1.t.first > p2.t.first) || (p1.t.first == p2.t.first && p1.t.second > p2.t.second);
}

typedef priority_queue<Period, vector<Period>, greater<Period>> pq;

// O(mlogn)
bool conflict(int T, pq& tasks) {
	long long begin = 0;
	Period curr = tasks.top(); tasks.pop();
	while (!tasks.empty() && curr.t.first < T) {
		if (curr.t.first < begin)
			return true;
		begin = curr.t.second;
		curr.t.first += curr.p;
		curr.t.second += curr.p;
		tasks.push(curr);
		curr = tasks.top(); tasks.pop();
	}
	return false;
}

bool solve_mu() {
	string str;
	getline(cin, str);

	if (str == "")
		return false;

	stringstream ss(str);
	int N, M, T;
	ss >> N >> M >> T;

	pq tasks;
	Period p;
	for (int i = 0; i < N; ++i) {
		cin >> p.t.first >> p.t.second;
		tasks.push(p);
	}
	for (int i = 0; i < M; ++i) {
		cin >> p.t.first >> p.t.second >> p.p;
		tasks.push(p);
	}
	if (N != 0 || M != 0)
		cin.ignore();

	string res = (conflict(T, tasks) ? "SI" : "NO");
		
	cout << res << "\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("mult.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int c = 1;
	while (solve_mu()) ++c;
	return 0;
}