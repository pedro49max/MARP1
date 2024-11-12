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

bool solve_m() {
	int N;
	cin >> N;
	if (N == 0)
		return false;

	pq periods;
	User us;
	for (int i = 0; i < N; ++i) {
		cin >> us.ID >> us.period;
		us.time = us.period;
		periods.push(us);
	}

	int K;
	cin >> K;

	while (K && !periods.empty()) {
		User q = periods.top(); periods.pop();
		cout << q.ID /* << " " << q.time*/ << "\n";
		q.time += q.period;
		periods.push(q);
		--K;
	}
	cout << "---\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("moitor.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	while (solve_m());
	return 0;
}