#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include"Grafo.h"
using namespace std;

struct p {
	int x;
	int deepness;
};

bool operator>(p p1, p p2) {
	return (p1.deepness > p2.deepness);
}

typedef priority_queue<p,vector<p>, greater<p>> pq;


int dfs(const Grafo &tablero, vector<bool> &visited, const int &maxId, const int &k, vector<int> &escaleras) {
	visited[0] = true;
	pq dd;
	p a = { 0,0 };
	int num = 0, deep = 0;
	dd.push(a);
	while (!dd.empty() && num != maxId) {
		a = dd.top(); dd.pop();
		num = a.x; deep = a.deepness;
		if(num!=maxId)
			for (int x : tablero.ady(num)) {
				if (!visited[x]) {
					visited[x] = true;
					for(int fr = 0; fr < escaleras.size();fr++)//salto por escalera o serpiente
						if (escaleras[fr] == x) {
							x = tablero.ady(x)[0];
							visited[x] = true;
						}
					//cout << deep << ": from " << num << " to " << x << endl;
					a.x = x;
					a.deepness = deep + 1;
					dd.push(a);
				}
			}
	}
	return deep;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int N, K, S, E;
	cin >> N >> K >> S >> E;
	while (N != 0) {
		Grafo tablero(N * N);
		vector<bool> seted(N * N, false);
		vector<int> escaleras(E +S);
		for (int i = 0; i < (S + E); i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			tablero.ponArista(a, b);
			escaleras[i] = a;
			seted[a] = true;
		}
		for (int i = 0; i < N * N; i++) {//O(n*K), n=N*N
			if (!seted[i]) {
				seted[i] = true;
				for (int j = i + 1; j < N * N && j <= i + K; j++) {
					tablero.ponArista(i, j);
				}
			}
		}
		vector<bool> visited(N * N, false);
		cout << dfs(tablero, visited, N * N - 1, K, escaleras) << "\n";
		cin >> N >> K >> S >> E;
	}


	return 0;
}