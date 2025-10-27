#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

struct p {
	int x;
	int deepness;
};

bool operator>(p p1, p p2) {
	return (p1.deepness > p2.deepness);
}

typedef priority_queue<p,vector<p>, greater<p>> pq;

//O(N*N*K)
int dfs(const vector<vector<int>> &tablero, vector<bool> &visited, const int &maxId, const int &k, vector<int> &escaleras) {
	visited[0] = true;
	pq dd;
	p a = { 0,0 };
	int num = 0, deep = 0;
	dd.push(a);//O(log(n))
	
	while (!dd.empty() && num != maxId) {
		a = dd.top(); dd.pop();
		num = a.x; deep = a.deepness;
		//si no es el maximo, explorar adyacentes
		if(num!=maxId)
			for (int x : tablero[num]) {
				if (!visited[x]) {
					visited[x] = true;
					for(int fr = 0; fr < escaleras.size();fr++)//salto por escalera o serpiente
						if (escaleras[fr] == x) {
							x = tablero[x][0];
							visited[x] = true;
						}
					//cout << deep << ": from " << num << " to " << x << endl;
					a.x = x;
					a.deepness = deep + 1;
					dd.push(a);//O(log(n))
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
		vector<vector<int>> tablero(N * N);
		vector<bool> seted(N * N, false);
		vector<int> escaleras(E +S);
		for (int i = 0; i < (S + E); i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			tablero[a].push_back(b);
			escaleras[i] = a;
			seted[a] = true;
		}
		for (int i = 0; i < N * N; i++) {//O(n*K), n=N*N
			if (!seted[i]) {
				seted[i] = true;
				for (int j = i + 1; j < N * N && j <= i + K; j++) {
					tablero[i].push_back(j);
				}
			}
		}
		vector<bool> visited(N * N, false);
		cout << dfs(tablero, visited, N * N - 1, K, escaleras) << "\n";
		cin >> N >> K >> S >> E;
	}


	return 0;
}