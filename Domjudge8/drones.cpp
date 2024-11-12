#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;
typedef priority_queue<int, vector<int>, less<int>> pq;



bool solve(int N, int A,int  B) {
	pq pilas9v;
	pq pilas15v;
	int v;
	for (int i = 0; i < A; i++) {
		cin >> v;
		pilas9v.push(v);
	}
	for (int i = 0; i < B; i++) {
		cin >> v;
		pilas15v.push(v);
	}
	bool first = true;
	while (!pilas9v.empty() && !pilas15v.empty()) {
		int horas = 0;
		pq pilas9vReutilizar;
		pq pilas15vReutilizar;
		for (int i = 0; i < N && (!pilas9v.empty() && !pilas15v.empty()); i++) {
			int vatios9 = pilas9v.top(); pilas9v.pop();
			int vatios15 = pilas15v.top(); pilas15v.pop();
			if (vatios9 > vatios15) {
				horas += vatios15;
				pilas9vReutilizar.push(vatios9 - vatios15);
			}
			else if (vatios9 < vatios15) {
				horas += vatios9;
				pilas15vReutilizar.push(vatios15 - vatios9);
			}
			else
				horas += vatios9;
		}
		while (!pilas15vReutilizar.empty()) {
			pilas15v.push(pilas15vReutilizar.top()); pilas15vReutilizar.pop();
		}
		while (!pilas9vReutilizar.empty()) {
			pilas9v.push(pilas9vReutilizar.top()); pilas9vReutilizar.pop();
		}
		if (!first)
			cout << " ";
		first = false;
		cout << horas;
	}
	cout << endl;

	return true;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int A, B,N;
	while ((cin >> N >> A >> B) && solve(N, A, B));
		
	return 0; 
}