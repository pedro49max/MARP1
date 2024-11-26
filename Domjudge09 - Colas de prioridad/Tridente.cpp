#include "IndexPQ.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

#define MAX 1000000

struct Cita {
	string name;
	long n;
	long t;
};

struct Hash {
	long n;
	long i;
	long t;
};

typedef Cita ii;
typedef Hash ih;

bool operator>(ii q1, ii q2) {
	return (q1.n > q2.n) || (q1.n == q2.n && q1.t >= q2.t);
}

typedef IndexPQ<ii, greater<ii>> pqi;
typedef unordered_map<string, ih> idx;

void printFirst(long n, pqi& indexpq) {
	if (indexpq.empty()) return;
	stack<pair<long, ii>> store;

	auto top = indexpq.top();

	int c = 1;
	while (!indexpq.empty() && c <= 3) {
		top = indexpq.top(); indexpq.pop();
		if (top.prioridad.n == 0) break;
		store.push({ top.elem, top.prioridad });
		cout << c << " " << top.prioridad.name << "\n";
		++c;
	}
	while (!store.empty()) {
		auto entry = store.top(); store.pop();
		indexpq.push(entry.first, entry.second);
	}
}

bool solve_tri() {
	long n = MAX;
	if (!(cin >> n))
		return false;

	pqi x(n);
	idx indexes;

	string type;
	ii e;
	for (int i = 0; i < n; ++i) {
		cin >> type;
		if (type == "TC") {
			printFirst(3, x);
		}
		else if (type == "C") {
			cin >> e.name >> e.n;
			long a = e.t = i;
			if (indexes.find(e.name) != indexes.end()) {
				a = indexes[e.name].i;
				e.n += indexes[e.name].n;
				x.update(a, e);
			}
			else {
				x.push(a, e);
			}
			indexes[e.name] = { e.n, a, e.t };
		}
		else if (type == "E") {
			cin >> e.name >> e.n;
			long a = e.t = i;
			if (indexes.find(e.name) != indexes.end()) {
				a = indexes[e.name].i;
				e.t = indexes[e.name].t; // if you remove the time mark is not updated
				e.n = indexes[e.name].n - e.n;
				x.update(a, e);
			}
			indexes[e.name] = { e.n, a, e.t };
		}
	}
	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (solve_tri());
	return 0;
}