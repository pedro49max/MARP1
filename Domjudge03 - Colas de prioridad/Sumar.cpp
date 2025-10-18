#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef priority_queue<long long, vector<long long>, greater<long long>> pq;

bool solve_s() {//O(N log N)
	int N;
	cin >> N;
	if (N == 0)
		return false;

	pq sums;
	long long a;
	for (int i = 0; i < N; ++i) {//N veces
		cin >> a;
		sums.push(a);//push log(n)
	}

	long long cost = 0, sumand1, sumand2, sum;
	while (sums.size() > 1) {//n-1 veces
		sumand1 = sums.top(); sums.pop();//pop log(n)
		sumand2 = sums.top(); sums.pop();//pop log(n)
		sum = sumand1 + sumand2;
		cost += sum;
		sums.push(sum);//push log(n)
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
