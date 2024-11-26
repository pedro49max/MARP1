#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	int R, C;
	while (cin >> R >> C) {
		vector<vector<bool>> visited(R, vector<bool>(C, false));
		char x;
		int couterManchas = 0;
		for (int r = 0; r < R; r++) {//O(n)
			for (int c = 0; c < C; c++) {
				cin >> x;
				if (x == '-') 
					visited[r][c] = true;			
			}
		}
		struct coordenadas {
			int row, col;
		};
		queue<coordenadas> cola;
		int maxi = 0;
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {//O(log(n))
				if (!visited[r][c]) {
					couterManchas++;
					int cx = 0;
					cola.push(coordenadas{ r,c });
					visited[r][c] = true;
					while (!cola.empty()) {
						coordenadas coor = cola.front(); cola.pop();
						cx++;
						if (coor.row + 1 < R && !visited[coor.row + 1][coor.col]) {
							cola.push(coordenadas{ coor.row + 1, coor.col });
							visited[coor.row +1][coor.col] = true;
						}
							
						if (coor.row - 1 >= 0 && !visited[coor.row - 1][coor.col]) {
							cola.push(coordenadas{ coor.row - 1, coor.col });
							visited[coor.row -1][coor.col] = true;
						}
							
						if (coor.col + 1 < C && !visited[coor.row][coor.col + 1]) {
							cola.push(coordenadas{ coor.row, coor.col + 1 });
							visited[coor.row][coor.col +1] = true;
						}
							
						if (coor.col - 1 >= 0 && !visited[coor.row][coor.col - 1]) {
							cola.push(coordenadas{ coor.row, coor.col - 1 });
							visited[coor.row][coor.col -1] = true;
						}		
					}
					if (cx > maxi) {
						maxi = cx;
					}
				}
			}
		}
		cout << couterManchas << " " << maxi << endl;
	}

	return 0;
}