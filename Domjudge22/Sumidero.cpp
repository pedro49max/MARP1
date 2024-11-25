#include<iostream>
#include<fstream>
#include"Grafo.h"
#include<vector>
using namespace std;


int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int V;
	while (cin >> V){
		int A;
		cin >> A;
		Grafo directo(V);
		Grafo inverso(V);
		for (int i = 0; i < A; i++) {
			int a, b;
			cin >> a >> b;
			directo.ponArista(a, b);
			inverso.ponArista(b, a);
		}
		int sumidero = -1;
		for (int i = 0; i < V && sumidero == -1; i++) {
			if (directo.ady(i).empty() && inverso.ady(i).size() == V - 1)
				sumidero = i;
		}
		if (sumidero == -1) {
			cout << "NO\n";
		}
		else
			cout << "SI " << sumidero << endl;
	}
	return 0;
}