//Pedro Tobalina & Jorge Polo
#include<iostream>
#include<vector>
using namespace std;

void resolve(const vector<int>& tEspera, vector<int>& cajasOcupada, int& puesto) {
	int cajaResult;
	while (puesto <= tEspera.size()) {
		int min = -1;
		for (int i = 0; i < cajasOcupada.size() && puesto <= tEspera.size(); i++) {//va de caja en caja viendo cual o cuales estan libres
			if (cajasOcupada[i] <= 0) {
				if (puesto == tEspera.size())//ya es el turno del enamorado
					cajaResult = i;
				else //va alguien de la fila
					cajasOcupada[i] = tEspera[puesto];	
				puesto++;
			}
			if (min == -1 || cajasOcupada[i] < min) {//para el for loop de abajo
				min = cajasOcupada[i];
			}
		}
		for (int i = 0; i < cajasOcupada.size(); i++)//para provocar que por lo menos 1 caja este libre para la proxima iteración
			cajasOcupada[i] -= min;
	}
	cout << cajaResult + 1 << endl;
}

int main() {
	int cajas, gente;
	cin >> cajas >> gente;
	while (cajas != 0 && gente != 0) {
		vector<int> tEspera(gente);
		for (int i = 0; i < gente; i++) {//leyendo los tiempos de espera
			cin >> tEspera[i];
		}
		vector<int> cajasOcupada(cajas);
		for (int i = 0; i < cajas; i++) {//inicializando las cajas
			cajasOcupada[i] = 0;
		}
		int puesto = 0;
		resolve(tEspera, cajasOcupada, puesto);
		cin >> cajas >> gente;
	}
	return 0;
}