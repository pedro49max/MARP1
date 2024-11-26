#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef priority_queue<long long, vector<long long>, greater<long long>> pq;

bool solve_s() {
	int N;
	cin >> N;
	if (N == 0)
		return false;

	pq sums;
	long long a;
	for (int i = 0; i < N; ++i) {
		cin >> a;
		sums.push(a);
	}

	long long cost = 0, sumand1, sumand2, sum;
	while (sums.size() > 1) {
		sumand1 = sums.top(); sums.pop();
		sumand2 = sums.top(); sums.pop();
		sum = sumand1 + sumand2;
		cost += sum;
		sums.push(sum);
	}

	cout << cost << endl;

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int c = 1;
	while (solve_s()) ++c;
	return 0;
}
