#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include <sstream>
#include"GrafoValorado.h"
#include"ConjuntosDisjuntos.h"
#include"PriorityQueue.h"
using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
public:
	Valor costeARM() const {//O(1)
		return coste;
	}
	std::vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}
	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {//O(A*(log(A))
		PriorityQueue<Arista<Valor>> pq(g.aristas());//O(A)

		ConjuntosDisjuntos cjtos(g.V());//O(V)
		while (!pq.empty()) {//O(A*(log(A))
			auto a = pq.top(); pq.pop();//O(log(A))
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {//O(log(V))
				cjtos.unir(v, w);//O(log(V))
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}
};


int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int I;
	while (cin >> I) {
		int P;
		cin >> P;
		GrafoValorado<int> islas(I);

		for (int i = 0; i < P; i++) {
			int a, b, cost;
			cin >> a >> b >> cost;
			a--; b--;
			islas.ponArista({a,b,cost});
		}
		ARM_Kruskal<int> kr(islas);
		int min = kr.costeARM();
		if (kr.ARM().size() != I-1)
			cout << "No hay puentes suficientes\n";
		else
			cout << min << endl;
	}
	return 0;
}