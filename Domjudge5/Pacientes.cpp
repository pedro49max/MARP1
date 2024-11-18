#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Paciente {
	string name;
	int gravedad;
	int tiempo; // ~~ hora a la que llego
};

bool operator<(Paciente u1, Paciente u2) {
	return (u1.gravedad < u2.gravedad) || (u1.gravedad == u2.gravedad && u1.tiempo > u2.tiempo);
}

typedef priority_queue<Paciente, vector<Paciente>, less<Paciente>> pq;

bool solve_p() {
	int N;
	cin >> N;
	if (N == 0)
		return false;

	pq pacientes;
	Paciente pac;
	char op;
	for (int i = 0; i < N; ++i) {
		cin >> op;
		if (op == 'I') {
			cin >> pac.name >> pac.gravedad;
			pac.tiempo = i;
			pacientes.push(pac);
		}
		else if (op == 'A') {
			pac = pacientes.top(); pacientes.pop();
			cout << pac.name << endl;
		}
	}
	cout << "---" << endl;

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in_txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (solve_p());
	return 0;
}
