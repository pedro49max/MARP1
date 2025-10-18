#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct User {
	int time;
	int ID;
	int period;
};

bool operator>(User u1, User u2) {
	return (u1.time > u2.time) || (u1.time == u2.time && u1.ID > u2.ID);
}

typedef priority_queue<User, vector<User>, greater<User>> pq;

bool solve_m() {//O(N log N + K log N)
	int N;
	cin >> N;
	if (N == 0)
		return false;

	pq periods;
	User us;
	//Lectura de los usuarios
	for (int i = 0; i < N; ++i) {//O(N log N)
		cin >> us.ID >> us.period;
		us.time = us.period;
		periods.push(us);//O(log N)
	}

	int K;
	cin >> K;
//Procesamiento de los K primeros usuarios. Cada vez que se procesa uno, se vuelve a insertar con su nuevo tiempo.
	while (K && !periods.empty()) {//O(K log N)
		User q = periods.top(); periods.pop();//Saco el usuario con menor tiempo O(log N)
		cout << q.ID << "\n";
		q.time += q.period;
		periods.push(q);//O(log N)
		--K;
	}
	cout << "---\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (solve_m());
	return 0;
}
