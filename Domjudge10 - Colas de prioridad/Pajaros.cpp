#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef priority_queue<long long, vector<long long>, greater<long long>> pq_old;
typedef priority_queue<long long, vector<long long>, less<long long>> pq_young;

bool solve_pa() {
	int first, N;
	cin >> first >> N;
	if (first == 0 && N == 0)
		return false;

	pq_old old;
	pq_young young;

	int p1, p2;
	while (N) {
		cin >> p1 >> p2;
		if (p1 < first) {
			young.push(p1);
			if (p2 < first) {
				young.push(p2);
				old.push(first);
				first = young.top(); young.pop();
			}
			else {
				old.push(p2);
			}
		}
		else {
			old.push(p1);
			if (p2 < first) {
				young.push(p2);
			}
			else {
				old.push(p2);
				young.push(first);
				first = old.top(); old.pop();
			}
		}
		cout << first << " ";
		--N;
	}
	cout << "\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (solve_pa());
	return 0;
}