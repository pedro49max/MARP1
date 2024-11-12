#include<iostream>
#include"TreeMap_AVL.h"
using namespace std;

void resolve(const map<int,int>& avltree, int &timer, const int number, int &current) {
	int timeToNext = -1;
	auto it = avltree.cbegin();
	auto end = avltree.cend();
	while (it != end && current < number) {
		int pacient = it->clave;
		int Hz = it->valor;
		it.operator++();
		if (timer % Hz == 0) {
			cout << pacient << endl;
			current++;
		}
		int aux = Hz -(timer % Hz);
		if (aux == 0)
			aux = Hz;
		if (timeToNext == -1 || timeToNext > aux)
			timeToNext = aux;
	}
	timer += timeToNext;
	if (current < number)
		resolve(avltree, timer, number, current);
}

int main() {
	int n;
	cin >> n;
	while (n != 0) {
		map<int, int> avltree;
		int pacient, Hz, number, startTime = -1, current = 0;
		for (int i = 0; i < n; i++) {//reading the operands
			cin >> pacient >> Hz;
			avltree[pacient] = Hz;
			if (startTime == -1 || startTime > Hz)
				startTime = Hz;
		}
		cin >> number;
		resolve(avltree, startTime , number, current);
		cout << "---" << endl;
		cin >> n;
	}

	return 0;
}