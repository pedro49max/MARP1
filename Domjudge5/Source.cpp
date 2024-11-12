#include<iostream>
#include<string>
#include"TreeMap_AVL.h"
using namespace std;


void updateTime(map<int, map<int, string>> pacients) {
		auto it = pacients.cbegin();
		auto end = pacients.cend();
		while (it != end) {
			map<int, string> pacient = it->valor;
			int xreytical = it->clave;
			auto itJ = pacient.cbegin();
			auto endJ = pacient.cend();
			while (itJ != endJ) {
				string name = itJ->valor;
				int time = itJ->clave;
				pacient.erase(time);
				time++;
				pacient[time] = name;
				itJ.operator++();
			}//falla algo
			cout << "xd";
			pacients[xreytical] = pacient;
			it.operator++();
		}
}

void getPacient(map<int, map<int, string>> pacients){
	auto it = pacients.cbegin();
	map<int, string> pacient = it->valor;
	int critical = it->clave;
	auto itJ = pacient.cbegin();
	string name = itJ->valor;
	int time = itJ->clave;

	cout << name << endl;

	pacient.erase(time);
	if (pacient.empty())
		pacients.erase(critical);
}

int main() {
	int n;
	cin >> n;
	while (n != 0) {
		map<int, map<int ,string>> pacients;
		for (int i = 0; i < n; i++) {
			string action;
			cin >> action;
			if (action == "A")
				getPacient(pacients);
			else {
				int critical;
				string name;
				cin >> name >> critical;
				map<int, string > pacient;
				pacient[0] = name;
				critical = 1000000 - critical;
				pacients[critical] = pacient;
			}
			updateTime(pacients);
		}

		cin >> n;
	}
	return 0;
}