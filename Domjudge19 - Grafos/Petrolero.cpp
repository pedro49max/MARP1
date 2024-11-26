#include <iostream>
#include<fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;
// Direcciones para moverse en las 8 posibles adyacencias
const vector<pair<int, int>> DIRECTIONS = { {-1, -1}, {-1, 0}, {-1, 1},
										   {0, -1},          {0, 1},
										   {1, -1}, {1, 0}, {1, 1} };

// Convierte coordenadas (fila, columna) a un índice lineal
int posToIndex(int row, int col, int cols) {
	return row * cols + col;
}

// Verifica si una posición está dentro de los límites de la cuadrícula
bool isValid(int row, int col, int rows, int cols) {
	return row >= 0 && row < rows&& col >= 0 && col < cols;
}

int main() {//O(F*C+n)
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int F, C;

	while (cin >> F >> C) {
		vector<string> grid(F);
		for (int i = 0; i < F; i++) cin >> grid[i];

		int n;
		cin >> n;
		vector<pair<int, int>> newCells(n);
		for (int i = 0; i < n; i++) {
			cin >> newCells[i].first >> newCells[i].second;
			newCells[i].first--; // Ajustar índice a 0
			newCells[i].second--;
		}

		// Inicializar conjuntos disjuntos
		ConjuntosDisjuntos disj(F * C);
		int maxSize = 0;

		// Construcción inicial de conjuntos
		for (int row = 0; row < F; row++) {//O(F x C x lg*(N))
			for (int col = 0; col < C; col++) {
				if (grid[row][col] == '#') {
					int currentIndex = posToIndex(row, col, C);
					for (pair<int, int>pxd : DIRECTIONS) {
						int dr = pxd.first, dc = pxd.second;
						int newRow = row + dr, newCol = col + dc;
						if (isValid(newRow, newCol, F, C) && grid[newRow][newCol] == '#') {
							int neighborIndex = posToIndex(newRow, newCol, C);
							disj.unir(currentIndex, neighborIndex);
						}
					}
					maxSize = max(maxSize, disj.tam(currentIndex));
				}
			}
		}

		// Resultado inicial
		vector<int> results;
		results.push_back(maxSize);

		// Procesar nuevas celdas
		for (pair<int, int>pxd : newCells) {//O(n * k * lg*(N))
			int row = pxd.first, col = pxd.second;
			int newIndex = posToIndex(row, col, C);

			if (grid[row][col] != '#') { // Si no está ya contaminada
				grid[row][col] = '#';

				for (pair<int, int> catuja: DIRECTIONS) {
					int dr = catuja.first, dc = catuja.second;
					int newRow = row + dr, newCol = col + dc;
					if (isValid(newRow, newCol, F, C) && grid[newRow][newCol] == '#') {
						int neighborIndex = posToIndex(newRow, newCol, C);
						disj.unir(newIndex, neighborIndex);
					}
				}

				maxSize = max(maxSize, disj.tam(newIndex));
			}

			results.push_back(maxSize);
		}

		// Imprimir resultados
		for (int i = 0; i < results.size(); i++) {
			if (i > 0) cout << " ";
			cout << results[i];
		}
		cout << "\n";
	}

	return 0;
}
