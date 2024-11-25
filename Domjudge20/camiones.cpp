#include<iostream>
#include<fstream>
#include<vector>
#include"GrafoValorado.h"
using namespace std;

bool dfs(const GrafoValorado<int>& mapaCiudad, vector<bool> &visited, int a, const int& b, const int& anchura) {
	bool okay = false;
	if (a == b)
		okay = true;
	else {
		for (Arista<int> x : mapaCiudad.ady(a)) {
			//x.print();
			//cout << okay << !visited[x.otro(a)] << x.valor() <<" "<< anchura << endl;
			if (!okay && !visited[x.otro(a)] && x.valor() >= anchura) {
				visited[x.otro(a)] = true;
				okay = dfs(mapaCiudad, visited, x.otro(a), b, anchura);
			}
		}
	}

	return okay;
}

/*void printMapInfo(const GrafoValorado<int>& mapaCiudad, vector<bool>& visited, int a) {
	for (Arista<int> x : mapaCiudad.ady(a)) {
		if (!visited[x.otro(a)]) {
			visited[x.otro(a)] = true;
			x.print();
			printMapInfo(mapaCiudad, visited, x.otro(a));
		}
	}
}*/



int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int V;
	while (cin >> V) {
		int E;
		cin >> E;
		GrafoValorado<int> mapaCiudad(V);
		for (int i = 0; i < E; i++) {
			int a, b, anch;
			cin >> a >> b >> anch;		
			a--; b--;
			mapaCiudad.ponArista({ a,b,anch });
		}
		int k;
		cin >> k;
		for (int i = 0; i < k; i++) {
			int a, b, anchura;
			cin >> a >> b >> anchura;
			a--; b--;
			vector<bool>visited(V, false);
			visited[a] = true;
			//printMapInfo(mapaCiudad, visited, a);
			if (dfs(mapaCiudad, visited, a, b, anchura))
				cout << "SI\n";
			else
				cout << "NO\n";
		}
	}

}